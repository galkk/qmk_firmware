#include QMK_KEYBOARD_H

#define WIN RGUI
#define CTRL_ALT_T LCA_T
#define WIN_SHIFT_T SGUI_T
#define CTRL_SHIFT_T RCS_T
#define ALT_SHIFT RSA
#define CTRL_ALT_SHIFT MEH
#define CTRL_WIN(kc) MT(MOD_LCTL | MOD_RGUI, kc)
#define CAPS_WORD QK_CAPS_WORD_TOGGLE

#define BASE_LAYER          0
#define CHARACTERS          1
#define CURSOR              2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE_LAYER] = LAYOUT_ortho_5x12(
    _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, WIN(KC_SPC),
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, WIN_SHIFT_T(KC_P), CTRL_ALT_T(_______),
    KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, WIN_T(KC_SCLN), CTRL_WIN(KC_QUOTE),
    CAPS_WORD, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, CTRL_SHIFT_T(KC_SLSH), ALT_SHIFT(_______),
    _______, KC_LALT, OSM(MOD_LCTL), MO(CURSOR), KC_LSFT, KC_BSPC, _______, KC_ENT, LT(CHARACTERS, KC_SPC), KC_LBRC, KC_RBRC, CTRL_ALT_SHIFT(_______)),

[CHARACTERS] = LAYOUT_ortho_5x12(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
    _______, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_BSLS, _______, KC_UNDS, KC_DQUO, KC_QUOT, KC_CIRC, _______,
    _______, KC_DLR, KC_PLUS, KC_MINS, KC_ASTR, _______, _______, KC_AMPR, KC_PIPE, KC_EXLM, KC_EQL, _______,
    _______, KC_AT, KC_COLN, KC_HASH, KC_PERC, _______, _______, KC_TILD, KC_GRV, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LPRN, KC_RPRN, _______),

[CURSOR] = LAYOUT_ortho_5x12(
    QK_BOOTLOADER, LCTL(KC_HOME), LCTL(KC_PGDN), LCTL(KC_PGUP), LCTL(KC_END), _______, _______, _______, _______, _______, RGB_MOD, RGB_TOG,
    LGUI(KC_TAB), KC_HOME, KC_PGDN, KC_PGUP, KC_END, LCTL(KC_F4), _______, _______, KC_MS_U, _______, _______, _______,
    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, LCTL(KC_BSPC), _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
    _______, LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP), LCTL(KC_RGHT), _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_TRNS, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______)

};

// RGB lightning documentation:
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgblight.md
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 2:
            rgblight_enable_noeeprom();
            rgblight_setrgb(RGB_BLUE);
            break;
        case 1:
            rgblight_enable_noeeprom();
            rgblight_setrgb(RGB_YELLOW);
            break;
        default: // for any other layers, or the default layer
            rgblight_disable_noeeprom();
            break;
    }
    return state;
}
