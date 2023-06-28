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

#include "c3.h"

static uint32_t os_switch_timer_buffer   = 0;
static uint8_t  os_switch_indicate_count = 0;

void keyboard_post_init_kb(void) {
    setPinOutputPushPull(LED_MAC_OS_PIN);
    setPinOutputPushPull(LED_WIN_OS_PIN);

    default_layer_set(1U << 2);

    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    if (default_layer_state == (1 << 0)) {
        writePin(LED_MAC_OS_PIN, LED_PIN_ON_STATE);
        writePin(LED_WIN_OS_PIN, !LED_PIN_ON_STATE);
    }
    if (default_layer_state == (1 << 2)) {
        writePin(LED_MAC_OS_PIN, !LED_PIN_ON_STATE);
        writePin(LED_WIN_OS_PIN, LED_PIN_ON_STATE);
    }

    if (os_switch_timer_buffer && timer_elapsed32(os_switch_timer_buffer) > 300) {
        if (os_switch_indicate_count++ > 6) {
            os_switch_indicate_count = 0;
            os_switch_timer_buffer   = 0;
        } else {
            os_switch_timer_buffer = timer_read32();
        }
    }

    housekeeping_task_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case KC_OSSW:
            if (record->event.pressed) {
                default_layer_xor(1U << 0);
                default_layer_xor(1U << 2);
                os_switch_timer_buffer = timer_read32();
            }
            return false;
        default:
            return true;
    }
}

bool led_matrix_indicators_kb(void) {
    if (!led_matrix_indicators_user()) {
        return false;
    }

    if (os_switch_indicate_count) {
        led_matrix_set_value_all(os_switch_indicate_count % 2 ? 0 : UINT8_MAX);
    }

    return true;
}
