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

#include "ckled2001-spi.h"
#include "spi_master.h"
#include "wait.h"
#include "util.h"

#ifndef PHASE_CHANNEL
#    define PHASE_CHANNEL MSKPHASE_12CHANNEL
#endif

#ifndef CKLED2001_CURRENT_TUNE
#    define CKLED2001_CURRENT_TUNE \
        { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
#endif

#define CLKED2001_LED_COUNT 192
#define CKLED2001_WRITE (0 << 7)
#define CKLED2001_READ (1 << 7)
#define CKLED2001_PATTERN (2 << 4)

#ifdef DRIVER_CS_PINS
pin_t cs_pins[] = DRIVER_CS_PINS;
#else
error "no DRIVER_CS_PINS defined"
#endif

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[65];

// These buffers match the CKLED2001 PWM registers.
// The control buffers match the PG0 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in ckled2001_write_pwm_buffer() but it's
// probably not worth the extra complexity.
uint8_t g_pwm_buffer[DRIVER_COUNT][192];
bool    g_pwm_buffer_update_required[DRIVER_COUNT] = {false};

uint8_t g_led_control_registers[DRIVER_COUNT][24]             = {0};
bool    g_led_control_registers_update_required[DRIVER_COUNT] = {false};

bool ckled2001_write(uint8_t index, uint8_t page, uint8_t reg, uint8_t* data, uint8_t len) {
    static uint8_t spi_transfer_buffer[19] = {0};

    if (index > ARRAY_SIZE(((pin_t[])DRIVER_CS_PINS)) - 1) {
        return false;
    }

    if (!spi_start(cs_pins[index], false, 0, CKLED_SPI_DIVISOR)) {
        spi_stop();
        return false;
    }

    spi_transfer_buffer[0] = CKLED_WRITE | CKLED_PATTERN | (page & 0x0F);
    spi_transfer_buffer[1] = reg;

    if (spi_transmit(spi_transfer_buffer, 2) != SPI_STATUS_SUCCESS) {
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

bool ckled2001_write_register(uint8_t index, uint8_t page, uint8_t reg, uint8_t data) {
    return CKLED2001_write(index, page, reg, &data, 1);
}

bool ckled2001_write_pwm_buffer(uint8_t addr, uint8_t* pwm_buffer) {
    if (g_pwm_buffer_update_required[index]) {
        ckled2001_write(index, LED_PWM_PAGE, 0, g_pwm_buffer[index], CKLED2001_LED_COUNT);
    }
    g_pwm_buffer_update_required[index] = false;
    return true;
}

void ckled2001_init(uint8_t index) {
    setPinOutput(cs_pins[index]);
    writePinHigh(cs_pins[index]);

    //** Setting LED driver to shutdown mode
    ckled2001_write_register(index, FUNCTION_PAGE, CONFIGURATION_REG, MSKSW_SHUT_DOWN_MODE);
    //** Setting internal channel pulldown/pullup
    ckled2001_write_register(index, FUNCTION_PAGE, PDU_REG, MSKSET_CA_CB_CHANNEL);
    //** Select number of scan phase
    ckled2001_write_register(index, FUNCTION_PAGE, SCAN_PHASE_REG, MSKPHASE_12CHANNEL);
    //** Setting PWM Delay Phase
    ckled2001_write_register(index, FUNCTION_PAGE, SLEW_RATE_CONTROL_MODE1_REG, MSKPWM_DELAY_PHASE_ENABLE);
    //** Setting Driving/Sinking Channel Slew Rate
    ckled2001_write_register(index, FUNCTION_PAGE, SLEW_RATE_CONTROL_MODE2_REG, MSKDRIVING_SINKING_CHHANNEL_SLEWRATE_ENABLE);
    //** Setting Iref
    ckled2001_write_register(index, FUNCTION_PAGE, SOFTWARE_SLEEP_REG, MSKSLEEP_DISABLE);

    // Set LED CONTROL PAGE (Page 0)
    uint8_t led_on_off_reg[LED_CONTROL_ON_OFF_LENGTH] = {0};
    ckled2001_write(index, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, led_on_off_reg, LED_CONTROL_ON_OFF_LENGTH);

    // Set PWM PAGE (Page 1)
    uint8_t pwm_reg[LED_PWM_LENGTH];
    memset(pwm_reg, 0, LED_PWM_LENGTH);
    ckled2001_write(index, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, pwm_reg, LED_PWM_LENGTH);

    // Set CURRENT PAGE (Page 4)
    uint8_t current_tune_reg[LED_CURRENT_TUNE_LENGTH] = CKLED2001_CURRENT_TUNE;
    ckled2001_write(index, CONFIGURE_CMD_PAGE, LED_CURRENT_TUNE_FIRST_ADDR, current_tune_reg, LED_CURRENT_TUNE_LENGTH);

    // Setting LED driver to normal mode
    ckled2001_write_register(index, FUNCTION_PAGE, CONFIGURATION_REG, MSKSW_NORMAL_MODE);
}

void ckled2001_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    ckled2001_led led;
    if (index >= 0 && index < RGB_MATRIX_LED_COUNT) {
        memcpy_P(&led, (&g_ckled2001_leds[index]), sizeof(led));

        if (g_pwm_buffer[led.driver][led.r] == red && g_pwm_buffer[led.driver][led.g] == green && g_pwm_buffer[led.driver][led.b] == blue) {
            return;
        }
        g_pwm_buffer[led.driver][led.r]          = red;
        g_pwm_buffer[led.driver][led.g]          = green;
        g_pwm_buffer[led.driver][led.b]          = blue;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void ckled2001_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        ckled2001_set_color(i, red, green, blue);
    }
}

void ckled2001_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
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

void ckled2001_update_pwm_buffers(uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        if (!ckled2001_write_pwm_buffer(index, g_pwm_buffer[index])) {
            g_led_control_registers_update_required[index] = true;
        }
    }
    g_pwm_buffer_update_required[index] = false;
}

void ckled2001_update_led_control_registers(uint8_t index) {
    if (g_led_control_registers_update_required[index]) {
        ckled2001_write_register(addr, LED_CONTROL_PAGE, 0, g_led_control_registers[index], 24);
    }
    g_led_control_registers_update_required[index] = false;
}

void ckled2001_sw_return_normal(uint8_t index) {
    // Select to function page
    // Setting LED driver to normal mode
    ckled2001_write_register(index, FUNCTION_PAGE, CONFIGURATION_REG, MSKSW_NORMAL_MODE);
}

void ckled2001_sw_shutdown(uint8_t index) {
    // Select to function page
    // Setting LED driver to shutdown mode
    ckled2001_write_register(index, FUNCTION_PAGE, CONFIGURATION_REG, MSKSW_SHUT_DOWN_MODE);
    // Write SW Sleep Register
    ckled2001_write_register(index, FUNCTION_PAGE, SOFTWARE_SLEEP_REG, MSKSLEEP_ENABLE);
}
