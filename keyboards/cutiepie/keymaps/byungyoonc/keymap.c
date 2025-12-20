
#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "byungyoonc.h"

enum planck_layers {
  _QWERTY,
  _EXTEND,
  _SYMBOL,
  _NUMBER,
  _CADET,
  _FUNCTION,
};

#define EXT MO(_EXTEND)
#define SYM MO(_SYMBOL)
#define NUM MO(_NUMBER)
#define CADET MO(_CADET)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  | |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+ +------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  | |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------+ +------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  | |   N  |   M  |   ,  |   .  |   /  |
 * |------+------+------+------+------+-+------+------+------+------+------|
 * |  NUM | LAlt | EXT  ||    Shift    |    Space    ||SYMBOL| RAlt |CADET |
 * `-----------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
    NUM,     KC_LALT, EXT,     KC_LSFT,          KC_SPC,           SYM,     KC_RALT, CADET
),
/* Extend
 * ,-----------------------------------------------------------------------.
 * | Esc  | Tab  | Menu |  F1  | Caps | | Del  | Home |  Up  | End  | PgUp |
 * |------+------+------+------+------+ +------+------+------+------+------|
 * | OGUI | OALT | OCTL | OSFT | HOLD | | Bspc | Left | Down | Right| PgDn |
 * |------+------+------+------+------+ +------+------+------+------+------|
 * | Undo | Cut  | Copy | Paste| GUI  | | Enter|      |      |      |      |
 * |------+------+------+------+------+-+------+------+------+------+------|
 * |      |      |   v  ||             |             ||      |      |      |
 * `-----------------------------------------------------------------------'
 */
[_EXTEND] = LAYOUT(
    KC_ESC,  KC_TAB,  KC_APP,  KC_F1,   KC_CAPS, KC_DEL,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,
    OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, OS_HOLD, KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
    C(KC_Z), C(KC_X), C(KC_C), C(KC_V), KC_LGUI, KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______,          _______,          _______, _______, _______
),
/* Symbol
 * ,-----------------------------------------------------------------------.
 * |   !  |   @  |   #  |   %  |   `  | |   ~  |   (  |   )  |   -  |   =  |
 * |------+------+------+------+------+ +------+------+------+------+------|
 * | OGUI | OALT | OCTL | OSFT |      | |   +  |   [  |   ]  |   \  |   '  |
 * |------+------+------+------+------+ +------+------+------+------+------|
 * |   &  |   *  |   ^  |   $  |   $  | |   _  |   {  |   }  |   |  |   "  |
 * |------+------+------+------+------+-+------+------+------+------+------|
 * |      |      |      ||             |             ||   v  |      |      |
 * `-----------------------------------------------------------------------'
 */
[_SYMBOL] = LAYOUT(
    KC_EXLM, KC_AT,   KC_HASH, KC_PERC, KC_GRV,  KC_TILD, KC_LPRN, KC_RPRN, KC_MINS, KC_EQL,
    OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, OS_HOLD, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_QUOT,
    KC_AMPR, KC_ASTR, KC_CIRC, KC_DLR,  KC_DLR,  KC_UNDS, KC_LCBR, KC_RCBR, KC_PIPE, KC_DQT,
    _______, _______, _______, _______,          _______,          _______, _______, _______
),
/* Number
 * ,-----------------------------------------------------------------------.
 * | Esc  | Tab  | Menu |  F1  | Nlck | | Del  |   7  |   8  |   9  |   -  |
 * |------+------+------+------+------+ +------+------+------+------+------|
 * | OGUI | OALT | OCTL | OSFT | HOLD | | Bspc |   4  |   5  |   6  |   +  |
 * |------+------+------+------+------+ +------+------+------+------+------|
 * | Undo | Cut  | Copy | Paste| GUI  | | Enter|   1  |   2  |   3  |   .  |
 * |------+------+------+------+------+-+------+------+------+------+------|
 * |   v  |      |      ||             |      0      ||      |      |      |
 * `-----------------------------------------------------------------------'
 */
[_NUMBER] = LAYOUT(
    KC_ESC,  KC_TAB,  KC_APP,  KC_F1,   KC_NUM,  KC_DEL,  KC_7,    KC_8,    KC_9,    KC_PMNS,
    OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, OS_HOLD, KC_BSPC, KC_4,    KC_5,    KC_6,    KC_PPLS,
    C(KC_Z), C(KC_X), C(KC_C), C(KC_V), KC_LGUI, KC_ENT,  KC_1,    KC_2,    KC_3,    KC_PDOT,
    _______, _______, _______, _______,          KC_0,             _______, _______, _______
),
/* Space Cadet Symbols
 * ,-----------------------------------------------------------------------.
 * |   ∧  |   ∨  |   ∩  |   ∪  |   ⊂  | |   ⊃  |   ∀  |   ∞  |   ∃  |   ∂  |
 * |------+------+------+------+------+ +------+------+------+------+------|
 * |   ⊥  |   ⊤  |   ⊢  |   ⊣  |   ↑  | |   ↓  |   ←  |   →  |   ↔  |      |
 * |------+------+------+------+------+ +------+------+------+------+------|
 * |   ⌊  |   ⌈  |   ≠  |   ≃  |   ≡  | |   ≤  |   ≥  |      |      |      |
 * |------+------+------+------+------+-+------+------+------+------+------|
 * |      |      |      ||             |             ||      |      |   v  |
 * `-----------------------------------------------------------------------'
 */
[_CADET] = LAYOUT(
    UC(0x2227), UC(0x2228), UC(0x2229), UC(0x222A), UC(0x2282), UC(0x2283), UC(0x2200), UC(0x221E), UC(0x2203), UC(0x2202),
    UC(0x22A5), UC(0x22A4), UC(0x22A2), UC(0x22A3), UC(0x2191), UC(0x2193), UC(0x2190), UC(0x2192), UC(0x2194), _______,
    UC(0x230A), UC(0x2308), UC(0x2260), UC(0x2243), UC(0x2261), UC(0x2264), UC(0x2265), _______, _______, KC_APP,
    _______, _______, _______, _______,          _______,          _______, _______, _______
),
/* Function
 * ,------------------------------------------------------------------------.
 * | RGBTOG| Rwnd | Play | Ffwd | VDn  | | VUp  |  F7  |  F8  |  F9  | F10  |
 * |-------+------+------+------+------+ +------+------+------+------+------|
 * |  OGUI | OALT | OCTL | OSFT | HOLD | | Mute |  F4  |  F5  |  F6  | F11  |
 * |-------+------+------+------+------+ +------+------+------+------+------|
 * |  SEC1 | SEC2 | CSC  | CSV  |      | |      |  F1  |  F2  |  F3  | F12  |
 * |-------+------+------+------+------+-+------+------+------+------+------|
 * |       |      |   v  ||   NKTOGG    |    Reset    ||   v  |      |      |
 * `------------------------------------------------------------------------'
 */
[_FUNCTION] = LAYOUT(
    RM_TOGG, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD,  KC_VOLU, KC_F7,   KC_F8,   KC_F9,   KC_F10,
    OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, OS_HOLD,  KC_MUTE, KC_F4,   KC_F5,   KC_F6,   KC_F11,
    KC_SEC1,KC_SEC2,C(S(KC_C)),C(S(KC_V)),XXXXXXX,XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F12,
    _______, _______, _______, NK_TOGG,           QK_BOOT,          _______, _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _EXTEND, _SYMBOL, _FUNCTION);
    return state;
}
