// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "byungyoonc.h"

enum layers {
  _QWERTY,
  _EXTEND,
  _SYMBOL,
  _FUNCTION,
  _NUMBER,
};

#define NUM MO(_NUMBER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x5_3(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                      NUM,     TL_LOWR, KC_LSFT,      KC_SPC,  TL_UPPR, KC_RALT
  ),

  [_EXTEND] = LAYOUT_split_3x5_3(
    KC_ESC,  KC_TAB,  KC_MENU, KC_F1,   KC_CAPS,      KC_DEL,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,
    OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, OS_HOLD,      KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
    C(KC_Z), C(KC_X), C(KC_C), C(KC_V), KC_LGUI,      KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      _______, _______, _______,      _______, _______, _______
  ),

  [_SYMBOL] = LAYOUT_split_3x5_3(
    KC_EXLM, KC_AT,   KC_HASH, KC_PERC, KC_GRV,       KC_TILD, KC_LPRN, KC_RPRN, KC_MINS, KC_EQL,
    OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, OS_HOLD,      KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_QUOT,
    KC_AMPR, KC_ASTR, KC_CIRC, KC_DLR,  KC_DLR,       KC_UNDS, KC_LCBR, KC_RCBR, KC_PIPE, KC_DQT,
                      _______, _______, _______,      _______, _______, _______
  ),

  [_FUNCTION] = LAYOUT_split_3x5_3(
    RM_TOGG, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,      RM_NEXT, KC_F7,   KC_F8,   KC_F9,   KC_F10,
    OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, KC_VOLD,      RM_HUEU, KC_F4,   KC_F5,   KC_F6,   KC_F11,
    KC_SEC1,KC_SEC2,C(S(KC_C)),C(S(KC_V)),KC_MUTE,    RM_SATU, KC_F1,   KC_F2,   KC_F3,   KC_F12,
                      RM_VALU, _______, NK_TOGG,      QK_BOOT, _______, RM_SPDU
  ),

  [_NUMBER] = LAYOUT_split_3x5_3(
    KC_ESC,  KC_TAB,  KC_MENU, KC_F1,   KC_NUM,       KC_DEL,  KC_7,    KC_8,    KC_9,    KC_PMNS,
    OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, OS_HOLD,      KC_BSPC, KC_4,    KC_5,    KC_6,    KC_PPLS,
    C(KC_Z), C(KC_X), C(KC_C), C(KC_V), KC_LGUI,      KC_ENT,  KC_1,    KC_2,    KC_3,    KC_PDOT,
                      _______, _______, _______,      KC_0,    _______, _______
  )
};
