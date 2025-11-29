/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
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

// #define SPLIT_TRANSACTION_IDS_USER RPC_ID_USER_HID_SYNC
#define SPLIT_TRANSACTION_IDS_USER RPC_ID_USER_HID_SYNC, RPC_ID_USER_CAPS_WORD_SYNC, RPC_ID_USER_LAYER_SYNC
// #define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0

#define ONESHOT_TAP_TOGGLE 2
#define TAPPING_TERM 180
#define QUICK_TAP_TERM 100
#define HOLD_ON_OTHER_KEY_PRESS
#define PERMISSIVE_HOLD

// #define RETRO_TAPPING

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE

#define SPLIT_ACTIVITY_ENABLE
#define SPLIT_OLED_ENABLE

#define RGB_MATRIX_SLEEP
#define RGB_MATRIX_TIMEOUT 600000
#define OLED_TIMEOUT 600000

#define RGB_TRIGGER_ON_KEYDOWN

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES  // or KEYRELEASES, if you want reactive effects

#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_RIVERFLOW
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE

