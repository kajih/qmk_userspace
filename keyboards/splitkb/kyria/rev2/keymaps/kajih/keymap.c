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

#include "quantum.h"
#include "quantum/keycodes.h"
#include "keymap_swedish.h"

enum layers {
    _QWERTY = 0,
    _COLEMAK_DH,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
    _TRI,
};

// Aliases for readability
#define QWERTY		DF(_QWERTY)
#define COLEMAK		DF(_COLEMAK_DH)

#define SYM			MO(_SYM)
#define NAV			MO(_NAV)
#define FKEYS		MO(_FUNCTION)
#define ADJUST		MO(_ADJUST)
#define TRI         MO(_TRI)

#define CTL_ESC		MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT	MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS	MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT		MT(MOD_LALT, KC_ENT)


/* COMBO CODE NOT USED
 */
const uint16_t PROGMEM test_combo1[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END};
combo_t key_combos[] = {
    COMBO(test_combo1, KC_ESC),
    COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
};

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
    [_QWERTY] = LAYOUT(
        KC_TAB , KC_Q , KC_W , KC_E , KC_R , KC_T , KC_Y, KC_U , KC_I , KC_O , KC_P , KC_BSPC,
        CTL_ESC , KC_A , KC_S , KC_D , KC_F , KC_G , KC_H, KC_J , KC_K , KC_L , KC_SCLN, CTL_QUOT,
        KC_LSFT , KC_Z , KC_X , KC_C , KC_V , KC_B , KC_LBRC , CW_TOGG , FKEYS , KC_RBRC, KC_N, KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
        ADJUST , KC_LGUI, ALT_ENT, KC_SPC , NAV , SYM , KC_SPC ,KC_RALT, KC_RGUI, KC_APP
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
    [_COLEMAK_DH] = LAYOUT(
        KC_TAB , KC_Q , KC_W , KC_F , KC_P , KC_B , KC_J, KC_L , KC_U , KC_Y ,KC_SCLN, KC_BSPC,
        CTL_ESC , KC_A , KC_R , KC_S , KC_T , KC_G , KC_M, KC_N , KC_E , KC_I , KC_O , CTL_QUOT,
        KC_LSFT , KC_Z , KC_X , KC_C , KC_D , KC_V , KC_LBRC,KC_CAPS, FKEYS , KC_RBRC, KC_K, KC_H ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
        ADJUST, KC_LGUI, ALT_ENT, KC_SPC , NAV , SYM , KC_SPC ,KC_RALT, KC_RGUI, KC_APP
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
     * Sym Layer: Numbers and symbols
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
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
        KC_GRV , KC_1 , KC_2 , KC_3 , KC_4 , KC_5 ,                                                         KC_6 , KC_7 , KC_8 , KC_9 , KC_0 , SE_EQL ,
        SE_TILD , SE_EXLM, SE_AT , SE_HASH, SE_DLR, SE_PERC,                                      SE_AMPR, SE_SLSH, SE_LPRN, SE_RPRN, SE_ASTR, SE_PLUS,
        SE_PIPE , SE_BSLS, SE_COLN, SE_SCLN, SE_MINS, SE_LBRC, SE_LCBR, _______, _______, SE_RCBR, SE_RBRC, SE_UNDS, SE_COMM, SE_DOT, SE_CIRC, SE_QUES,
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
    [_FUNCTION] = LAYOUT(
        _______, KC_F9 , KC_F10, KC_F11, KC_F12, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, KC_F5 , KC_F6 , KC_F7 , KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
        _______, KC_F1 , KC_F2 , KC_F3 , KC_F4 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /*
     * Adjust Layer: Default layer settings, ADJUST / RGB
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |      |      |      |      |QWERTY|                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |      |      |      |      |Colmak|                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_ADJUST] = LAYOUT(
        _______, _______, _______, _______, _______, QWERTY,                                      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, COLEMAK,                                     RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD, _______,
        _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    /*
     * Tri Layer:
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |      |      |      |      |      |                              |      |   (  |   )  |      |   Å  |        |
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
        _______, _______, _______, _______, _______, _______,                                     _______, SE_LPRN, SE_RPRN, SE_UNDS, SE_ARNG, _______,
        _______, _______, _______, _______, _______, _______,                                     _______, SE_LCBR, SE_RCBR, SE_ODIA, SE_ADIA, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, SE_LBRC, SE_RBRC, _______, _______, _______,
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
        case _COLEMAK_DH:
            oled_write_P(PSTR("Colemak-DH\n"), false);
        break;
        case _NAV:
            oled_write_P(PSTR("Nav\n"), false);
        break;
        case _SYM:
            oled_write_P(PSTR("Sym\n"), false);
        break;
        case _FUNCTION:
            oled_write_P(PSTR("Function\n"), false);
        break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
        break;
        case _TRI:
            oled_write_P(PSTR("Tri-State\n"), false);
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

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
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

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }

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
