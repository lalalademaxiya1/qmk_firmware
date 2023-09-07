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

// clang-format off
#ifdef RGB_MATRIX_ENABLE
const ckled2001_led g_ckled2001_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to CKLED manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
   {0, I_1,    G_1,     H_1},
   {0, I_2,    G_2,     H_2},
   {0, I_3,    G_3,     H_3},
   {0, I_4,    G_4,     H_4},
   {0, I_5,    G_5,     H_5},
   {0, I_6,    G_6,     H_6},
   {0, I_7,    G_7,     H_7},
   {0, I_8,    G_8,     H_8},
   {0, I_9,    G_9,     H_9},
   {0, I_10,   G_10,    H_10},
   {0, I_11,   G_11,    H_11},
   {0, I_12,   G_12,    H_12},
   {0, I_13,   G_13,    H_13},
   {0, I_14,   G_14,    H_14},
   {0, I_16,   G_16,    H_16},

   {0, C_1,    A_1,     B_1},
   {0, C_2,    A_2,     B_2},
   {0, C_3,    A_3,     B_3},
   {0, C_4,    A_4,     B_4},
   {0, C_5,    A_5,     B_5},
   {0, C_6,    A_6,     B_6},
   {0, C_7,    A_7,     B_7},
   {0, C_8,    A_8,     B_8},
   {0, C_9,    A_9,     B_9},
   {0, C_10,   A_10,    B_10},
   {0, C_11,   A_11,    B_11},
   {0, C_12,   A_12,    B_12},
   {0, C_13,   A_13,    B_13},
   {0, C_14,   A_14,    B_14},
   {0, C_16,   A_16,    B_16},

   {0, F_1,    D_1,     E_1},
   {0, F_2,    D_2,     E_2},
   {0, F_3,    D_3,     E_3},
   {0, F_4,    D_4,     E_4},
   {0, F_5,    D_5,     E_5},
   {0, F_6,    D_6,     E_6},
   {0, F_7,    D_7,     E_7},
   {0, F_8,    D_8,     E_8},
   {0, F_9,    D_9,     E_9},
   {0, F_10,   D_10,    E_10},
   {0, F_11,   D_11,    E_11},
   {0, F_12,   D_12,    E_12},
   {0, F_13,   D_13,    E_13},
   {0, F_14,   D_14,    E_14},
   {0, F_16,   D_16,    E_16},

   {1, C_16,   A_16,    B_16},
   {1, C_15,   A_15,    B_15},
   {1, C_14,   A_14,    B_14},
   {1, C_13,   A_13,    B_13},
   {1, C_12,   A_12,    B_12},
   {1, C_11,   A_11,    B_11},
   {1, C_10,   A_10,    B_10},
   {1, C_9,    A_9,     B_9},
   {1, C_8,    A_8,     B_8},
   {1, C_7,    A_7,     B_7},
   {1, C_6,    A_6,     B_6},
   {1, C_5,    A_5,     B_5},
   {1, C_3,    A_3,     B_3},
   {1, C_1,    A_1,     B_1},

   {1, I_16,   G_16,    H_16},
   {1, I_14,   G_14,    H_14},
   {1, I_13,   G_13,    H_13},
   {1, I_12,   G_12,    H_12},
   {1, I_11,   G_11,    H_11},
   {1, I_10,   G_10,    H_10},
   {1, I_9,    G_9,     H_9},
   {1, I_8,    G_8,     H_8},
   {1, I_7,    G_7,     H_7},
   {1, I_6,    G_6,     H_6},
   {1, I_5,    G_5,     H_5},
   {1, I_3,    G_3,     H_3},
   {1, I_2,    G_2,     H_2},

   {1, F_16,   D_16,    E_16},
   {1, F_15,   D_15,    E_15},
   {1, F_14,   D_14,    E_14},
   {1, F_10,   D_10,    E_10},
   {1, F_6,    D_6,     E_6},
   {1, F_5,    D_5,     E_5},
   {1, F_4,    D_4,     E_4},
   {1, F_3,    D_3,     E_3},
   {1, F_2,    D_2,     E_2},
   {1, F_1,    D_1,     E_1}
};

led_config_t g_led_config = {
    {
        { 0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13,     NO_LED, 14 },
        { 15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     NO_LED, 29 },
        { 30,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42,     43,     NO_LED, 44 },
        { 45,     46,     47,     48,     49,     50,     51,     52,     53,     54,     55,     56,     NO_LED, 57,     NO_LED, 58 },
        { 59,     NO_LED, 60,     61,     62,     63,     64,     65,     66,     67,     68,     69,     NO_LED, 70,     71,     NO_LED },
        { 72,     73,     74,     NO_LED, NO_LED, NO_LED, 75,     NO_LED, NO_LED, NO_LED, 76,     77,     78,     79,     80,     81 }
    },
    {
        {0, 0}, {18, 0}, {32, 0}, {47, 0}, {62, 0}, {80, 0}, {95, 0}, {109,  0}, {124,  0}, {142,  0}, {157,  0}, {172,  0}, {186,  0}, {205,  0},            {223,  0},
        {0,14}, {14,14}, {29,14}, {43,14}, {58,14}, {73,14}, {87,14}, {102, 14}, {117, 14}, {131, 14}, {146, 14}, {161, 14}, {175, 14}, {197, 14},            {224, 14},
        {3,26}, {21,26}, {36,26}, {51,26}, {65,26}, {80,26}, {95,26}, {109, 26}, {124, 26}, {139, 26}, {153, 26}, {168, 26}, {183, 26}, {201, 26},            {224, 26},
        {5,37}, {25,37}, {40,37}, {54,37}, {69,37}, {84,37}, {98,37}, {113, 37}, {128, 37}, {142, 37}, {157, 37}, {172, 37},            {195, 37},            {224, 37},
        {9,50},          {32,50}, {47,50}, {62,50}, {76,50}, {91,50}, {106, 50}, {120, 50}, {135, 50}, {150, 50}, {164, 50},            {185, 50}, {209, 50},
        {1,62}, {20,62}, {38,62},                            {93,62},                                  {146, 62}, {161, 62}, {176, 62}, {194, 62}, {209, 62}, {224, 62}

    },
    {
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,        4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,        4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,        4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,        4,        4,
        4,        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,        4,   4,
        4,   4,   4,                  4,                  4,   4,   4,   4,   4,   4
    }
};
#endif

// clang-format on

enum via_capslock_value {
    id_capslock_brightness = 1,
    id_capslock_status     = 2,
    id_capslock_color      = 3,
};

struct {
    HSV hsv;
    // uint8_t brightness;
    bool status;
} g_capslock_control;

void keyboard_post_init_user() {
    eeconfig_read_user_datablock(&g_capslock_control);
}

void eeconfig_init_kb(void) {
#if (EECONFIG_KB_DATA_SIZE) == 0
    // Reset Keyboard EEPROM value to blank, rather than to a set value
    eeconfig_update_kb(0);
#endif
    g_capslock_control.brightness = 255;
    g_capslock_control.status     = true;
    g_capslock_control.color      = true;
    eeconfig_update_user_datablock(&g_capslock_control);

    eeconfig_init_user();
}

void os_state_indicate(void) {
#if defined(CAPS_LOCK_INDEX)
    if (host_keyboard_led_state().caps_lock && g_capslock_control.status) {
#    if defined(DIM_CAPS_LOCK)
        rgb_matrix_set_color(CAPS_LOCK_INDEX, 0, 0, 0);
#    else
        rgb_matrix_set_color(CAPS_LOCK_INDEX, g_capslock_control.brightness, g_capslock_control.brightness, g_capslock_control.brightness);
#    endif
    }
#endif
}

void capslock_config_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_capslock_brightness: {
            g_capslock_control.brightness = *value_data;
            break;
        }
        case id_capslock_status: {
            g_capslock_control.status = *value_data;
            break;
        }
    }
}

void capslock_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_capslock_brightness: {
            *value_data = g_capslock_control.brightness;
            break;
        }
        case id_capslock_status: {
            *value_data = g_capslock_control.status;
            break;
        }
    }
}

void capslock_config_save(void) {
    eeconfig_update_user_datablock(&g_capslock_control);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                capslock_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                capslock_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                capslock_config_save();
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
