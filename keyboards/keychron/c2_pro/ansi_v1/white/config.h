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

#pragma once

#ifdef LED_MATRIX_ENABLE
/* LED Matrix Driver Configuration */
#    define DRIVER_COUNT 1
#    define DRIVER_ADDR_1 0b1110100

/* RGB Matrix Configuration */
#    define LED_MATRIX_LED_COUNT 108

/* turn off effects when suspended */
#    define LED_DISABLE_WHEN_USB_SUSPENDED

/* Use the first 8 channels of led driver */
#    define PHASE_CHANNEL MSKPHASE_8CHANNEL

/* Set LED driver current */
#    define CKLED2001_CURRENT_TUNE \
        { 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0 }

// LED Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_led_matrix?id=led-matrix-effects
// #if defined(LED_MATRIX_KEYPRESSES) || defined(LED_MATRIX_KEYRELEASES)
#    define LED_MATRIX_KEYPRESSES
#    define LED_MATRIX_KEYRELEASES
#endif
