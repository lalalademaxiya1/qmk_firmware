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

#include QMK_KEYBOARD_H
#include "keychron_common.h"

bool     is_siri_active = false;
uint32_t siri_timer     = 0;
// clang-format off
key_combination_t key_comb_list[4] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}},
    {3, {KC_LSFT, KC_LCMD, KC_4}},
    {2, {KC_LWIN, KC_C}}
};

static uint8_t mac_keycode[4] = {KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD};
// clang-format on
void housekeeping_task_keychron(void) {
    if (is_siri_active) {
        if (sync_timer_elapsed32(siri_timer) >= 500) {
            unregister_code(KC_LCMD);
            unregister_code(KC_SPACE);
            is_siri_active = false;
        }
    }
}

bool process_record_keychron(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_KB_0:
            if (record->event.pressed) {
                register_code(KC_MISSION_CONTROL);
            } else {
                unregister_code(KC_MISSION_CONTROL);
            }
            return false; // Skip all further processing of this key
        case QK_KB_1:
            if (record->event.pressed) {
                register_code(KC_LAUNCHPAD);
            } else {
                unregister_code(KC_LAUNCHPAD);
            }
            return false; // Skip all further processing of this key
        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false; // Skip all further processing of this key
        case KC_SIRI:
            if (record->event.pressed) {
                if (!is_siri_active) {
                    is_siri_active = true;
                    register_code(KC_LCMD);
                    register_code(KC_SPACE);
                }
                siri_timer = sync_timer_read32();
            } else {
                // Do something else when release
            }
            return false; // Skip all further processing of this key
        case KC_TASK:
        case KC_FLXP:
        case KC_SNAP:
        case KC_CRTA:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    register_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            } else {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    unregister_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            }
            return false; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}

#if defined(RGB_MATRIX_ENABLE) && (defined(CAPS_LOCK_LED_INDEX) || defined(NUM_LOCK_LED_INDEX))

#    define CAPS_NUM_LOCK_MAX_BRIGHTNESS 0xFF
#    ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#        undef CAPS_NUM_LOCK_MAX_BRIGHTNESS
#        define CAPS_NUM_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    endif

#    define CAPS_NUM_LOCK_VAL_STEP 8
#    ifdef RGB_MATRIX_VAL_STEP
#        undef CAPS_NUM_LOCK_VAL_STEP
#        define CAPS_NUM_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
#    endif

extern void rgb_matrix_update_pwm_buffers(void);

static uint8_t light_brightness_get(void) {
    uint8_t value = rgb_matrix_get_val();
    if (value < CAPS_NUM_LOCK_VAL_STEP) {
        value = CAPS_NUM_LOCK_VAL_STEP;
    } else if (value < (CAPS_NUM_LOCK_MAX_BRIGHTNESS - CAPS_NUM_LOCK_VAL_STEP)) {
        value += CAPS_NUM_LOCK_VAL_STEP; // one step more than current brightness
    } else {
        value = CAPS_NUM_LOCK_MAX_BRIGHTNESS;
    }
    return value;
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
#    if defined(CAPS_LOCK_LED_INDEX)
    if (host_keyboard_led_state().caps_lock) {
        uint8_t v = light_brightness_get();
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, v, v, v); // white, with the adjusted brightness
    }
#    endif
#    if defined(NUM_LOCK_LED_INDEX)
    if (host_keyboard_led_state().num_lock) {
        uint8_t v = light_brightness_get();
        rgb_matrix_set_color(NUM_LOCK_LED_INDEX, v, v, v); // white, with the adjusted brightness
    }
#    endif
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
#    if defined(CAPS_LOCK_LED_INDEX)
        if (led_state.caps_lock) {
            uint8_t v = light_brightness_get();
            rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, v, v, v);
        } else {
            rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, 0, 0, 0);
        }
#    endif
#    if defined(NUM_LOCK_LED_INDEX)
        if (led_state.num_lock) {
            uint8_t v = light_brightness_get();
            rgb_matrix_set_color(NUM_LOCK_LED_INDEX, v, v, v);
        } else {
            rgb_matrix_set_color(NUM_LOCK_LED_INDEX, 0, 0, 0);
        }
#    endif
        rgb_matrix_update_pwm_buffers();
    }
    return res;
}

#endif

#if defined(ENCODER_ENABLE) && defined(PAL_USE_CALLBACKS)
static void encoder_pad_cb(void *param) {
    encoder_interrupt_read((uint32_t)param & 0XFF);
}

__attribute__((weak)) void keyboard_post_init_kb(void) {
    pin_t encoders_pad_a[NUM_ENCODERS] = ENCODERS_PAD_A;
    pin_t encoders_pad_b[NUM_ENCODERS] = ENCODERS_PAD_B;
    for (uint32_t i = 0; i < NUM_ENCODERS; i++) {
        palEnableLineEvent(encoders_pad_a[i], PAL_EVENT_MODE_BOTH_EDGES);
        palEnableLineEvent(encoders_pad_b[i], PAL_EVENT_MODE_BOTH_EDGES);
        palSetLineCallback(encoders_pad_a[i], encoder_pad_cb, (void *)i);
        palSetLineCallback(encoders_pad_b[i], encoder_pad_cb, (void *)i);
    }
}
#endif
