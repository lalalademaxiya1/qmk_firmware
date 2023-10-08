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

uint8_t win_lock_toggle_flag = 0;

void keyboard_post_init_kb(void) {
    setPinOutputPushPull(LED_WIN_LOCK_PIN);
    eeconfig_read_user_datablock(&win_lock_toggle_flag);
    keyboard_post_init_user();
}

void housekeeping_task_kb() {
    if (win_lock_toggle_flag) {
        writePin(LED_WIN_LOCK_PIN, LED_PIN_ON_STATE);
    } else {
        writePin(LED_WIN_LOCK_PIN, !LED_PIN_ON_STATE);
    }
}

void suspend_power_down_kb(void) {
    suspend_power_down_user();
    writePin(LED_WIN_LOCK_PIN, !LED_PIN_ON_STATE);
}

void eeconfig_init_kb(void) {
#if (EECONFIG_KB_DATA_SIZE) == 0
    // Reset Keyboard EEPROM value to blank, rather than to a set value
    eeconfig_update_kb(0);
#endif
    keymap_config.raw  = eeconfig_read_keymap();
    keymap_config.nkro = 1;
    eeconfig_update_keymap(keymap_config.raw);

    win_lock_toggle_flag = 0;
    eeconfig_update_user_datablock(&win_lock_toggle_flag);

    eeconfig_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case GU_TOGG:
            if (record->event.pressed) {
                win_lock_toggle_flag = !win_lock_toggle_flag;
                if (win_lock_toggle_flag) {
                    writePin(LED_WIN_LOCK_PIN, LED_PIN_ON_STATE);
                } else {
                    writePin(LED_WIN_LOCK_PIN, !LED_PIN_ON_STATE);
                }
                eeconfig_update_user_datablock(&win_lock_toggle_flag);
            }
            return true;
        default:
            return true;
    }
}
