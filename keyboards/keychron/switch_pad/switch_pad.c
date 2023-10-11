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
const ckled2001_led PROGMEM g_ckled2001_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to CKLED2001 manual for these locations
 *   driver
 *   |  R location
 *   |  |     G location
 *   |  |     |     B location
 *   |  |     |     | */
    {0, I_1,  G_1,  H_1},
    {0, I_2,  G_2,  H_2},
    {0, I_3,  G_3,  H_3},
    {0, I_4,  G_4,  H_4},
    {0, I_5,  G_5,  H_5},
    {0, I_6,  G_6,  H_6},
    {0, I_7,  G_7,  H_7},
    {0, I_8,  G_8,  H_8},
    {0, I_9,  G_9,  H_9},
    {0, I_10, G_10, H_10},

    {0, I_11, G_11, H_11},
    {0, I_12, G_12, H_12},
    {0, I_13, G_13, H_13},
    {0, I_14, G_14, H_14},
    {0, I_15, G_15, H_15},
    {0, I_16, G_16, H_16},
    {1, L_6,  J_6,  K_6},
    {0, C_14, A_14, B_14},
    {0, C_15, A_15, B_15},
    {0, C_16, A_16, B_16},

    {0, C_1,  A_1,  B_1},
    {0, C_2,  A_2,  B_2},
    {0, C_3,  A_3,  B_3},
    {0, C_4,  A_4,  B_4},
    {0, C_5,  A_5,  B_5},
    {0, C_6,  A_6,  B_6},
    {0, C_7,  A_7,  B_7},
    {0, C_8,  A_8,  B_8},
    {0, C_9,  A_9,  B_9},
    {0, C_10, A_10, B_10},

    {0, C_11, A_11, B_11},
    {0, C_12, A_12, B_12},
    {0, C_13, A_13, B_13},
    {0, F_14, D_14, E_14},
    {0, F_15, D_15, E_15},
    {0, F_16, D_16, E_16},
    {0, F_11, D_11, E_11},
    {0, F_12, D_12, E_12},
    {0, F_13, D_13, E_13},
    {0, F_10, D_10, E_10},

    {0, F_1,  D_1,  E_1},
    {0, F_2,  D_2,  E_2},
    {0, F_3,  D_3,  E_3},
    {0, F_4,  D_4,  E_4},
    {0, F_5,  D_5,  E_5},
    {0, F_6,  D_6,  E_6},
    {0, F_7,  D_7,  E_7},
    {0, F_8,  D_8,  E_8},
    {0, F_9,  D_9,  E_9},
    {1, L_7,  J_7,  K_7},

    {1, I_1,  G_1,  H_1},
    {1, I_2,  G_2,  H_2},
    {1, I_3,  G_3,  H_3},
    {1, I_4,  G_4,  H_4},
    {1, I_5,  G_5,  H_5},
    {1, I_6,  G_6,  H_6},
    {1, I_7,  G_7,  H_7},
    {1, I_8,  G_8,  H_8},
    {1, I_9,  G_9,  H_9},
    {1, I_10, G_10, H_10},

    {1, I_11, G_11, H_11},
    {1, I_12, G_12, H_12},
    {1, I_13, G_13, H_13},
    {1, I_14, G_14, H_14},
    {1, I_15, G_15, H_15},
    {1, I_16, G_16, H_16},
    {1, L_8,  J_8,  K_8},
    {1, C_14, A_14, B_14},
    {1, C_15, A_15, B_15},
    {1, C_16, A_16, B_16},

    {1, C_1,  A_1,  B_1},
    {1, C_2,  A_2,  B_2},
    {1, C_3,  A_3,  B_3},
    {1, C_4,  A_4,  B_4},
    {1, C_5,  A_5,  B_5},
    {1, C_6,  A_6,  B_6},
    {1, C_7,  A_7,  B_7},
    {1, C_8,  A_8,  B_8},
    {1, C_9,  A_9,  B_9},
    {1, C_10, A_10, B_10},

    {1, C_11, A_11, B_11},
    {1, C_12, A_12, B_12},
    {1, C_13, A_13, B_13},
    {1, F_14, D_14, E_14},
    {1, F_15, D_15, E_15},
    {1, F_16, D_16, E_16},
    {1, F_11, D_11, E_11},
    {1, F_12, D_12, E_12},
    {1, F_13, D_13, E_13},
    {1, F_10, D_10, E_10},

    {1, F_1,  D_1,  E_1},
    {1, F_2,  D_2,  E_2},
    {1, F_3,  D_3,  E_3},
    {1, F_4,  D_4,  E_4},
    {1, F_5,  D_5,  E_5},
    {1, F_6,  D_6,  E_6},
    {1, F_7,  D_7,  E_7},
    {1, F_8,  D_8,  E_8},
    {1, F_9,  D_9,  E_9},
    {1, L_9,  J_9,  K_9},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
		{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16 },
        { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 17, 18, 19, __ },
        { 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 36, 37, 38, 33, 34, 35, 39 },
        { 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66 },
        { 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 67, 68, 69, __ },
        { 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 86, 87, 88, 83, 84, 85, 89 },
    },
    {
        {0,0},  {25,0},  {50,0},  {75,0},   {100,0},  {124,0},  {149,0},  {174,0},  {199,0},  {224,0},
        {0,7},  {25,7},  {50,7},  {75,7},   {100,7},  {124,7},  {149,7},  {174,7},  {199,7},  {224,7},
        {0,14}, {25,14}, {50,14}, {75,14},  {100,14}, {124,14}, {149,14}, {174,14}, {199,14}, {224,14},
        {0,21}, {25,21}, {50,21}, {75,21},  {100,21}, {124,21}, {149,21}, {174,21}, {199,21}, {224,21},
        {0,28}, {25,28}, {50,28}, {75,28},  {100,28}, {124,28}, {149,28}, {174,28}, {199,28}, {224,28},
        {0,36}, {25,36}, {50,36}, {75,36},  {100,36}, {124,36}, {149,36}, {174,36}, {199,36}, {224,36},
        {0,43}, {25,43}, {50,43}, {75,43},  {100,43}, {124,43}, {149,43}, {174,43}, {199,43}, {224,43},
        {0,50}, {25,50}, {50,50}, {75,50},  {100,50}, {124,50}, {149,50}, {174,50}, {199,50}, {224,50},
        {0,57}, {25,57}, {50,57}, {75,57},  {100,57}, {124,57}, {149,57}, {174,57}, {199,57}, {224,57},
        {0,64}, {25,64}, {50,64}, {75,64},  {100,64}, {124,64}, {149,64}, {174,64}, {199,64}, {224,64},
    },
	{
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
    }
};
#endif

// clang-format on
uint8_t row1 = 1;
uint8_t row2 = 2;
uint8_t row3 = 4;
uint8_t col  = 9;

uint8_t  key_press_status     = 0;
uint8_t  factory_reset_count  = 0;
uint32_t factory_reset_buffer = 0;
uint32_t indicator_buffer     = 0;

#define KEY_PRESS_STEP_0 (0x1 << 0)
#define KEY_PRESS_STEP_1 (0x1 << 1)
#define KEY_PRESS_STEP_2 (0x1 << 2)
#define KEY_PRESS_STEP_3 (0x1 << 3)
#define KEY_PRESS_STEP_4 (0x1 << 4)
#define KEY_PRESS_FACTORY_RESET (KEY_PRESS_STEP_0 | KEY_PRESS_STEP_1)
#define KEY_PRESS_LIGHT_TEST (KEY_PRESS_STEP_2 | KEY_PRESS_STEP_3 | KEY_PRESS_STEP_4)

enum {
    LED_TEST_MODE_OFF,
    LED_TEST_MODE_WHITE,
    LED_TEST_MODE_RED,
    LED_TEST_MODE_GREEN,
    LED_TEST_MODE_BLUE,
    LED_TEST_MODE_MAX,
} led_test_mode;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case RGB_MOD:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_STEP_0;
                if (key_press_status == KEY_PRESS_FACTORY_RESET) {
                    factory_reset_buffer = timer_read32();
                }
            } else {
                rgb_matrix_step();
                key_press_status &= ~KEY_PRESS_STEP_0;
                factory_reset_buffer = 0;
            }
            return false;
        case RGB_RMOD:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_STEP_1;
                if (key_press_status == KEY_PRESS_FACTORY_RESET) {
                    factory_reset_buffer = timer_read32();
                }
            } else {
                rgb_matrix_step_reverse();
                key_press_status &= ~KEY_PRESS_STEP_1;
                factory_reset_buffer = 0;
            }
            return false;
        case KC_P9:
            if (record->event.pressed) {
                if (matrix_get_row(row1) & (1 << col)) {
                    key_press_status |= KEY_PRESS_STEP_2;
                }
                if (matrix_get_row(row2) & (1 << col)) {
                    key_press_status |= KEY_PRESS_STEP_3;
                    if (led_test_mode) {
                        if (++led_test_mode >= LED_TEST_MODE_MAX) {
                            led_test_mode = LED_TEST_MODE_WHITE;
                        }
                    }
                }
                if (matrix_get_row(row3) & (1 << col)) {
                    key_press_status |= KEY_PRESS_STEP_4;
                    if (led_test_mode) {
                        led_test_mode = LED_TEST_MODE_OFF;
                    }
                }
                if (key_press_status == KEY_PRESS_LIGHT_TEST) {
                    factory_reset_buffer = timer_read32();
                }
            } else {
                if (matrix_get_row(row1) & (1 << col)) {
                    key_press_status &= ~KEY_PRESS_STEP_2;
                }
                if (matrix_get_row(row2) & (1 << col)) {
                    key_press_status &= ~KEY_PRESS_STEP_3;
                }
                if (matrix_get_row(row3) & (1 << col)) {
                    key_press_status &= ~KEY_PRESS_STEP_4;
                }
                factory_reset_buffer = 0;
            }
            return true;
    }

    return true;
}

void housekeeping_task_kb(void) {
    if (factory_reset_buffer && (timer_elapsed32(factory_reset_buffer) > 4000)) {
        factory_reset_buffer = 0;
        if (key_press_status == KEY_PRESS_FACTORY_RESET) {
            indicator_buffer = timer_read32();
            factory_reset_count++;
            eeconfig_init();
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_enable();
            }
            rgb_matrix_init();
        } else if (key_press_status == KEY_PRESS_LIGHT_TEST) {
            led_test_mode = LED_TEST_MODE_WHITE;
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_enable();
            }
        }
        key_press_status = 0;
    }

    if (indicator_buffer && (timer_elapsed32(indicator_buffer) > 300)) {
        if (factory_reset_count++ > 6) {
            indicator_buffer    = 0;
            factory_reset_count = 0;
        } else {
            indicator_buffer = timer_read32();
        }
    }
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (factory_reset_count) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            rgb_matrix_set_color(i, factory_reset_count % 2 ? 0 : RGB_RED);
        }
    }

    if (led_test_mode) {
        switch (led_test_mode) {
            case LED_TEST_MODE_WHITE:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, RGB_WHITE);
                }
                break;
            case LED_TEST_MODE_RED:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, RGB_RED);
                }
                break;
            case LED_TEST_MODE_GREEN:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, RGB_GREEN);
                }
                break;
            case LED_TEST_MODE_BLUE:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, RGB_BLUE);
                }
                break;
            default:
                break;
        }
    }
    return true;
}
