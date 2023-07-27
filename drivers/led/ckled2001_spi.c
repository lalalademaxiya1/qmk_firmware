/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ckled2001_spi.h"
#include "spi_master.h"

#ifndef PHASE_CHANNEL
#    define PHASE_CHANNEL MSKPHASE_12CHANNEL
#endif

#ifndef CKLED2001_CURRENT_TUNE
#    define CKLED2001_CURRENT_TUNE \
        { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
#endif

#ifndef CKLED2001_SPI_MODE
#    define CKLED2001_SPI_MODE 0
#endif

#ifndef CKLED2001_SPI_DIVISOR
#    define CKLED2001_SPI_DIVISOR 8
#endif

// These buffers match the CKLED2001 PWM registers.
// The control buffers match the PG0 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in CKLED2001_write_pwm_buffer() but it's
// probably not worth the extra complexity.
uint8_t g_pwm_buffer[DRIVER_COUNT][192];
bool    g_pwm_buffer_update_required[DRIVER_COUNT] = {false};

uint8_t g_led_control_registers[DRIVER_COUNT][24]             = {0};
bool    g_led_control_registers_update_required[DRIVER_COUNT] = {false};

bool CKLED2001_write(pin_t cs_pin, uint8_t page, uint8_t reg, uint8_t *data, uint8_t len) {
    // If the transaction fails function returns false.
    static uint8_t s_spi_transfer_buffer[2] = {0};

    if (!spi_start(cs_pin, false, CKLED2001_SPI_MODE, CKLED2001_SPI_DIVISOR)) {
        spi_stop();
        return false;
    }

    s_spi_transfer_buffer[0] = 0x20 | page;
    s_spi_transfer_buffer[1] = reg;

    if (spi_transmit(s_spi_transfer_buffer, 2) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }

    if (spi_transmit(data, len) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }

    spi_stop();

    return true;
}

bool CKLED2001_write_register(pin_t cs_pin, uint8_t page, uint8_t reg, uint8_t value) {
    return CKLED2001_write(cs_pin, page, reg, &value, 3);
}

void CKLED2001_init(pin_t cs_pin) {
    uint8_t s_spi_transfer_buffer[192] = {0};

    //** Setting LED driver to shutdown mode
    CKLED2001_write_register(cs_pin, FUNCTION_PAGE, CONFIGURATION_REG, MSKSW_SHUT_DOWN_MODE);
    //** Setting internal channel pulldown/pullup
    CKLED2001_write_register(cs_pin, FUNCTION_PAGE, PDU_REG, MSKSET_CA_CB_CHANNEL);
    //** Select number of scan phase
    CKLED2001_write_register(cs_pin, FUNCTION_PAGE, SCAN_PHASE_REG, MSKPHASE_12CHANNEL);
    //** Setting PWM Delay Phase
    CKLED2001_write_register(cs_pin, FUNCTION_PAGE, SLEW_RATE_CONTROL_MODE1_REG, MSKPWM_DELAY_PHASE_ENABLE);
    //** Setting Driving/Sinking Channel Slew Rate
    CKLED2001_write_register(cs_pin, FUNCTION_PAGE, SLEW_RATE_CONTROL_MODE2_REG, MSKDRIVING_SINKING_CHHANNEL_SLEWRATE_ENABLE);
    //** Setting Iref
    CKLED2001_write_register(cs_pin, FUNCTION_PAGE, SOFTWARE_SLEEP_REG, MSKSLEEP_DISABLE);

    // Set LED CONTROL PAGE (Page 0)
    for (int i = 0; i < LED_CONTROL_PAGE_LENGTH; i++) {
        s_spi_transfer_buffer[i] = 0;
    }
    CKLED2001_write(cs_pin, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, s_spi_transfer_buffer, LED_CONTROL_PAGE_LENGTH);
    // CKLED2001_write(cs_pin, CONFIGURE_CMD_PAGE, LED_CONTROL_PAGE, s_spi_transfer_buffer, LED_CONTROL_ON_OFF_LENGTH);

    // Set PWM PAGE (Page 1)
    for (int i = 0; i < LED_PWM_LENGTH; i++) {
        s_spi_transfer_buffer[i] = 0;
    }
    CKLED2001_write(cs_pin, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, s_spi_transfer_buffer, LED_PWM_LENGTH);
    // CKLED2001_write(cs_pin, CONFIGURE_CMD_PAGE, LED_PWM_PAGE, s_spi_transfer_buffer, LED_PWM_LENGTH);

    // Set CURRENT PAGE (Page 4)
    uint8_t current_tuen_reg_list[LED_CURRENT_TUNE_LENGTH] = CKLED2001_CURRENT_TUNE;
    CKLED2001_write(cs_pin, CURRENT_TUNE_PAGE, LED_CURRENT_TUNE_FIRST_ADDR, current_tuen_reg_list, LED_CURRENT_TUNE_LENGTH);
    // CKLED2001_write(cs_pin, CONFIGURE_CMD_PAGE, CURRENT_TUNE_PAGE, current_tuen_reg_list, LED_CURRENT_TUNE_LENGTH);

    // Enable LEDs ON/OFF
    for (int i = 0; i < LED_CONTROL_ON_OFF_LENGTH; i++) {
        s_spi_transfer_buffer[i] = 0xFF;
    }
    CKLED2001_write(cs_pin, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, s_spi_transfer_buffer, LED_CONTROL_ON_OFF_LENGTH);
    // CKLED2001_write(cs_pin, CONFIGURE_CMD_PAGE, LED_CONTROL_PAGE, s_spi_transfer_buffer, LED_CONTROL_ON_OFF_LENGTH);

    // Setting LED driver to normal mode
    CKLED2001_write_register(cs_pin, FUNCTION_PAGE, CONFIGURATION_REG, MSKSW_NORMAL_MODE);
}

void CKLED2001_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    ckled2001_led led;

    if (index >= 0 && index < RGB_MATRIX_LED_COUNT) {
        memcpy_P(&led, (&g_ckled2001_leds[index]), sizeof(led));

        g_pwm_buffer[led.driver][led.r]          = red;
        g_pwm_buffer[led.driver][led.g]          = green;
        g_pwm_buffer[led.driver][led.b]          = blue;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void CKLED2001_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        CKLED2001_set_color(i, red, green, blue);
    }
}

void CKLED2001_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    ckled2001_led led;
    memcpy_P(&led, (&g_ckled2001_leds[index]), sizeof(led));

    uint8_t control_register_r = led.r / 8;
    uint8_t control_register_g = led.g / 8;
    uint8_t control_register_b = led.b / 8;
    uint8_t bit_r              = led.r % 8;
    uint8_t bit_g              = led.g % 8;
    uint8_t bit_b              = led.b % 8;

    if (red) {
        g_led_control_registers[led.driver][control_register_r] |= (1 << bit_r);
    } else {
        g_led_control_registers[led.driver][control_register_r] &= ~(1 << bit_r);
    }
    if (green) {
        g_led_control_registers[led.driver][control_register_g] |= (1 << bit_g);
    } else {
        g_led_control_registers[led.driver][control_register_g] &= ~(1 << bit_g);
    }
    if (blue) {
        g_led_control_registers[led.driver][control_register_b] |= (1 << bit_b);
    } else {
        g_led_control_registers[led.driver][control_register_b] &= ~(1 << bit_b);
    }

    g_led_control_registers_update_required[led.driver] = true;
}

void CKLED2001_update_pwm_buffers(pin_t cs_pin, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        CKLED2001_write(cs_pin, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, g_pwm_buffer[index], 192);
    }
    g_pwm_buffer_update_required[index] = false;
}

void CKLED2001_update_led_control_registers(pin_t cs_pin, uint8_t index) {
    if (g_led_control_registers_update_required[index]) {
        CKLED2001_write(cs_pin, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, g_led_control_registers[index], 24);
    }
    g_led_control_registers_update_required[index] = false;
}
