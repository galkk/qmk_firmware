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
#define GAMING              1
#define CHARACTERS          2
#define CURSOR              3

#define USB_POLLING_INTERVAL_MS 1

#ifdef ENABLE_TIMER
#include "print.h"
#endif

//CAPS_WORD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE_LAYER] = LAYOUT_ortho_5x12(
    _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, WIN(KC_SPC),
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, WIN_SHIFT_T(KC_P), CTRL_ALT_T(_______),
    KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, WIN_T(KC_SCLN), CTRL_WIN(KC_QUOTE),
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, CTRL_SHIFT_T(KC_SLSH), ALT_SHIFT(_______),
    OSM(MOD_LCTL), KC_LALT, _______, MO(CURSOR), KC_LSFT, KC_BSPC, KC_ENT, KC_SPC , MO(CHARACTERS), KC_LBRC, KC_RBRC, CTRL_ALT_SHIFT(_______)),

[GAMING] = LAYOUT_ortho_5x12(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_F1,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, _______, _______,
    KC_CAPS_LOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, _______, KC_TILD,
    KC_LALT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, _______,
    _______, KC_LCTL, KC_SPC, KC_RGHT, KC_LSFT, KC_BSPC, KC_ENT, _______, KC_SPC, KC_LEFT, KC_DOWN, KC_RGHT),

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
        case CURSOR:
            rgblight_enable_noeeprom();
            rgblight_setrgb(RGB_BLUE);
            break;
        case CHARACTERS:
            rgblight_enable_noeeprom();
            rgblight_setrgb(RGB_YELLOW);
            break;
        case GAMING:
            rgblight_enable_noeeprom();
            rgblight_setrgb(RGB_TURQUOISE);
            break;
        default: // no colors for any other layers, or the default layer
            rgblight_disable_noeeprom();
            break;
    }
    return state;
}


#ifdef ENABLE_TIMER

/*
    Plan, as I see it
        * yio - MEGA 10, 5, spawned
        * hjk - RED 10, 5, spawned

        So when, let's say, first timer expires, it send keypress to the game `u` `o` keys, and the game
        will print in the chat (I expect) that 10 seconds left, mega

        In worst case scenario I can have global app that will listen to all keypresses and notify me
*/

enum ItemType { MEGA, RED };

typedef struct {
    char *keybinds;
    int   position;
    enum ItemType item;
} Item;

static Item RED_INFO = {
    .keybinds =  "yui",
    .position = 0,
    .item     = RED
};

static Item MEGA_INFO = {
    .keybinds = "hjk",
    .position = 0,
    .item     = MEGA
};

uint32_t send_notification(uint32_t trigger_time, void *i) {
    Item *item = (Item *)i;
    char key  = item->keybinds[item->position];
    char str[1] = {key};

    dprintf("%s in %i, sending %c letter\n",
        item->item==MEGA ? "MEGA" : "RED",
        5*(2-item->position),
        key);

    SEND_STRING(str);
    item->position++;

    if (item->position < strlen(item->keybinds)) {
        defer_exec(5*1000, send_notification, item);
    }

    return 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // do this only on gaming layer
    if (!record->event.pressed || !layer_state_is(GAMING)) {
        return true;
    }

    switch (keycode) {
    case KC_3:
            dprint("starting RED timer\n");
            RED_INFO.position = 0;
            defer_exec(15 * 1000, send_notification, &RED_INFO);
            break;
    case KC_4:
            dprint("starting MEGA timer\n");
            MEGA_INFO.position = 0;
            defer_exec(25 * 1000, send_notification, &MEGA_INFO);
            break;
    }
    return true;
}

#endif
