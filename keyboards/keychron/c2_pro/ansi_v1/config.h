/* Copyright 2022 @ Keychron(https://www.keychron.com)
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

#pragma once

/* DIP switch */
#define DIP_SWITCH_MATRIX_GRID \
    {                          \
        { 5, 4 }               \
    }
#define SCAN_COUNT_MAX 100

/* Disable DIP switch in matrix data */
#define MATRIX_MASKED

/* Increase I2C speed to 1000 KHz */
#define I2C1_TIMINGR_PRESC 0U
#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 15U
#define I2C1_TIMINGR_SCLL 51U

/* Enable indicator LED*/
#define NUM_LED_INDEX 16
#define CAPS_LED_INDEX 17
#define MAC_LED_INDEX 18
#define WIN_LED_INDEX 19

/* HC595 driver definition */
#define HC595_STCP A0
#define HC595_SHCP A1
#define HC595_DS C15
#define SHIFT_COL_START 11
#define SHIFT_COL_END 19
