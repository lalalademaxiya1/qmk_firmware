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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.g
 */

#include "quantum.h"

// clang-format off
#ifdef LED_MATRIX_ENABLE
const ckled2001_led g_ckled2001_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to CKLED2001 manual for these locations
 *   driver
 *   |  LED address
 *   |  | */
    {0, K_1},
    {0, K_2},
    {0, K_3},
    {0, K_4},
    {0, K_5},
    {0, K_6},
    {0, K_7},
    {0, K_8},
    {0, K_9},
    {0, K_10},
    {0, K_11},
    {0, K_12},
    {0, K_13},
    {0, K_14},

    {0, H_1},
    {0, H_2},
    {0, H_3},
    {0, H_4},
    {0, H_5},
    {0, H_6},
    {0, H_7},
    {0, H_8},
    {0, H_9},
    {0, H_10},
    {0, H_11},
    {0, H_12},
    {0, H_13},

    {0, E_1},
    {0, E_2},
    {0, E_3},
    {0, E_4},
    {0, E_5},
    {0, E_6},
    {0, E_7},
    {0, E_8},
    {0, E_9},
    {0, E_10},
    {0, E_11},
    {0, E_12},
    {0, E_14},
    {0, H_14},

    {0, B_1},
    {0, B_2},
    {0, B_3},
    {0, B_4},
    {0, B_5},
    {0, B_6},
    {0, B_7},
    {0, B_8},
    {0, B_9},
    {0, B_10},
    {0, B_11},
    {0, B_12},
    {0, B_14},

    {0, B_15},
    {0, B_16},
    {0, E_15},
    {0, E_16},
    {0, H_15},
    {0, H_16},
    {0, K_15},
    {0, K_16},
};
#endif
