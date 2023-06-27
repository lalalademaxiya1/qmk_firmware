/* Copyright 2022 @ Keychron (https://www.keychron.com)
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
// clang-format off
const matrix_row_t matrix_mask[] = {
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111101111,
};
// clang-format on
#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    return true;
}

#endif // DIP_SWITCH_ENABLE

#if (defined(RGB_MATRIX_ENABLE) || defined(LED_MATRIX_ENABLE)) && defined(NUM_LOCK_INDEX) && defined(CAPS_LOCK_INDEX) && defined(MAC_OS_LED_INDEX) && defined(WIN_OS_LED_INDEX)

#    ifdef RGB_MATRIX_ENABLE
#        define LED_MATRIX_INDICATORS_KB rgb_matrix_indicators_kb
#        define LED_MATRIX_INDICATORS_USER rgb_matrix_indicators_user
#        define LED_MATRIX_SET_COLOR rgb_matrix_set_color
#        define LED_MATRIX_UPDATE_PWN_BUFFERS rgb_matrix_update_pwm_buffers
#        define LED_MATRIX_INDICATORS_NONE_KB rgb_matrix_indicators_none_kb
#        define LED_MATRIX_IS_ENABLED rgb_matrix_is_enabled
#        define COLOR_WHITE 255, 255, 255
#        define COLOR_BLACK 0, 0, 0
#    endif

#    ifdef LED_MATRIX_ENABLE
#        define LED_MATRIX_INDICATORS_KB led_matrix_indicators_kb
#        define LED_MATRIX_INDICATORS_USER led_matrix_indicators_user
#        define LED_MATRIX_SET_COLOR led_matrix_set_value
#        define LED_MATRIX_UPDATE_PWN_BUFFERS led_matrix_update_pwm_buffers
#        define LED_MATRIX_INDICATORS_NONE_KB led_matrix_indicators_none_kb
#        define LED_MATRIX_IS_ENABLED led_matrix_is_enabled
#        define COLOR_WHITE 255
#        define COLOR_BLACK 0
#    endif

extern void LED_MATRIX_UPDATE_PWN_BUFFERS(void);

bool LED_MATRIX_INDICATORS_KB(void) {
    if (!LED_MATRIX_INDICATORS_USER()) {
        return false;
    }
#    if defined(CAPS_LOCK_INDEX)
    if (host_keyboard_led_state().caps_lock) {
        LED_MATRIX_SET_COLOR(CAPS_LOCK_INDEX, COLOR_WHITE);
    } else {
        LED_MATRIX_SET_COLOR(CAPS_LOCK_INDEX, COLOR_BLACK);
    }
#    endif // CAPS_LOCK_INDEX
#    if defined(NUM_LOCK_INDEX)
    if (host_keyboard_led_state().num_lock) {
        LED_MATRIX_SET_COLOR(NUM_LOCK_INDEX, COLOR_WHITE);
    } else {
        LED_MATRIX_SET_COLOR(NUM_LOCK_INDEX, COLOR_BLACK);
    }
#    endif // NUM_LOCK_INDEX
#    if defined(MAC_OS_LED_INDEX)
    if (default_layer_state == (1 << 0)) {
        LED_MATRIX_SET_COLOR(MAC_OS_LED_INDEX, COLOR_WHITE);
    } else {
        LED_MATRIX_SET_COLOR(MAC_OS_LED_INDEX, COLOR_BLACK);
    }
#    endif // MAC_OS_LED_INDEX
#    if defined(WIN_OS_LED_INDEX)
    if (default_layer_state == (1 << 2)) {
        LED_MATRIX_SET_COLOR(WIN_OS_LED_INDEX, COLOR_WHITE);
    } else {
        LED_MATRIX_SET_COLOR(WIN_OS_LED_INDEX, COLOR_BLACK);
    }
#    endif // WIN_OS_LED_INDEX
    return true;
}

void LED_MATRIX_INDICATORS_NONE_KB(void) {
    LED_MATRIX_INDICATORS_KB();
    LED_MATRIX_UPDATE_PWN_BUFFERS();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);

    if (LED_MATRIX_IS_ENABLED()
#    if defined(RGB_MATRIX_ENABLE)
#        if defined(ENABLE_RGB_MATRIX_RAINDROPS)
        && (rgb_matrix_get_mode() != RGB_MATRIX_RAINDROPS)
#        endif
#        if defined(ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS)
        && (rgb_matrix_get_mode() != RGB_MATRIX_JELLYBEAN_RAINDROPS)
#        endif
#        if defined(ENABLE_RGB_MATRIX_PIXEL_RAIN)
        && (rgb_matrix_get_mode() != RGB_MATRIX_PIXEL_RAIN)
#        endif
#    endif
    ) {
        return res;
    }

    if (res) {
#    if defined(NUM_LOCK_INDEX)
        if (led_state.num_lock) {
            LED_MATRIX_SET_COLOR(NUM_LOCK_INDEX, COLOR_WHITE);
        } else {
            LED_MATRIX_SET_COLOR(NUM_LOCK_INDEX, COLOR_BLACK);
        }
#    endif // NUM_LOCK_INDEX
#    if defined(CAPS_LOCK_INDEX)
        if (led_state.caps_lock) {
            LED_MATRIX_SET_COLOR(CAPS_LOCK_INDEX, COLOR_WHITE);
        } else {
            LED_MATRIX_SET_COLOR(CAPS_LOCK_INDEX, COLOR_BLACK);
        }
#    endif // CAPS_LOCK_INDEX

        LED_MATRIX_UPDATE_PWN_BUFFERS();
    }

    return res;
}

void housekeeping_task_kb(void) {
    if (!LED_MATRIX_IS_ENABLED()) {
#    if defined(MAC_OS_LED_INDEX)
        if (default_layer_state == (1 << 0)) {
            LED_MATRIX_SET_COLOR(MAC_OS_LED_INDEX, COLOR_WHITE);
        } else {
            LED_MATRIX_SET_COLOR(MAC_OS_LED_INDEX, COLOR_BLACK);
        }
#    endif // MAC_OS_LED_INDEX
#    if defined(WIN_OS_LED_INDEX)
        if (default_layer_state == (1 << 2)) {
            LED_MATRIX_SET_COLOR(WIN_OS_LED_INDEX, COLOR_WHITE);
        } else {
            LED_MATRIX_SET_COLOR(WIN_OS_LED_INDEX, COLOR_BLACK);
        }
#    endif // WIN_OS_LED_INDEX
        LED_MATRIX_UPDATE_PWN_BUFFERS();
    }
}

#endif
