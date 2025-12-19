/*
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

// Layer shorthand
enum layer_names {
    _BASE,
    _NUM,
    _SYMBOL,
    _ADJUST
};

#define NUM MO(_NUM)
#define SYMBOL MO(_SYMBOL)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * | `      | 1      | 2      | 3      | 4      | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | PSCR   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | BACKSP |        | DELETE |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * | ESC    | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | ENTER  | HOME   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | RSHIFT | UP     | END    |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
     * | LCTRL  | LGUI   | LALT   | ADJUST | NUM    | SPACE  | SPACE  | SYMBOL | RALT   | MENU   | RCTRL  | LEFT   | DOWN   | RIGHT  |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_BASE] = LAYOUT_ortho_5x14(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, XXXXXXX, KC_DEL,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_HOME,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT, ADJUST,  NUM,     KC_SPC,  KC_SPC,  SYMBOL,  KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Number Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * | BACKSP |        |        |        |        |        |        | NumLck | Num_/  | Num_*  | Num_-  |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | ENTER  | P      | O      | I      | U      | Y      | T      | Num_7  | Num_8  | Num_9  | Num_+  |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * | '      | ;      | L      | K      | J      | H      | G      | Num_4  | Num_5  | Num_6  | N_Ent  |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * |        | /      | .      | ,      | M      | N      | B      | Num_1  | Num_2  | Num_3  | Num_.  |        |        |        |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
     * |        |        |        |        |        | Num_0  | Num_0  |        |        |        |        |        |        |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_NUM] = LAYOUT_ortho_5x14(
        KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, XXXXXXX, XXXXXXX, _______,
        KC_ENT,  KC_P,    KC_O,    KC_I,    KC_U,    KC_Y,    KC_T,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______, _______, _______,
        KC_QUOT, KC_SCLN, KC_L,    KC_K,    KC_J,    KC_H,    KC_G,    KC_P4,   KC_P5,   KC_P6,   KC_PENT, XXXXXXX, _______, _______,
        _______, KC_SLSH, KC_DOT,  KC_COMM, KC_M,    KC_N,    KC_B,    KC_P1,   KC_P2,   KC_P3,   KC_PDOT, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_P0,   KC_P0,   _______, _______, _______, _______, _______, _______, _______
    ),

    /* Symbol Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * |        | !      | @      | #      | %      |        |        | (      | )      | -      | =      |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * |        | &      | *      | $      |        |        |        | [      | ]      | \      |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * |        |        | ^      | ^      |        |        |        |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_SYMBOL] = LAYOUT_ortho_5x14(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_PERC, XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, KC_MINS, KC_EQL,  _______, _______, _______,
        _______, KC_AMPR, KC_ASTR, KC_DLR,  XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, _______, _______, _______, _______,
        _______, XXXXXXX, KC_CIRC, KC_CIRC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Adjust Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * |        | SEC1   | SEC2   |        |        |        |        |        |        |        |        |        | DEBUG  | RESET  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | F1     |        | VOL+   |        |        | NK_TOG |        | F7     | F8     | F9     | F10    |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * |        | RWND   | VOL-   | FFWD   |        |        |        | F4     | F5     | F6     | F11    |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * |        | PLAY   | MUTE   |        |        |        |        | F1     | F2     | F3     | F12    |        |        |        |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_ortho_5x14(
        _______, KC_SEC1, KC_SEC2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DB_TOGG, QK_BOOT,
        KC_F1,   XXXXXXX, KC_VOLU, XXXXXXX, XXXXXXX, NK_TOGG, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______,
        _______, KC_MRWD, KC_VOLD, KC_MFFD, XXXXXXX, RM_TOGG, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______, _______, _______,
        _______, KC_MPLY, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )

};

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    return;
}
