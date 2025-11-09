/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#include "default_keyboard.h"
#include "transactions.h"
#include "config.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "quantum.h"
#include "quantum/keycodes.h"
#include "keymap_swedish.h"
#include "print.h"

enum layers {
    _QWERTY,
    _QMOL,
    _QMOR,
    _COLEMAK_DH,
    _CMOL,
    _CMOR,
    _NUM,
    _SYM,
    _FUN,
    _NAV,
    _ADJ,
    _TRI,
    _BTN,
};

// Tap Dance Declarations
enum tapdance {
    TD_LBRC = 0,
    TD_RBRC,
    TD_Q
};

// Keycodes
enum custom_keycodes {
    CLBRC = SAFE_RANGE,
    CRBRC,
    CBPIP,
    CCLN
};


// Aliases for readability
#define QWE DF(_QWERTY)
#define COL DF(_COLEMAK_DH)

#define FKEYS MO(_FUN)
#define ADJ MO(_ADJ)
#define TRI MO(_TRI)
#define BTN MO(_BTN)

#define MLS(key) MT(MOD_LSFT, key)
#define MLC(key) MT(MOD_LCTL, key)
#define MLA(key) MT(MOD_LALT, key)
#define MLG(key) MT(MOD_LGUI, key)

#define MRS(key) MT(MOD_RSFT, key)
#define MRC(key) MT(MOD_RCTL, key)
#define MRA(key) MT(MOD_RALT, key)
#define MRG(key) MT(MOD_RGUI, key)

/* COMBO CODE NOT USED
 const uint16_t PROGMEM test_combo1[] = {KC_A, KC_B, COMBO_END};
 const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END};
 combo_t key_combos[] = {
 COMBO(test_combo1, KC_ESC)
 COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
 };
 */


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer: QWERTY
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |  Esc   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |Lsft/Tab|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |  :;  | Rshft/'|
     * |--------+------+------+------+------+------+---------------.  ,-----------+------+------+------+------+------+--------|
     * | LCTL   |   Z  |   X  |   C  |   V  |   B  | ({[  |CapsTogg|  |F-keys| )}]|   N  |   M  | ,  < | . >  | /?  | Rctl   |
     * `----------------------+------+------+------+------+--------|  |------+------+------+------+------+--------------------'
     *                        |Adjust| LGUI | Fun  | ModL | Nav    |  | Sym  | ModR | Num | RALT | RGUI |
     *                        |      |      | Esc  | Spce | Tab    |  | Entr | Bspc | Del |      |      |
     *                        `------------------------------------'  `---------------------------------'
     */
    [_QWERTY] = LAYOUT(
        KC_ESC,               KC_Q, KC_W, KC_E, KC_R, KC_T,                                                        KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_BSPC,
        MT(MOD_LSFT, KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G,                                                        KC_H, KC_J, KC_K,    KC_L,    KC_BSLS, MRS(KC_QUOT),
        KC_LCTL,              KC_Z, KC_X, KC_C, KC_V, KC_B, TD(TD_LBRC), CW_TOGG,                      FKEYS, TD(TD_RBRC), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RCTL,
                       ADJ, KC_LGUI, LT(_FUN, KC_ESC), LT(_QMOL, KC_SPC), LT(_NAV, KC_TAB), /**/ LT(_SYM, KC_ENT), LT(_QMOR, KC_BSPC), LT(_NUM, KC_DEL), KC_RALT, KC_RGUI
    ),

    /*
    * Mod L Layer
    *
    * ,-------------------------------------------.                              ,-------------------------------------------.
    * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
    * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    * |        | LGui | Alt  | Ctrl | Shft |      |                              |      |      |      |      |      |        |
    * |--------+------+------+------+------+------+-------------.  ,-------------,-------------------------------------------.
    * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        |      |      |      |    X |      |  |      |      |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    */
    [_QMOL] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                          _______, _______, _______, _______, _______, _______,
        _______, OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, _______,                                          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______
    ),


    /*
     * Mod R Layer
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |                              |      | Shft | Ctrl |  Alt |  GUI |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      | X    |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */

     [_QMOR] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                          _______, _______, _______, _______, _______, _______,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    _______,                                          _______, OS_RSFT, OS_RCTL, OS_RALT, OS_RGUI, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______
    ),

    /*
     * Base Layer: Colemak DH
     *
     * ,-------------------------------------------.                                ,-------------------------------------------.
     * |  Esc   |   Q  |   W  |   F  |   P  |   B  |                                |   J  |   L  |   U  |   Y  | ;  : |  Bksp  |
     * |--------+------+------+------+------+------|                                |------+------+------+------+------+--------|
     * |Ctrl/Esc|   A  |   R  |   S  |   T  |   G  |                                |   M  |   N  |   E  |   I  |   O  | Rshft/'|
     * |--------+------+------+------+------+------+---------------.  ,-------------+------+------+------+------+------+--------|
     * | LShift |   Z  |   X  |   C  |   D  |   V  | ({[  | CapsL  |  |F-keys| )}]  |   K  |   H  | ,  < | . >  | /  ? | Rctl   |
     * `----------------------+------+------+------+------+--------|  |------+------+------+------+------+----------------------'
     *                        |Adjust| LGUI | Fun  | ModL | Nav    |  | Sym  | ModR | Num | RALT | RGUI |
     *                        |      |      | Esc  | Spce | Tab    |  | Entr | Bspc | Del |      |      |
     *                        `------------------------------------'  `---------------------------------'
    */
    [_COLEMAK_DH] = LAYOUT(
        _______, KC_Q, KC_W, KC_F, KC_P, KC_B,                                                   KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN,  _______,
        _______, KC_A, KC_R, KC_S, KC_T, KC_G,                                                   KC_M, KC_N, KC_E,    KC_I,   KC_O,     _______,
        _______, KC_Z, KC_X, KC_C, KC_D, KC_V,  TD(TD_LBRC), KC_CAPS,        FKEYS, TD(TD_RBRC), KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH,  _______,
     ADJ, KC_LGUI, LT(_FUN, KC_ESC), LT(_CMOL, KC_SPC), LT(_NAV, KC_TAB), /**/ LT(_SYM, KC_ENT), LT(_CMOR, KC_BSPC), LT(_NUM, KC_DEL), KC_RALT, KC_RGUI

    ),

    /*
    * Mod L Layer for Colemak
    *
    * ,-------------------------------------------.                              ,-------------------------------------------.
    * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
    * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    * |        | LGui | Alt  | Ctrl | Shft |      |                              |      |      |      |      |      |        |
    * |--------+------+------+------+------+------+-------------.  ,-------------,-------------------------------------------.
    * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        |      |      |      |    X |      |  |      |      |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    */
    [_CMOL] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                          _______, _______, _______, _______, _______, _______,
        _______, OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, _______,                                          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______
    ),


    /*
     * Mod R Layer for Colemak
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |                              |      | Shft | Ctrl |  Alt |  GUI |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      | X    |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */

     [_CMOR] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                          _______, _______, _______, _______, _______, _______,
        _______, KC_A,    KC_R,    KC_S,    KC_T,    _______,                                          _______, OS_RSFT, OS_RCTL, OS_RALT, OS_RGUI, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______
    ),

    /*
     * Num Layer: Numerical keys
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |  {[  |   7  |   8  |   9  |  ]}  |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |  : ; |   4  |   5  |   6  |   +  |                              |      | Shift| Ctrl |  Alt |  GUI |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |   .  |   1  |   2  |   3  |  \ | |      |      |  |      |      |      |      |   <  |   >  |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |   '  |  0   |   -  |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      | X    |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
     [_NUM] = LAYOUT(
        _______, CLBRC,  KC_7, KC_8,    KC_9,    CRBRC,                                       _______, _______, _______, _______, _______, _______,
        _______, CCLN,   KC_4, KC_5,    KC_6,    SE_PLUS,                                     _______, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______,
        _______, SE_DOT, KC_1, KC_2,    KC_3,    CBPIP,   _______, _______, _______, _______, _______, _______, SE_LABK, SE_RABK, _______, _______,
                              _______, _______, SE_QUOT, KC_0,    LT(_NAV, SE_MINS), _______, _______, _______, _______, _______
    ),

    /*
     * Sym Layer: Numbers and symbols
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |  !   |  @   |  #   |  $   |  %   |                              |   &  |  /   |  (   |  )   |  *   |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  ^   |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |  X   |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_SYM] = LAYOUT(
        _______, SE_EXLM, SE_AT,   SE_HASH, SE_DLR,  SE_PERC,                                     SE_AMPR, SE_SLSH, SE_LPRN, SE_RPRN, SE_ASTR, _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, SE_BSLS, SE_COLN, SE_SCLN, SE_MINS, SE_LBRC, SE_LCBR, _______, _______, SE_RCBR, SE_RBRC, SE_UNDS, SE_COMM, SE_DOT,  SE_CIRC, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /*
     * Function Layer: Function keys
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |      |      |      |      |      |                              |      |  F7  |  F8  |  F9  |  F10 |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |                              |      |  F4  |  F5  |  F6  |  F11 |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |      |  |      |      |      |  F1  |  F2  |  F3  |  F12 |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_FUN] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                     _______,  KC_F7, KC_F8, KC_F9, KC_F10,_______,
        _______, _______, _______, _______, _______, _______,                                     _______,  KC_F4, KC_F5, KC_F6, KC_F11,_______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_F1, KC_F2, KC_F3, KC_F12,_______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /*
     * Nav Layer: Media, navigation
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |  W1  |  W2  |  W3  |  W4  |  W5  |                              | Home | PgUp | PgDn | End  | VolUp| Delete |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |  GUI |  Alt | Ctrl | Shift|      |                              |   ←  |   ↓  |   ↑  |   →  | VolDn| Insert |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |ScLck |  |  W←  |  W→  | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |    X |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_NAV] = LAYOUT(
        _______, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5),                     KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_VOLU, KC_DEL,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                    KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_VOLD, KC_INS,
        _______, _______, _______, _______, _______, _______, _______, KC_SCRL, LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_RGHT)),KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /*
     * Adjust Layer: Default layer settings, ADJUST / RGB
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |  TOG   | SAI  | HUI  | VAI  | MOD  |QWERTY|                              |      |  MW↓ |  MW↑ |      |      |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        | SAD  | HUD  | VAD  | RMOD |Colmak|                              |  M←  |  M↓  |  M↑  |  M→  |      |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        | SPU  | SPD  |      |      |      |      |      |  | MB3  | MB4  |      |      |      |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |  X   |      |      |      |      |  | MB1  | MB2  | SPD0 | SPD1 | SPD2 |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_ADJ] = LAYOUT(
        RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, QWE,                                     _______, MS_WHLD, MS_WHLU, _______, _______, _______,
        _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, COL,                                         MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, _______, _______,
        _______, RM_SPDU, RM_SPDD, _______, _______, _______, _______, _______, MS_BTN3, MS_BTN4, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, MS_BTN1, MS_BTN2, MS_ACL0, MS_ACL1, MS_ACL2
    ),
    /*
     * Tri Layer:
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * | BOOT   |      |      |      |      |      |                              |      |      |      |   Ö  |      | BOOT   |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |   Å  |   Ä  |      |      |      |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      | DBG  |  |      |      |      |      |      |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |  X   |  |   X  |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_TRI] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______,                                     _______, _______, _______, SE_ODIA, _______, QK_BOOT,
        _______, SE_ARNG, SE_ADIA, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /*
     * Layer template
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |    X |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
     [_BTN] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    // /*
    //  * Layer template
    //  *
    //  * ,-------------------------------------------.                              ,-------------------------------------------.
    //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
    //  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
    //  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    //  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
    //  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    //  *                        |      |      |      |      |      |  |      |      |      |      |      |
    //  *                        |      |      |      |      |      |  |      |      |      |      |      |
    //  *                        `----------------------------------'  `----------------------------------'
    //  */
    //     [_LAYERINDEX] = LAYOUT(
    //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
    //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
    //       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    //     ),
};

// Tap Dance Definitions
void tapLeftBrace(tap_dance_state_t *state, void *user_data) {
    uprintf("Keycode in tapLeftBrace\n");
    switch (state->count) {
        case 1:
            tap_code16(SE_LPRN);
            break;
        case 2:
            tap_code16(SE_LCBR);
            break;
        default:
            tap_code16(SE_LBRC);
            break;
    }
}

void tapRightBrace(tap_dance_state_t *state, void *user_data) {
    uprintf("Keycode in tapRightBrace\n");
    switch (state->count) {
        case 1:
            tap_code16(SE_RPRN);
            break;
        case 2:
            tap_code16(SE_RCBR);
            break;
        default:
            tap_code16(SE_RBRC);
            break;
    }
}
void tapQuote(tap_dance_state_t *state, void *user_data) {
    uprintf("Keycode in tapQuote\n");
    switch (state->count) {
        case 1:
            tap_code16(SE_QUOT);
            break;
        case 2:
            tap_code16(SE_DQUO);
            break;
        default:
            tap_code16(SE_DQUO);
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LBRC]   = ACTION_TAP_DANCE_FN(tapLeftBrace),
    [TD_RBRC]   = ACTION_TAP_DANCE_FN(tapRightBrace),
    [TD_Q]      = ACTION_TAP_DANCE_FN(tapQuote)
};

// Custom Shift/Normal Tapkey redefines
bool shift_and_tap16(keyrecord_t *record, uint16_t scode, uint16_t code) {
    uint8_t mods = get_mods();
    if (record->event.pressed) {
        del_mods(MOD_MASK_SHIFT);
        if (mods & MOD_MASK_SHIFT) {
            tap_code16(scode);
        } else {
            tap_code16(code);
        }
        set_mods(mods);
        return false;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uprintf("Keycode %u in process_record_user\n", keycode);
    bool process = true;
    switch (keycode) {
        case CLBRC:
            /* { [ */
            process = shift_and_tap16(record, SE_LBRC, SE_LCBR);
            break;

        case CRBRC:
            /* } ] */
            process = shift_and_tap16(record, SE_RBRC, SE_RCBR);
            break;

        case CBPIP:
            /* \ | */
            process = shift_and_tap16(record, SE_PIPE, SE_BSLS);
            break;

        case CCLN:
            /* ; : */
            process = shift_and_tap16(record, SE_COLN, SE_SCLN);
            break;

        default:
    }

    uprintf("Exiting process_record_user %u\n", process);
    return process;
}

// OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NAV, _SYM, _TRI);
}

void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

void render_state(void) {
    oled_write_P(PSTR("\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case _QMOL:
            oled_write_P(PSTR("Mod Left (Qwe)\n"), false);
            break;
        case _QMOR:
            oled_write_P(PSTR("Mod Right (Qwe)\n"), false);
            break;
       case _COLEMAK_DH:
            oled_write_P(PSTR("Colemak\n"), false);
            break;
        case _CMOL:
            oled_write_P(PSTR("Mod Left (Col)\n"), false);
            break;
        case _CMOR:
            oled_write_P(PSTR("Mod Right (Col)\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Numerical\n"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("Symbol\n"), false);
            break;
        case _FUN:
            oled_write_P(PSTR("Function\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case _ADJ:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        case _TRI:
            oled_write_P(PSTR("Tri-State\n"), false);
            break;
        case _BTN:
            oled_write_P(PSTR("Buttons\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);

    uint8_t mod_state;
    mod_state = get_mods();

    oled_write_P(mod_state & MOD_MASK_SHIFT ? PSTR("S") : PSTR(" "), false);
    oled_write_P(mod_state & MOD_MASK_CTRL ? PSTR("C") : PSTR(" "), false);
    oled_write_P(mod_state & MOD_MASK_ALT ? PSTR("A") : PSTR(" "), false);
    oled_write_P(mod_state & MOD_MASK_GUI ? PSTR("G") : PSTR(" "), false);
    oled_write_P(is_caps_word_on() ? PSTR("W") : PSTR(" "), false);
}

static char offhand[RPC_M2S_BUFFER_SIZE];

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_logo();
        render_state();
    } else {
        // Off-Hand
        render_logo();
        oled_write(offhand, false);
    }
    return false;
}

// ENCODER HANDLING
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}


// USB HID HANDLING
void raw_hid_receive(uint8_t *data, uint8_t length) {
    dprintf("raw_hid_receive - received %u bytes \n", length);
    if (is_keyboard_master()) {
        dprint("RPC_ID_USER_HID_SYNC \n");
        transaction_rpc_send(RPC_ID_USER_HID_SYNC, length, data);
    }
}

void hid_sync(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    memcpy(offhand, in_data, in_buflen);
}

void keyboard_post_init_user() {
    memset(offhand, 0, RPC_M2S_BUFFER_SIZE);
    transaction_register_rpc(RPC_ID_USER_HID_SYNC, hid_sync);
}
