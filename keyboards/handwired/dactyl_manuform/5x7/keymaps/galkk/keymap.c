#include QMK_KEYBOARD_H

// This dactyl has a bit weird layout, that doesn't map well to UI/order of buttons in the layout.
// Those macroses help to have approach as the rest of the keyboard: left -> right, top to bottom
#define LEFT_THUMB_BLOCK(p1,p2,p3,p4,p5,p6) \
    p4, p1, \
    p5, p2, \
    p6, p3

#define RIGHT_THUMB_BLOCK(p1,p2,p3,p4,p5,p6) \
    p3, p6, \
    p2, p5, \
    p1, p4

// This is needed to wrap layout macro expansion
#define LAYOUT(...) LAYOUT_5x7(__VA_ARGS__)

// I don't want to change generic json layouts, so will just reformat the file
#define LONG_LAYOUT(l11, l12, l13, l14, l15, l16, l17,                       r11, r12, r13, r14, r15, r16, r17, \
                    l21, l22, l23, l24, l25, l26, l27,                       r21, r22, r23, r24, r25, r26, r27, \
                    l31, l32, l33, l34, l35, l36, l37,                       r31, r32, r33, r34, r35, r36, r37, \
                    l41, l42, l43, l44, l45, l46,                            r41, r42, r43, r44, r45, r46,      \
                    l51, l52, l53, l54,                                                r51, r52, r53, r54,      \
                              l61, l62, l63,                                 r61, r62, r63,                     \
                              l71, l72, l73,                                 r71, r72, r73                      \
                    ) \
    LAYOUT(l11, l12, l13, l14, l15, l16, l17, \
                l21, l22, l23, l24, l25, l26, l27, \
                l31, l32, l33, l34, l35, l36, l37, \
                l41, l42, l43, l44, l45, l46, \
                l51, l52, l53, l54, \
                LEFT_THUMB_BLOCK(l61, l62, l63, \
                                l71, l72, l73), \
                r11, r12, r13, r14, r15, r16, r17, \
                r21, r22, r23, r24, r25, r26, r27, \
                r31, r32, r33, r34, r35, r36, r37, \
                r41, r42, r43, r44, r45, r46,  \
                r51, r52, r53, r54, \
                RIGHT_THUMB_BLOCK(r61, r62, r63, \
                                  r71, r72, r73) \
        )

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

// https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
                                                                                //  CTRL | ALT | SHIFT | WIN
#define CTRL_ALT_T LCA_T                                                        //    X     X
#define CTRL_SHIFT_T RCS_T                                                      //    X            X
#define CTRL_ALT_SHIFT MEH                                                      //    X     X      X
#define CTRL_WIN(kc) MT(MOD_LCTL | MOD_LGUI, kc)                                //    X                   X
#define WIN_SHIFT_T SGUI_T                                                      //                 X      X
#define ALT_SHIFT_T RSA_T                                                       //          X      X

#define WIN RGUI
#define CAPS_WORD QK_CAPS_WORD_TOGGLE

#define BASE_LAYER          0
#define CHARACTERS          1
#define CURSOR              2
#define KEY_COMBINATIONS    3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE_LAYER] = LONG_LAYOUT(

    _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_PRINT_SCREEN,                         _______, KC_6, KC_7, KC_8, KC_9, KC_0, WIN(KC_SPC),
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_DELETE,                                KC_INSERT, KC_Y, KC_U, KC_I, KC_O, CTRL_SHIFT_T(KC_P), CTRL_ALT_T(_______),
    KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_LEFT_GUI,                              _______, KC_H, KC_J, KC_K, KC_L, WIN_T(KC_SCLN), CTRL_WIN(KC_QUOTE),
    CAPS_WORD, KC_Z, KC_X, KC_C, KC_V, KC_B,                                        KC_N, KC_M, KC_COMM, KC_DOT, WIN_SHIFT_T(KC_SLSH), ALT_SHIFT_T(_______),
    _______, _______, _______, _______,                                             MO(KEY_COMBINATIONS), KC_LBRC, KC_RBRC, CTRL_ALT_SHIFT(_______),

    TT(CURSOR), KC_LCTL, LM(CURSOR, MOD_LSFT),                                      QK_LOCK, LCTL(KC_BSPC), TT(CHARACTERS),
    KC_LSFT, KC_BSPC, KC_ENT,                                                       LCTL(KC_ENTER), KC_RALT, KC_SPC
    
),

[CHARACTERS] = LONG_LAYOUT(

    _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, _______,                            _______, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
    _______, _______, _______, KC_CIRC, KC_BSLS, _______, _______,                  _______, _______, KC_UNDS, KC_QUOT, KC_DQUO, _______, KC_F12,
    _______, KC_DLR, KC_PLUS, KC_MINS, KC_ASTR, _______, _______,                   _______, KC_TILD, KC_AMPR, KC_PIPE, KC_EXLM, KC_EQL, _______,
    _______, KC_AT, KC_COLN, KC_HASH, KC_PERC, _______,                             _______, KC_GRV, _______, _______, _______, POINTER_DEREFERENCE,
    _______, _______, _______, _______,                                             _______, KC_LPRN, KC_RPRN, _______,

    _______, _______, _______,                                                      _______, _______, _______,
    KC_INSERT,KC_DELETE, _______,                                                   _______, _______, _______

),

[CURSOR] = LONG_LAYOUT(

    _______, LCTL(KC_HOME), LCTL(KC_PGDN), LCTL(KC_PGUP), LCTL(KC_END),             _______, _______, _______, _______, _______, _______, _______, _______, _______,
    LCTL(KC_F4), KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______,               _______, _______, KC_MS_WH_DOWN, KC_MS_U, KC_MS_WH_UP, _______, _______,
    _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, LCTL(KC_BSPC), _______,              _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
    _______, LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP), LCTL(KC_RGHT), _______,     _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,                                             _______, _______, _______, _______,

    _______, _______, _______,                                                      _______, KC_BTN1, KC_BTN2,
    _______, _______, _______,                                                      _______, _______, _______

),

[KEY_COMBINATIONS] = LONG_LAYOUT(

    QK_REBOOT, _______, _______, _______, _______, _______, _______,                  QK_BOOTLOADER, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,                                             _______, _______, _______, _______,

    _______, _______, _______,                                                      _______, _______, _______,
    _______, _______, _______,                                                      _______, _______, _______

)

};
