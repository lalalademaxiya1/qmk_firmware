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
#include "keychron_ft_c1v2.h"

void housekeeping_task_kb(void) {
    if (!factory_reset_flag) {
        if (default_layer_state == (1 << 0)) {
            writePin(LED_MAC_OS_PIN, LED_OS_PIN_ON_STATE);
            writePin(LED_WIN_OS_PIN, !LED_OS_PIN_ON_STATE);
        }
        if (default_layer_state == (1 << 2)) {
            writePin(LED_MAC_OS_PIN, !LED_OS_PIN_ON_STATE);
            writePin(LED_WIN_OS_PIN, LED_OS_PIN_ON_STATE);
        }
    }
    factory_reset_task();
    factory_reset_ind_task();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res && (!factory_reset_flag)) {
#ifdef LED_CAPS_LOCK_PIN
        writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
#endif
    }
    return res;
}
