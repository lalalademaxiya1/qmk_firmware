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

#include "quantum.h"
#include "raw_hid.h"

#define KEY_PRESS_FN (0x1 << 0)
#define KEY_PRESS_J (0x1 << 1)
#define KEY_PRESS_Z (0x1 << 2)
#define KEY_PRESS_FACTORY_RESET (KEY_PRESS_FN | KEY_PRESS_J | KEY_PRESS_Z)

#ifndef NKRO
#    include <string.h>
#    define RAW_EPSIZE 32
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
    FACTORY_TEST_CMD_OS_SWITCH = 0x02,
    FACTORY_TEST_CMD_JUMP_TO_BL,
    FACTORY_TEST_CMD_EEPROM_CLEAR,
};

uint16_t            key_press_status    = 0;
uint32_t            timer_3s_buffer     = 0;
uint32_t            timer_300ms_buffer  = 0;
uint8_t             factory_reset_count = 0;
bool                factory_reset_flag  = false;
bool                report_os_sw_state  = false;
extern matrix_row_t matrix[MATRIX_ROWS];

#ifdef SPLIT_KEYBOARD
#    ifdef RGB_MATRIX_ENABLE
uint8_t led_state        = 0;
uint8_t light_test_state = 0;
HSV     hsv;
#    endif
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
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
        default:
            return process_record_user(keycode, record);
    }
}

static void factory_reset(void) {
    timer_300ms_buffer          = timer_read32();
    layer_state_t default_layer = default_layer_state;
    eeconfig_init();
    default_layer_set(default_layer);
    factory_reset_count++;
}

void factory_reset_task(void) {
    if (timer_3s_buffer && (timer_elapsed32(timer_3s_buffer) > 3000)) {
        timer_3s_buffer = 0;
        if (key_press_status == KEY_PRESS_FACTORY_RESET) {
            factory_reset_flag = true;
            factory_reset();
        }
        key_press_status = 0;
    }
}

void factory_reset_ind_task(void) {
    if (timer_300ms_buffer && (timer_elapsed32(timer_300ms_buffer) > 300)) {
        if (factory_reset_count++ > 7) {
            timer_300ms_buffer  = 0;
            factory_reset_count = 0;
            factory_reset_flag  = false;
            if (host_keyboard_led_state().caps_lock) {
                writePin(LED_CAPS_LOCK_PIN, LED_OS_PIN_ON_STATE);
            }
        } else {
            timer_300ms_buffer = timer_read32();
            if (factory_reset_count % 2 == 0) {
                writePin(LED_MAC_OS_PIN, LED_OS_PIN_ON_STATE);
                writePin(LED_WIN_OS_PIN, LED_OS_PIN_ON_STATE);
                writePin(LED_CAPS_LOCK_PIN, LED_OS_PIN_ON_STATE);
            } else {
                writePin(LED_MAC_OS_PIN, !LED_OS_PIN_ON_STATE);
                writePin(LED_WIN_OS_PIN, !LED_OS_PIN_ON_STATE);
                writePin(LED_CAPS_LOCK_PIN, !LED_OS_PIN_ON_STATE);
            }
        }
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
