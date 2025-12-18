#include "byungyoonc.h"
#include "keycodes.h"
#include "oneshot.h"

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#    include "secrets.h"
#else
static const char *const secrets[] = {"test1", "test2"};
#endif

#if !defined(MACRO_TIMER)
#   define MACRO_TIMER 20
#endif

#define KC_TASK LCTL(LSFT(KC_ESC))
#define KC_MMUT LSG(KC_A)

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    switch (keycode) {
    case KC_SEC1 ... KC_SEC2: /* Secrets!  Externally defined strings, not stored in repo */
        if (!record->event.pressed) {
            send_string_with_delay(secrets[keycode - KC_SEC1], MACRO_TIMER);
        }
        return false;
        break;
    }

    return true;
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    if (QK_MOMENTARY <= keycode && keycode <= QK_MOMENTARY_MAX) {
        return true;
    }
    if (keycode == QK_TRI_LAYER_LOWER ||
        keycode == QK_TRI_LAYER_UPPER) {
        return true;
    }
    return false;
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    if (QK_MOMENTARY <= keycode && keycode <= QK_MOMENTARY_MAX) {
        return true;
    }
    if (keycode == QK_TRI_LAYER_LOWER ||
        keycode == QK_TRI_LAYER_UPPER) {
        return true;
    }
    switch (keycode) {
        case KC_LSFT:
        case KC_RSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_CMD:
            return true;
    }
    return false;
}

bool is_oneshot_hold_key(uint16_t keycode) {
    return keycode == OS_HOLD;
}
