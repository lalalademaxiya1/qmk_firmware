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
#ifdef LED_MATRIX_ENABLE
const ckled2001_led PROGMEM g_ckled2001_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to CKLED2001 manual for these locations
 *   driver
 *   |  LED address
 *   |  |   */
    {0, A_16}, // esc
    {0, A_15}, // f1
    {0, A_14}, // f2
    {0, A_13}, // f3
    {0, A_12}, // f4
    {0, A_11}, // f5
    {0, A_10}, // f6
    {0, A_9},  // f7
    {0, A_8},  // f8
    {0, A_7},  // f9
    {0, A_6},  // f10
    {0, A_5},  // f11
    {0, A_4},  // f12
    {0, A_2},  // print
    {0, A_1},  // siri
    {0, G_1},  // light

    {0, B_16}, // ~
    {0, B_15}, // 1!
    {0, B_14}, // 2@
    {0, B_13}, // 3#
    {0, B_12}, // 4$
    {0, B_11}, // 5%
    {0, B_10}, // 6^
    {0, B_9},  // 7&
    {0, B_8},  // 8*
    {0, B_7},  // 9(
    {0, B_6},  // 0)
    {0, B_5},  // -_
    {0, B_4},  // =+
    {0, B_3},  // back space
    {0, B_2},  // INS
    {0, B_1},  // HOME
    {0, H_1},  // PGUP

    {0, C_16}, // tab
    {0, C_15}, // q
    {0, C_14}, // w
    {0, C_13}, // e
    {0, C_12}, // r
    {0, C_11}, // t
    {0, C_10}, // y
    {0, C_9},  // u
    {0, C_8},  // i
    {0, C_7},  // o
    {0, C_6},  // p
    {0, C_5},  // [{
    {0, C_4},  // ]}
    {0, C_3},  // \\|
    {0, C_2},  // DEL
    {0, C_1},  // END
    {0, G_6},  // PGDN

    {0, D_16}, // caps lock
    {0, D_15}, // a
    {0, D_14}, // s
    {0, D_13}, // d
    {0, D_12}, // f
    {0, D_11}, // g
    {0, D_10}, // h
    {0, D_9},  // j
    {0, D_8},  // k
    {0, D_7},  // l
    {0, D_6},  // ;:
    {0, D_5},  // '"
    {0, D_3},  // enter

    {0, H_7},  // CPAS
    {0, H_8},  // MAC
    {0, H_9},  // WIN

    {0, E_16}, // left shift
    {0, E_14}, // z
    {0, E_13}, // x
    {0, E_12}, // c
    {0, E_11}, // v
    {0, E_10}, // b
    {0, E_9},  // b
    {0, E_8},  // n
    {0, E_7},  // m
    {0, E_6},  // ,<
    {0, E_5},  // .>
    {0, E_3},  // right shift
    {0, E_1},  // up

    {0, F_16}, // left ctrl
    {0, F_15}, // left command
    {0, F_14}, // left option
    {0, F_10}, // space
    {0, F_6},  // right command
    {0, F_5},  // right option
    {0, F_4},  // right ctrl
    {0, F_3},  // Fn
    {0, F_2},  // left
    {0, F_1},  // down
    {0, G_13}, // right
};
#endif
