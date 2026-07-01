// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "quantum.h"

#define ESC_LSFT MT(MOD_LSFT, KC_ESC)
#define SPC_MOU  LT(_MOU, KC_SPC)
#define ENT_NAV  LT(_NAV, KC_ENT)

#define DEL_NUM  LT(_NUM, KC_DEL)
#define BSCP_SYM LT(_SYM, KC_BSPC)
#define TAB_SHFT MT(MOD_RSFT, KC_TAB)


// Bottom Row Mods
#define Z_MED LT(_MED, KC_A)
#define X_GUI MT(MOD_LGUI, KC_X)
#define C_ALT MT(MOD_LALT, KC_C)
#define V_CTL MT(MOD_LCTL, KC_V)

#define M_CTL     MT(MOD_RCTL, KC_M)
#define COMMA_ALT MT(MOD_RALT, KC_COMMA)
#define DOT_GUI   MT(MOD_RGUI, KC_DOT)
#define SLSH_FUN  LT(_FUN, KC_O)

enum cheapino_layers {
    _BASE,
    _SYM,
    _MOU,
    _FUN,
    _MED,
    _NUM,
    _NAV,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_F, KC_P,  KC_G,                          KC_J,    KC_L,  KC_U, KC_Y, KC_QUOT,
        KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                          KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
        Z_MED,   X_GUI,   C_ALT,   V_CTL,    KC_B,                          KC_K,    M_CTL,  COMMA_ALT, DOT_GUI, SLSH_FUN,
                          ESC_LSFT,SPC_MOU, ENT_NAV,    DEL_NUM, BSCP_SYM, TAB_SHFT
    ),

    [_SYM] = LAYOUT_split_3x5_3(
       KC_LBRC, KC_AMPR, KC_ASTR, KC_EQUAL,KC_RBRC,                      _______, _______, _______, _______, _______,
       KC_LPRN, KC_DLR,  KC_PERC, KC_CIRC, KC_RPRN,                      RCTL(KC_B),KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
       KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_BSLS,                      _______, _______, _______, _______, _______,
                                  KC_SCLN, _______, KC_MINUS,   _______, _______, _______
    ),

    [_MOU] = LAYOUT_split_3x5_3(
       LCTL(KC_H), LCTL(LSFT(KC_F)), LCTL(KC_F), LCTL(LALT(KC_LEFT)), LCTL(LALT(KC_RIGHT)),              _______, _______, _______, _______, _______,
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, LCTL(KC_B),                    _______, MS_LEFT, MS_DOWN, MS_UP,  MS_RGHT,
       _______,_______,_______,_______,_______,                      _______, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR,
                                  _______, _______, _______,    MS_BTN1, MS_BTN2, MS_BTN3
    ),

    [_FUN] = LAYOUT_split_3x5_3(
       KC_F12,  KC_F7,   KC_F8,   KC_F9,   QK_BOOT,                      _______, _______, _______, _______, _______,
       KC_F11,  KC_F4,   KC_F5,   KC_F6,   _______,                      KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______,
       KC_F10,  KC_F1,   KC_F2,   KC_F3,   _______,                      _______, _______, _______, _______, _______,
                                  _______, _______, _______,    _______, _______, _______
    ),

    [_MED] = LAYOUT_split_3x5_3(
       _______, _______,  _______, _______, _______,                     SGUI(KC_ENT),SGUI(KC_B),SGUI(KC_R),SGUI(KC_Z),SGUI(KC_X),
       _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,                    _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
       _______, _______,  _______, _______, _______,                 _______, _______,  _______, _______, _______,
                                  _______, _______, _______,    KC_MSTP, KC_MPLY, KC_MUTE
    ),

    [_NUM] = LAYOUT_split_3x5_3(
       KC_SLSH, KC_7,    KC_8,    KC_9,    KC_PLUS,                      _______, _______, _______, _______, _______,
       KC_ASTR, KC_4,    KC_5,    KC_6,   KC_MINUS,                      RCTL(KC_B),KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
       KC_DOT,  KC_1,    KC_2,    KC_3,   KC_EQUAL,                      _______, _______, _______, _______, _______,
                                  KC_0,   _______, LSFT(KC_ENT),      _______, _______, _______
    ),

    [_NAV] = LAYOUT_split_3x5_3(
       LGUI(KC_Q), LGUI(KC_W), LGUI(KC_T), C(S(KC_TAB)),LCTL(KC_TAB),       KC_PSCR, _______, _______, _______, _______,
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,LCTL(KC_B),                    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT,
       LGUI(KC_Z), LGUI(KC_X),  LGUI(KC_C), LGUI(KC_V), LGUI(KC_A),                    _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                  _______, _______, _______,  RALT(KC_DEL),RALT(KC_BSPC), RSFT(KC_TAB)
    ),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPC_MOU:
        case Z_MED:
        case X_GUI:
        case C_ALT:
        case V_CTL:
        case M_CTL:
        case COMMA_ALT:
        case DOT_GUI:
        case SLSH_FUN:
            return 200;
        default:
            return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPC_MOU:
        case Z_MED:
        case X_GUI:
        case C_ALT:
        case V_CTL:
        case M_CTL:
        case COMMA_ALT:
        case DOT_GUI:
        case SLSH_FUN:
            return false;
        default:
            return true;
    }
}
