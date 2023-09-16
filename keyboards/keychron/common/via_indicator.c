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

#if defined(RGB_MATRIX_ENABLE)
#    if defined(CAPS_LOCK_INDEX) || defined(NUM_LOCK_INDEX)

enum via_capslock_value {
    id_capslock_brightness = 1,
    id_capslock_status     = 2,
    id_capslock_color      = 3,
    id_numlock_brightness  = 4,
    id_numlock_status      = 5,
    id_numlock_color       = 6,
};

typedef struct {
    HSV  hsv;
    bool status;
} g_capslock_control;
typedef struct {
    HSV  hsv;
    bool status;
} g_numlock_control;
struct {
    g_capslock_control caps;
    g_numlock_control  num;
} g_indicator_control;

void keyboard_post_init_user() {
    eeconfig_read_user_datablock(&g_indicator_control);
}

void eeconfig_init_kb(void) {
#        if (EECONFIG_KB_DATA_SIZE) == 0
    // Reset Keyboard EEPROM value to blank, rather than to a set value
    eeconfig_update_kb(0);
#        endif
    g_indicator_control.caps.hsv.h  = 255;
    g_indicator_control.caps.hsv.s  = 0;
    g_indicator_control.caps.hsv.v  = 255;
    g_indicator_control.caps.status = true;
    g_indicator_control.num.hsv.h   = 255;
    g_indicator_control.num.hsv.s   = 0;
    g_indicator_control.num.hsv.v   = 255;
    g_indicator_control.num.status  = true;
    eeconfig_update_user_datablock(&g_indicator_control);

    eeconfig_init_user();
}

bool rgb_matrix_indicators_kb(void) {
#        if defined(CAPS_LOCK_INDEX)
    if (host_keyboard_led_state().caps_lock && g_indicator_control.caps.status) {
        RGB rgb = hsv_to_rgb(g_indicator_control.caps.hsv);
#            if defined(DIM_CAPS_LOCK)
        rgb_matrix_set_color(CAPS_LOCK_INDEX, 0, 0, 0);
#            else
        rgb_matrix_set_color(CAPS_LOCK_INDEX, rgb.r, rgb.g, rgb.b);
#            endif
    }
#        endif
#        if defined(NUM_LOCK_INDEX)
    if (host_keyboard_led_state().num_lock && g_indicator_control.num.status) {
        RGB rgb = hsv_to_rgb(g_indicator_control.num.hsv);
        rgb_matrix_set_color(NUM_LOCK_INDEX, rgb.r, rgb.g, rgb.b);
    }
#        endif
    return true;
}

void rgb_matrix_none_indicators_kb(void) {
    rgb_matrix_indicators_kb();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);

    if (rgb_matrix_is_enabled()
#        if defined(ENABLE_RGB_MATRIX_RAINDROPS)
        && (rgb_matrix_get_mode() != RGB_MATRIX_RAINDROPS)
#        endif
#        if defined(ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS)
        && (rgb_matrix_get_mode() != RGB_MATRIX_JELLYBEAN_RAINDROPS)
#        endif
#        if defined(ENABLE_RGB_MATRIX_PIXEL_RAIN)
        && (rgb_matrix_get_mode() != RGB_MATRIX_PIXEL_RAIN)
#        endif
    ) {
        return res;
    }

    if (res) {
#        if defined(CAPS_LOCK_INDEX)
        if (led_state.caps_lock) {
            RGB rgb = hsv_to_rgb(g_indicator_control.caps.hsv);
            rgb_matrix_set_color(CAPS_LOCK_INDEX, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(CAPS_LOCK_INDEX, 0, 0, 0);
        }
#        endif
#        if defined(NUM_LOCK_INDEX)
        if (led_state.num_lock) {
            RGB rgb = hsv_to_rgb(g_indicator_control.caps.hsv);
            rgb_matrix_set_color(NUM_LOCK_INDEX, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(NUM_LOCK_INDEX, 0, 0, 0);
        }
#        endif
        rgb_matrix_driver.flush();
    }
    return res;
}

void indicator_config_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_capslock_brightness: {
            g_indicator_control.caps.hsv.v = *value_data;
            break;
        }
        case id_capslock_status: {
            g_indicator_control.caps.status = *value_data;
            break;
        }
        case id_capslock_color: {
            g_indicator_control.caps.hsv.h = value_data[0];
            g_indicator_control.caps.hsv.s = value_data[1];
            break;
        }
        case id_numlock_brightness: {
            g_indicator_control.num.hsv.v = *value_data;
            break;
        }
        case id_numlock_status: {
            g_indicator_control.num.status = *value_data;
            break;
        }
        case id_numlock_color: {
            g_indicator_control.num.hsv.h = value_data[0];
            g_indicator_control.num.hsv.s = value_data[1];
            break;
        }
    }
}

void indicator_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_capslock_brightness: {
            *value_data = g_indicator_control.caps.hsv.v;
            break;
        }
        case id_capslock_status: {
            *value_data = g_indicator_control.caps.status;
            break;
        }
        case id_capslock_color: {
            value_data[0] = g_indicator_control.caps.hsv.h;
            value_data[1] = g_indicator_control.caps.hsv.s;
            break;
        }
        case id_numlock_brightness: {
            *value_data = g_indicator_control.num.hsv.v;
            break;
        }
        case id_numlock_status: {
            *value_data = g_indicator_control.num.status;
            break;
        }
        case id_numlock_color: {
            value_data[0] = g_indicator_control.num.hsv.h;
            value_data[1] = g_indicator_control.num.hsv.s;
            break;
        }
    }
}

void indicator_config_save(void) {
    eeconfig_update_user_datablock(&g_indicator_control);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                indicator_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                indicator_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                indicator_config_save();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}

#    endif
#endif
