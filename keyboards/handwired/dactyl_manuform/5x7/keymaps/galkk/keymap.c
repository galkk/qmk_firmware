#include QMK_KEYBOARD_H

enum custom_keycodes {
    POINTER_DEREFERENCE = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case POINTER_DEREFERENCE:
        if (record->event.pressed) {
            SEND_STRING("->");
        }
        break;
    }
    return true;
};

// This dactyl has a bit weird layout, that doesn't map well to UI/order of buttons in the layout.
// Those macroses help to have traditional approach: left -> right, row to bottom
#define LEFT_THUMB_BLOCK(p1,p2,p3,p4,p5,p6)p4, p1, p5, p2, p6, p3
#define RIGHT_THUMB_BLOCK(p1,p2,p3,p4,p5,p6)p3, p6, p2, p5, p3, p4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_5x7(
        KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO,
        KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_NO,
        CAPS_WORD, KC_Z, KC_X, KC_C, KC_V, KC_B,
        KC_NO, KC_NO, KC_NO, KC_LOCK,

    // lower upper, left -> right
            KC_LSFT, MO(3),
            KC_BSPC, KC_LCTL,
            KC_ENT, KC_NO,

        KC_NO, KC_6, KC_7, KC_8, KC_9, KC_0, RGUI(KC_SPC),
        KC_NO, KC_Y, KC_U, KC_I, KC_O, SGUI_T(KC_P), RCS(KC_NO),
        KC_NO, KC_H, KC_J, KC_K, KC_L, RGUI_T(KC_SCLN), MT(MOD_LCTL | MOD_RGUI, KC_QUOTE),
        KC_N, KC_M, KC_COMM, KC_DOT, LCA_T(KC_SLSH), RSA(KC_NO),
        MO(2), KC_LBRC, KC_RBRC, MEH(KC_NO),

    // upper lower, right -> left
            MO(1), KC_SPC,
            KC_LGUI, KC_RSFT,
            KC_NO, KC_RALT),

	[1] = LAYOUT_5x7(
        KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_BSLS, KC_NO, KC_NO,
        KC_NO, KC_DLR, KC_PLUS, KC_MINS, KC_ASTR, KC_NO, KC_NO,
        KC_NO, KC_AT, KC_COLN, KC_HASH, KC_PERC, KC_NO,
        KC_NO, KC_NO, KC_INSERT, KC_DELETE,

        KC_NO, KC_NO,
        KC_NO, KC_NO,
        KC_NO, KC_NO,

        KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        KC_NO, KC_NO, KC_UNDS, KC_DQUO, KC_QUOT, KC_CIRC, KC_F12,
        KC_NO, KC_NO, KC_AMPR, KC_PIPE, KC_EXLM, KC_EQL, KC_NO,
        KC_NO, KC_TILD, KC_GRV, KC_NO, KC_NO, POINTER_DEREFERENCE,
        KC_NO, KC_LPRN, KC_RPRN, KC_NO,

        KC_NO, KC_TRNS,
        KC_NO, KC_NO,
        KC_NO, KC_NO),

	[2] = LAYOUT_5x7(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO,
        KC_NO, KC_NO,
        KC_NO, KC_NO,

        QK_BOOTLOADER, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO,
        KC_NO, KC_NO,
        KC_NO, KC_NO),

	[3] = LAYOUT_5x7(
        KC_NO, LCTL(KC_HOME), LCTL(KC_PGDN), LCTL(KC_PGUP), LCTL(KC_END), KC_NO, KC_NO,
        KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, LCTL(KC_F4), KC_NO,
        KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, LCTL(KC_BSPC), KC_NO,
        KC_NO, LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP), LCTL(KC_RGHT), KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_TRNS,
        KC_NO, KC_NO,
        KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_MS_WH_DOWN, KC_MS_U, KC_MS_WH_UP, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO,
        KC_BTN1, KC_BTN2,
        KC_NO, KC_NO)
};
