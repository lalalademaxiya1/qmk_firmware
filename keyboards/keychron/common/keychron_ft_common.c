/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

#include "keychron_ft_common.h"
#include "raw_hid.h"

#ifndef NKRO
#    include <string.h>
#    define RAW_EPSIZE 32
#endif

#ifndef BL_TEST_KEY1
#    define BL_TEST_KEY1 KC_RIGHT
#endif

#ifndef BL_TEST_KEY2
#    define BL_TEST_KEY2 KC_HOME
#endif

#ifndef F_RESET_KEY1
#    define F_RESET_KEY1 KC_J
#endif

#ifndef F_RESET_KEY2
#    define F_RESET_KEY2 KC_Z
#endif

enum {
    OS_SWITCH = 0x01,
};

enum {
    FACTORY_TEST_CMD_BACKLIGHT = 0x01,
    FACTORY_TEST_CMD_OS_SWITCH,
    FACTORY_TEST_CMD_JUMP_TO_BL,
    FACTORY_TEST_CMD_EEPROM_CLEAR,
};
// clang-format on

uint16_t            key_press_status    = 0;
uint32_t            timer_3s_buffer     = 0;
uint32_t            timer_300ms_buffer  = 0;
uint8_t             factory_reset_count = 0;
bool                report_os_sw_state  = false;
extern matrix_row_t matrix[MATRIX_ROWS];

#ifdef SPLIT_KEYBOARD
#    ifdef RGB_MATRIX_ENABLE
uint8_t led_state        = 0;
uint8_t light_test_state = 0;
HSV     hsv;
#    endif
#endif

__attribute__((weak)) bool process_record_keychron_ft(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#if defined(FN_KEY1) || defined(FN_KEY2)
#    ifdef FN_KEY1
        case FN_KEY1: /* fall through */
#    endif
#    ifdef FN_KEY2
        case FN_KEY2:
#    endif
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_FN;
            } else {
                key_press_status &= ~KEY_PRESS_FN;
                timer_3s_buffer = 0;
            }
            return true;
#endif
        case F_RESET_KEY1:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_J;
                if (key_press_status == KEY_PRESS_FACTORY_RESET) {
                    timer_3s_buffer = timer_read32();
                }
            } else {
                key_press_status &= ~KEY_PRESS_J;
                timer_3s_buffer = 0;
            }
            return true;
        case F_RESET_KEY2:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_Z;
                if (key_press_status == KEY_PRESS_FACTORY_RESET) {
                    timer_3s_buffer = timer_read32();
                }
            } else {
                key_press_status &= ~KEY_PRESS_Z;
                timer_3s_buffer = 0;
            }
            return true;
        case BL_TEST_KEY1:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_HOME;
                if (led_test_mode) {
                    if (++led_test_mode >= LED_TEST_MODE_MAX) {
                        led_test_mode = LED_TEST_MODE_WHITE;
                    }
                } else if (key_press_status == KEY_PRESS_LED_TEST) {
                    timer_3s_buffer = timer_read32();
                }
            } else {
                key_press_status &= ~KEY_PRESS_HOME;
                timer_3s_buffer = 0;
            }
            return true;
        case BL_TEST_KEY2:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_RIGHT;
                if (led_test_mode) {
                    led_test_mode = LED_TEST_MODE_OFF;
                } else if (key_press_status == KEY_PRESS_LED_TEST) {
                    timer_3s_buffer = timer_read32();
                }
            } else {
                key_press_status &= ~KEY_PRESS_RIGHT;
                timer_3s_buffer = 0;
            }
            return true;
        default:
            return true;
    }
}

static void factory_reset(void) {
    timer_300ms_buffer = timer_read32();
    factory_reset_count++;
#ifdef KEYBOARD_keychron_c3_pro_ansi_white
    layer_state_t default_layer = 1 << 2;
#else
    layer_state_t default_layer = default_layer_state;
#endif
    eeconfig_init();
    default_layer_set(default_layer);
    led_test_mode = LED_TEST_MODE_OFF;
#ifdef LED_MATRIX_ENABLE
    if (!led_matrix_is_enabled()) {
        led_matrix_enable();
    }
    led_matrix_init();
#endif
#ifdef RGB_MATRIX_ENABLE
    if (!rgb_matrix_is_enabled()) {
        rgb_matrix_enable();
    }
    rgb_matrix_init();
#    ifdef SPLIT_KEYBOARD
    led_state = rgb_matrix_get_mode();
    hsv       = rgb_matrix_get_hsv();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#    endif
#endif
}

static void timer_3s_task(void) {
    if (timer_elapsed32(timer_3s_buffer) > 3000) {
        timer_3s_buffer = 0;
        if (key_press_status == KEY_PRESS_FACTORY_RESET) {
            factory_reset();
        } else if (key_press_status == KEY_PRESS_LED_TEST) {
#ifdef SPLIT_KEYBOARD
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif
            led_test_mode = LED_TEST_MODE_WHITE;
#ifdef LED_MATRIX_ENABLE
            if (!led_matrix_is_enabled()) {
                led_matrix_enable();
            }
#endif
#ifdef RGB_MATRIX_ENABLE
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_enable();
            }
#endif
        }
        key_press_status = 0;
    }
}

static void timer_300ms_task(void) {
    if (timer_elapsed32(timer_300ms_buffer) > 300) {
        if (factory_reset_count++ > 6) {
            timer_300ms_buffer  = 0;
            factory_reset_count = 0;
#ifdef SPLIT_KEYBOARD
            rgb_matrix_mode_noeeprom(led_state);
            rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
#endif
        } else {
            timer_300ms_buffer = timer_read32();
        }
    }
}

#ifdef LED_MATRIX_ENABLE
bool led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (factory_reset_count) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            led_matrix_set_value(i, factory_reset_count % 2 ? 0 : UINT8_MAX);
        }
    }
    return true;
}
#endif

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (factory_reset_count) {
        if (rgb_matrix_get_mode() == RGB_MATRIX_SOLID_COLOR) {
            if (factory_reset_count % 2) {
                rgb_matrix_sethsv_noeeprom(HSV_RED);
            } else {
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
        } else {
            for (uint8_t i = led_min; i <= led_max; i++) {
                rgb_matrix_set_color(i, factory_reset_count % 2 ? 0 : RGB_RED);
            }
        }
    } else if (led_test_mode) {
        switch (led_test_mode) {
            case LED_TEST_MODE_WHITE:
                if (rgb_matrix_get_mode() == RGB_MATRIX_SOLID_COLOR) {
                    rgb_matrix_sethsv_noeeprom(HSV_WHITE);
                } else {
                    for (uint8_t i = led_min; i <= led_max; i++) {
                        rgb_matrix_set_color(i, RGB_WHITE);
                    }
                }
                break;
            case LED_TEST_MODE_RED:
                if (rgb_matrix_get_mode() == RGB_MATRIX_SOLID_COLOR) {
                    rgb_matrix_sethsv_noeeprom(HSV_RED);
                } else {
                    for (uint8_t i = led_min; i <= led_max; i++) {
                        rgb_matrix_set_color(i, RGB_RED);
                    }
                }
                break;
            case LED_TEST_MODE_GREEN:
                if (rgb_matrix_get_mode() == RGB_MATRIX_SOLID_COLOR) {
                    rgb_matrix_sethsv_noeeprom(HSV_GREEN);
                } else {
                    for (uint8_t i = led_min; i <= led_max; i++) {
                        rgb_matrix_set_color(i, RGB_GREEN);
                    }
                }
                break;
            case LED_TEST_MODE_BLUE:
                if (rgb_matrix_get_mode() == RGB_MATRIX_SOLID_COLOR) {
                    rgb_matrix_sethsv_noeeprom(HSV_BLUE);
                } else {
                    for (uint8_t i = led_min; i <= led_max; i++) {
                        rgb_matrix_set_color(i, RGB_BLUE);
                    }
                }
                break;
            default:
                break;
        }
    }
    return true;
}
#endif

void housekeeping_task_keychron_ft(void) {
    if (timer_3s_buffer) {
        timer_3s_task();
    }
    if (timer_300ms_buffer) {
        timer_300ms_task();
    }
}

static void system_switch_state_report(uint8_t index, bool active) {
    uint16_t checksum         = 0;
    uint8_t  data[RAW_EPSIZE] = {0};
    uint8_t  payload[3]       = {0};

    if (report_os_sw_state) {
        payload[0] = FACTORY_TEST_CMD_OS_SWITCH;
        payload[1] = OS_SWITCH;
#if defined(OS_SWITCH_REVERSE)
        payload[2] = !active;
#else
        payload[2] = active;
#endif
        data[0] = 0xAB;
        memcpy(&data[1], payload, 3);
        for (uint8_t i = 1; i < RAW_EPSIZE - 3; i++) {
            checksum += data[i];
        }
        data[RAW_EPSIZE - 2] = checksum & 0xFF;
        data[RAW_EPSIZE - 1] = (checksum >> 8) & 0xFF;
        raw_hid_send(data, RAW_EPSIZE);
    }
}

bool dip_switch_update_user(uint8_t index, bool active) {
    /* Send default layer state to host */
    system_switch_state_report(index, active);
    return true;
}

bool via_command_kb(uint8_t *data, uint8_t length) {
    if (data[0] == 0xAB) {
        uint16_t checksum = 0;
        for (uint8_t i = 1; i < RAW_EPSIZE - 3; i++) {
            checksum += data[i];
        }
        /* Verify checksum */
        if ((checksum & 0xFF) != data[RAW_EPSIZE - 2] || checksum >> 8 != data[RAW_EPSIZE - 1]) {
            return true;
        }
        switch (data[1]) {
#if defined(RGB_MATRIX_ENABLE)
            case FACTORY_TEST_CMD_BACKLIGHT:
                led_test_mode = data[2];
#    if defined(SPLIT_KEYBOARD)
                if (led_test_mode) {
                    light_test_state += 1;
                    if (light_test_state == 1) {
                        led_state = rgb_matrix_get_mode();
                        hsv       = rgb_matrix_get_hsv();
                    }
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                } else {
                    if (light_test_state) {
                        light_test_state = 0;
                        rgb_matrix_mode_noeeprom(led_state);
                        rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
                    }
                }
#    endif
                timer_3s_buffer = 0;
                break;
#endif
#if defined(DIP_SWITCH_ENABLE)
            case FACTORY_TEST_CMD_OS_SWITCH:
                report_os_sw_state = data[2];
                if (report_os_sw_state) {
                    dip_switch_read(true);
                }
                break;
#endif
            case FACTORY_TEST_CMD_JUMP_TO_BL:
                if (matrix[0] & 0x1 && matrix[MATRIX_ROWS - 1] & (0x1 << (MATRIX_COLS - 1))) {
                    if (memcmp(&data[2], "JumpToBootloader", strlen("JumpToBootloader")) == 0) bootloader_jump();
                }
                break;
            case FACTORY_TEST_CMD_EEPROM_CLEAR:
                if (matrix[0] & 0x1 && matrix[MATRIX_ROWS - 1] & (0x1 << (MATRIX_COLS - 1))) {
                    if (data[2]) {
                        factory_reset();
                    }
                }
                break;
        }
        return true;
    }
    return false;
}
