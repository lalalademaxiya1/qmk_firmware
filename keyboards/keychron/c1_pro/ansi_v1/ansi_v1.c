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
    0b1111111111111111,
    0b1111111111111111,
    0b1111111111111111,
    0b1111111111111111,
    0b1111111111111111,
    0b1111111111101111,
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

#if defined(RGB_MATRIX_ENABLE) && defined(CAPS_MAC_WIN_LOCK_LED_INDEX)

extern void rgb_matrix_update_pwm_buffers(void);

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if ((host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 0))) {
        rgb_matrix_set_color(CAPS_MAC_WIN_LOCK_LED_INDEX, 0, 255, 255);
    } else if ((!host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 0))) {
        rgb_matrix_set_color(CAPS_MAC_WIN_LOCK_LED_INDEX, 0, 0, 255);
    } else if ((host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 2))) {
        rgb_matrix_set_color(CAPS_MAC_WIN_LOCK_LED_INDEX, 255, 255, 0);
    } else if ((!host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 2))) {
        rgb_matrix_set_color(CAPS_MAC_WIN_LOCK_LED_INDEX, 255, 0, 0);
    }
    return true;
}

void rgb_matrix_indicators_none_kb(void) {
    rgb_matrix_indicators_kb();
    rgb_matrix_update_pwm_buffers();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);

    if (rgb_matrix_is_enabled()
#    if defined(ENABLE_RGB_MATRIX_RAINDROPS)
        && (rgb_matrix_get_mode() != RGB_MATRIX_RAINDROPS)
#    endif
#    if defined(ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS)
        && (rgb_matrix_get_mode() != RGB_MATRIX_JELLYBEAN_RAINDROPS)
#    endif
#    if defined(ENABLE_RGB_MATRIX_PIXEL_RAIN)
        && (rgb_matrix_get_mode() != RGB_MATRIX_PIXEL_RAIN)
#    endif
    ) {
        return res;
    }

    if (res) {
#    if defined(CAPS_MAC_WIN_LOCK_LED_INDEX)
        if ((led_state.caps_lock) && (default_layer_state == (1 << 0))) {
            rgb_matrix_set_color(CAPS_MAC_WIN_LOCK_LED_INDEX, 0, 255, 255);
        } else if ((!led_state.caps_lock) && (default_layer_state == (1 << 0))) {
            rgb_matrix_set_color(CAPS_MAC_WIN_LOCK_LED_INDEX, 0, 0, 255);
        } else if ((led_state.caps_lock) && (default_layer_state == (1 << 2))) {
            rgb_matrix_set_color(CAPS_MAC_WIN_LOCK_LED_INDEX, 255, 255, 0);
        } else if ((!led_state.caps_lock) && (default_layer_state == (1 << 2))) {
            rgb_matrix_set_color(CAPS_MAC_WIN_LOCK_LED_INDEX, 255, 0, 0);
        }
#    endif
        rgb_matrix_update_pwm_buffers();
    }

    return res;
}

void housekeeping_task_kb(void) {
#    if defined(RGB_MATRIX_ENABLE) && defined(CAPS_MAC_WIN_LOCK_LED_INDEX)
    if (!rgb_matrix_is_enabled()) {
        if ((host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 0))) {
            rgb_matrix_set_color(CAPS_MAC_WIN_LOCK_LED_INDEX, 0, 255, 255);
        } else if ((!host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 0))) {
            rgb_matrix_set_color(CAPS_MAC_WIN_LOCK_LED_INDEX, 0, 0, 255);
        } else if ((host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 2))) {
            rgb_matrix_set_color(CAPS_MAC_WIN_LOCK_LED_INDEX, 255, 255, 0);
        } else if ((!host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 2))) {
            rgb_matrix_set_color(CAPS_MAC_WIN_LOCK_LED_INDEX, 255, 0, 0);
        }
        rgb_matrix_update_pwm_buffers();
    }
#    endif
}

#endif

#if defined(LED_MATRIX_ENABLE) && defined(CAPS_LOCK_LED_INDEX) && defined(MAC_LOCK_LED_INDEX) && defined(WIN_LOCK_LED_INDEX)

extern void led_matrix_update_pwm_buffers(void);

bool led_matrix_indicators_kb(void) {
    if (!led_matrix_indicators_user()) {
        return false;
    }
    if ((host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 0))) {
        led_matrix_set_value(CAPS_LOCK_LED_INDEX, 255);
        led_matrix_set_value(MAC_LOCK_LED_INDEX, 255);
        led_matrix_set_value(WIN_LOCK_LED_INDEX, 0);
    } else if ((!host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 0))) {
        led_matrix_set_value(CAPS_LOCK_LED_INDEX, 0);
        led_matrix_set_value(MAC_LOCK_LED_INDEX, 255);
        led_matrix_set_value(WIN_LOCK_LED_INDEX, 0);
    } else if ((host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 2))) {
        led_matrix_set_value(CAPS_LOCK_LED_INDEX, 255);
        led_matrix_set_value(MAC_LOCK_LED_INDEX, 0);
        led_matrix_set_value(WIN_LOCK_LED_INDEX, 255);
    } else if ((!host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 2))) {
        led_matrix_set_value(CAPS_LOCK_LED_INDEX, 0);
        led_matrix_set_value(MAC_LOCK_LED_INDEX, 0);
        led_matrix_set_value(WIN_LOCK_LED_INDEX, 255);
    }
    return true;
}

void led_matrix_indicators_none_kb(void) {
    led_matrix_indicators_kb();
    led_matrix_update_pwm_buffers();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);

    if (res) {
#    if defined(CAPS_LOCK_LED_INDEX) && defined(MAC_LOCK_LED_INDEX) && defined(WIN_LOCK_LED_INDEX)
        if ((host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 0))) {
            led_matrix_set_value(CAPS_LOCK_LED_INDEX, 255);
            led_matrix_set_value(MAC_LOCK_LED_INDEX, 255);
            led_matrix_set_value(WIN_LOCK_LED_INDEX, 0);
        } else if ((!host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 0))) {
            led_matrix_set_value(CAPS_LOCK_LED_INDEX, 0);
            led_matrix_set_value(MAC_LOCK_LED_INDEX, 255);
            led_matrix_set_value(WIN_LOCK_LED_INDEX, 0);
        } else if ((host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 2))) {
            led_matrix_set_value(CAPS_LOCK_LED_INDEX, 255);
            led_matrix_set_value(MAC_LOCK_LED_INDEX, 0);
            led_matrix_set_value(WIN_LOCK_LED_INDEX, 255);
        } else if ((!host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 2))) {
            led_matrix_set_value(CAPS_LOCK_LED_INDEX, 0);
            led_matrix_set_value(MAC_LOCK_LED_INDEX, 0);
            led_matrix_set_value(WIN_LOCK_LED_INDEX, 255);
        }
        led_matrix_update_pwm_buffers();
#    endif
    }

    return res;
}

void housekeeping_task_kb(void) {
#    if defined(LED_MATRIX_ENABLE) && defined(CAPS_LOCK_LED_INDEX) && defined(MAC_LOCK_LED_INDEX) && defined(WIN_LOCK_LED_INDEX)
    if (!led_matrix_is_enabled()) {
        if ((host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 0))) {
            led_matrix_set_value(CAPS_LOCK_LED_INDEX, 255);
            led_matrix_set_value(MAC_LOCK_LED_INDEX, 255);
            led_matrix_set_value(WIN_LOCK_LED_INDEX, 0);
        } else if ((!host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 0))) {
            led_matrix_set_value(CAPS_LOCK_LED_INDEX, 0);
            led_matrix_set_value(MAC_LOCK_LED_INDEX, 255);
            led_matrix_set_value(WIN_LOCK_LED_INDEX, 0);
        } else if ((host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 2))) {
            led_matrix_set_value(CAPS_LOCK_LED_INDEX, 255);
            led_matrix_set_value(MAC_LOCK_LED_INDEX, 0);
            led_matrix_set_value(WIN_LOCK_LED_INDEX, 255);
        } else if ((!host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 2))) {
            led_matrix_set_value(CAPS_LOCK_LED_INDEX, 0);
            led_matrix_set_value(MAC_LOCK_LED_INDEX, 0);
            led_matrix_set_value(WIN_LOCK_LED_INDEX, 255);
        }
        led_matrix_update_pwm_buffers();
    }
#    endif
}

#endif
