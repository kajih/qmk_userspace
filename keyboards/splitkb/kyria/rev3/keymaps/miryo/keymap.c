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

enum layers {
    _QWERTY_HROW = 0,
    _QWERTY,
    _COLEMAK_DH_HROW,
    _COLEMAK_DH,
    _NUM,
    _SYM,
    _FUN,
    _NAV,
    _ADJ,
    _TRI,
    _BTN,
    _MOSE,
};

// Aliases for readability
#define QWE_MOD   DF(_QWERTY_HROW)
#define QWE       DF(_QWERTY)
#define COL_MOD   DF(_COLEMAK_DH_HROW)
#define COL       DF(_COLEMAK_DH)

#define NUM       MO(_NUM)
#define SYM       MO(_SYM)
#define FKEYS     MO(_FUN)
#define NAV       MO(_NAV)
#define ADJ       MO(_ADJ)
#define TRI       MO(_TRI)
#define BTN       MO(_BTN)
#define MOSE      MO(_MOSE)

#define CTL_ESC   MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT  MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS  MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT   MT(MOD_LALT, KC_ENT)

#define MLS(key)  MT(MOD_LSFT, key)
#define MLC(key)  MT(MOD_LCTL, key)
#define MLA(key)  MT(MOD_LALT, key)
#define MLG(key)  MT(MOD_LGUI, key)

#define MRS(key)  MT(MOD_RSFT, key)
#define MRC(key)  MT(MOD_RCTL, key)
#define MRA(key)  MT(MOD_RALT, key)
#define MRG(key)  MT(MOD_RGUI, key)

/* COMBO CODE NOT USED
 const uint16_t PROGMEM test_combo1[] = {KC_A, KC_B, COMBO_END};
 const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END};
 combo_t key_combos[] = {
 COMBO(test_combo1, KC_ESC)
 COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
 };
 */

//Tap Dance Declarations
enum custom_tapdance {
    TD_LBRC = 0,
    TD_RBRC,
    TD_Q
};

//Tap Dance Definitions

void tapLeftBrace(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1: tap_code16(SE_LPRN); break;
        case 2: tap_code16(SE_LCBR); break;
        default: tap_code16(SE_LBRC); break;
    }
}

void tapRightBrace(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1: tap_code16(SE_RPRN); break;
        case 2: tap_code16(SE_RCBR); break;
        default: tap_code16(SE_RBRC); break;
    }
}
void tapQuote(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1: tap_code16(SE_QUOT); break;
        case 2: tap_code16(SE_DQUO); break;
        default: tap_code16(SE_DQUO); break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LBRC]  = ACTION_TAP_DANCE_FN(tapLeftBrace),
    [TD_RBRC]  = ACTION_TAP_DANCE_FN(tapRightBrace),
    [TD_Q]     = ACTION_TAP_DANCE_FN(tapQuote)
};

//Tap Dance END
enum custom_keycodes {
    CLBRC = SAFE_RANGE,
    CRBRC,
    CBPIP,
    CCLN
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CLBRC:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(SE_LBRC);
                } else {
                    tap_code16(SE_LCBR);
                }
            }
            return false; // vi har hanterat tangenttrycket själva

        case CRBRC:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(SE_RBRC);
                } else {
                    tap_code16(SE_RCBR);
                }
            }
            return false; // vi har hanterat tangenttrycket själva

        case CBPIP:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(SE_PIPE);
                } else {
                    tap_code16(SE_BSLS);
                }
            }
            return false; // vi har hanterat tangenttrycket själva

        case CCLN:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(SE_COLN);
                } else {
                    tap_code16(SE_SCLN);
                }
            }
            return false; // vi har hanterat tangenttrycket själva
      }
    return true;
}




// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer: QWERTY
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |  :;  |Ctrl/' "|
     * |--------+------+------+------+------+------+---------------.  ,-----------+------+------+------+------+------+--------|
     * | LShift |   Z  |   X  |   C  |   V  |   B  |  {[  |CapsTogg|  |F-keys|  ]} |   N  |   M  | ,  < | . >  | /? | RShift |
     * `----------------------+------+------+------+------+--------|  |------+------+------+------+------+----------------------'
     *                        |Adjust| LGUI | LAlt/| Space| Nav    |  | Sym  | Space| AltGr| RGUI | Menu |
     *                        |      |      | Enter|      |        |  |      |      |      |      |      |
     *                        `------------------------------------'  `----------------------------------'
     */
    [_QWERTY_HROW] = LAYOUT(
        KC_ESC,               KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,                                                                                        KC_Y,              KC_U,      KC_I,      KC_O,      KC_P,         KC_BSPC,
        MT(MOD_LSFT, KC_TAB), MLG(KC_A), MLA(KC_S), MLC(KC_D), MLS(KC_F), KC_G,                                                                                        KC_H,              MRS(KC_J), MRC(KC_K), MRA(KC_L), MRG(KC_BSLS), MRS(KC_QUOT),
        KC_LCTL,              KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,             TD_LBRC,         CW_TOGG,             FKEYS,             TD_RBRC,          KC_N,              KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,      KC_RCTL,
                                                    ADJ,       KC_LGUI,   LT(_MOSE, KC_ESC), LT(_BTN, KC_SPC), LT(_NAV, KC_TAB),     LT(_NUM, KC_ENT),   LT(_SYM, KC_BSPC), LT(_FUN, KC_DEL), KC_RALT,   KC_APP
    ),

    [_QWERTY] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                     KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /*
     * Base Layer: Colemak DH
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |  Tab   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  Bksp  |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |Ctrl/Esc|   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |Ctrl/' "|
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * | LShift |   Z  |   X  |   C  |   D  |   V  | [ {  |CapsLk|  |F-keys|  ] } |   K  |   H  | ,  < | . >  | /  ? | RShift |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
     *                        |      |      | Enter|      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_COLEMAK_DH_HROW] = LAYOUT(
        _______, KC_Q,      KC_W,      KC_F,      KC_P,      KC_B,                                                     KC_J,    KC_L,      KC_U,      KC_Y,      KC_SCLN,   _______,
        _______, MLG(KC_A), MLA(KC_R), MLC(KC_S), MLS(KC_T), KC_G,                                                     KC_M,    MRS(KC_N), MRC(KC_E), MRA(KC_I), MRG(KC_O), _______,
        _______, KC_Z,      KC_X,      KC_C,      KC_D,      KC_V,    TD(TD_LBRC), KC_CAPS,      FKEYS,   TD(TD_RBRC), KC_K,    KC_H,      KC_COMM,   KC_DOT,    KC_SLSH,   _______,
                                       _______,   _______,   _______, _______,     _______,      _______, _______,     _______, _______,   _______

    ),

    [_COLEMAK_DH] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, KC_A   , KC_R   , KC_S   , KC_T   , KC_G   ,                                     KC_M   , KC_N   , KC_E   , KC_I   , KC_O   , _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

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
     * |   '/"  |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   &  |  /   |  (   |  )   |  *   |   +    |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  ^   |   ?    |
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
     * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |  X   |      |      |      |      |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_FUN] = LAYOUT(
        _______, KC_F12, KC_F9, KC_F8,   KC_F7,   _______,                                     _______, _______, _______, _______, _______, _______,
        _______, KC_F11, KC_F6, KC_F5,   KC_F4,   _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
        _______, KC_F10, KC_F3, KC_F2,   KC_F1,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /*
     * Nav Layer: Media, navigation
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |   W1   |  W2  |  W3  |  W4  |  W5  |  W6  |                              | Home | PgUp | PgDn | End  | VolUp| Delete |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |  GUI |  Alt | Ctrl | Shift|      |                              |   ←  |   ↓  |   ↑  |   →  | VolDn| Insert |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |ScLck |  |  W←  |  W→  | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |  X   |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_NAV] = LAYOUT(
        LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), LGUI(KC_6),                                    KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_VOLU, KC_DEL,
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
        RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, QWE_MOD,                                     _______, MS_WHLD, MS_WHLU, _______, _______, _______,
        _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, QWE,                                         MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, _______, _______,
        _______, RM_SPDU, RM_SPDD, _______, _______, COL_MOD, _______, _______, MS_BTN3, MS_BTN4, _______, _______, _______, _______, _______, _______,
                                   _______, _______, COL,     _______, _______, MS_BTN1, MS_BTN2, MS_ACL0, MS_ACL1, MS_ACL2
    ),
    /*
     * Tri Layer:
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |      |      |      |      |      |                              |   ^  |   (  |   )  |   `  |   Å  |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |                              |      |   {  |   }  |   Ö  |   Ä  |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |      |  |      |      |      |   [  |   ]  |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |  X   |  |   X  |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_TRI] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______,                                     _______, _______, _______, SE_ODIA, _______, QK_BOOT,
        _______, SE_ARNG, SE_ADIA, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_BTN] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_MOSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MS_ACL0, MS_ACL1, MS_ACL2, _______, _______,
                                   _______, _______, _______, _______, _______, MS_BTN2, MS_BTN1, MS_BTN3, _______, _______
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

// OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NAV, _NUM, _TRI);
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
        case _QWERTY_HROW:
            oled_write_P(PSTR("QWERTY-HR\n"), false);
            break;
         case _QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case _COLEMAK_DH_HROW:
            oled_write_P(PSTR("Colemak-HR\n"), false);
            break;
        case _COLEMAK_DH:
            oled_write_P(PSTR("Colemak\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Numeric\n"), false);
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
         case _MOSE:
            oled_write_P(PSTR("Mouse\n"), false);
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
