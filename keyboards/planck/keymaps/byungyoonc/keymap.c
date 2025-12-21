/* Copyright 2015-2021 Jack Humbert
 * Copyright 2021 Choi Byungyoon
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

#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "byungyoonc.h"

enum layers {
  _QWERTY,
  _NUM,
  _MMO,
  _MMOF,
  _SYMBOL,
  _ADJUST,
};

#define NUM MO(_NUM)
#define MMO MO(_MMO)
#define SYMBOL MO(_SYMBOL)
#define QWERTY DF(_QWERTY)
#define AGRGUI LGUI_T(KC_RALT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty */
    [_QWERTY] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
    MMO,     XXXXXXX, XXXXXXX, KC_LALT, NUM,        KC_SPC,        SYMBOL,  AGRGUI,  KC_LEFT, KC_DOWN, KC_RGHT
    ),

/* Num */
[_NUM] = LAYOUT_planck_mit(
    KC_F1,   KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_CAPS, KC_NUM,  KC_7   , KC_8   , KC_9   , KC_PMNS, KC_DEL,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, XXXXXXX, KC_4   , KC_5   , KC_6   , KC_PPLS, _______,
    _______, KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, KC_APP,  XXXXXXX, KC_1   , KC_2   , KC_3   , KC_PDOT, _______,
    _______, _______, _______, _______, _______,       KC_0,       _______, _______, _______, _______, _______
),

/* MMO */
[_MMO] = LAYOUT_planck_mit(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_EQL,  _______, _______, _______, _______, _______, _______, _______,
    _______, KC_4,    KC_5,    KC_6,    KC_MINS, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______
),

/* MMO-F */
[_MMOF] = LAYOUT_planck_mit(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______, _______, _______, _______, _______, _______, _______,
    _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______, _______, _______, _______, _______, _______, _______,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______
),

/* Symbol */
[_SYMBOL] = LAYOUT_planck_mit(
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_PERC, KC_ASTR, XXXXXXX, KC_LPRN, KC_RPRN, KC_MINS, KC_EQL,  KC_DEL,
    _______, KC_AMPR, KC_ASTR, KC_DLR,  XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, KC_QUOT, _______,
    _______, XXXXXXX, KC_CIRC, KC_CIRC, XXXXXXX, KC_APP,  XXXXXXX, XXXXXXX, _______, _______, KC_SLSH, _______,
    _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______
),

/* Adjust */
[_ADJUST] = LAYOUT_planck_mit(
    _______, UG_TOGG, KC_MPRV, KC_MPLY, KC_MNXT, KC_SCRL, KC_VOLU, KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_PSCR,
    _______, KC_SEC1, KC_SEC2, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_F4,   KC_F5,   KC_F6,   KC_F11, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_F1,   KC_F2,   KC_F3,   KC_F12, _______,
    _______, _______, _______, _______, _______,      QK_BOOT,     _______, _______, NK_TOGG, DB_TOGG, XXXXXXX
),
};

const key_override_t pmns_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_PMNS, KC_PSLS);
const key_override_t ppls_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_PPLS, KC_PAST);
const key_override_t up_key_override = ko_make_with_layers(MOD_BIT(KC_RSFT), KC_UP, KC_QUES, (1 << _QWERTY));

const key_override_t *key_overrides[] = {
    &pmns_key_override,
    &ppls_key_override,
    &up_key_override
};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _NUM, _SYMBOL, _ADJUST);
    state = update_tri_layer_state(state, _MMO, _NUM, _MMOF);
    return state;
}
