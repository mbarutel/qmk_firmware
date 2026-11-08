// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "os_detection.h"

#define ESC_LSFT MT(MOD_LSFT, KC_ESC)
#define SPC_MOU  LT(_MOU, KC_SPC)
#define ENT_NAV  LT(_NAV, KC_ENT)

#define DEL_NUM  LT(_NUM, KC_DEL)
#define BSCP_SYM LT(_SYM, KC_BSPC)
#define TAB_SHFT MT(MOD_RSFT, KC_TAB)

// Bottom row mods
#define Z_GUI    MT(MOD_LGUI, KC_Z)
#define X_ALT    MT(MOD_LALT, KC_X)
#define C_CTL    MT(MOD_LCTL, KC_C)
#define V_MED    LT(_MED, KC_V)

#define M_FUN     LT(_FUN, KC_M)
#define COMMA_CTL MT(MOD_RCTL, KC_COMMA)
#define DOT_ALT   MT(MOD_RALT, KC_DOT)
#define SLSH_GUI  MT(MOD_RGUI, KC_SLSH)

enum cheapino_layers {
    _BASE,
    _SYM,
    _MOU,
    _FUN,
    _MED,
    _NUM,
    _NAV,
};

// Custom tap/hold keys, resolved by QMK's normal tapping logic.
// process_record_user() consumes both actions; no layer change occurs.
#define TH_FOC_L LT(0, KC_E)
#define TH_FOC_R LT(0, KC_I)

typedef struct {
    uint16_t keycode;
    uint16_t tap;
    uint16_t hold;
} tap_hold_t;

static const tap_hold_t tap_holds[] = {
    { TH_FOC_L, RGUI(KC_E), RGUI(KC_LEFT)  },
    { TH_FOC_R, RGUI(KC_I), RGUI(KC_RIGHT) },
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    for (uint8_t i = 0; i < ARRAY_SIZE(tap_holds); i++) {
        if (tap_holds[i].keycode != keycode) continue;

        uint16_t kc = record->tap.count ? tap_holds[i].tap
                                       : tap_holds[i].hold;
        if (record->event.pressed) {
            register_code16(kc);
        } else {
            unregister_code16(kc);
        }
        return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_F, KC_P,  KC_G,                          KC_J,    KC_L,  KC_U, KC_Y, KC_QUOT,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                          KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
        Z_GUI,   X_ALT,   C_CTL,   V_MED,    KC_B,                         KC_K,    M_FUN,   COMMA_CTL, DOT_ALT, SLSH_GUI,
                          ESC_LSFT,SPC_MOU, ENT_NAV,    DEL_NUM, BSCP_SYM, TAB_SHFT
    ),

    [_SYM] = LAYOUT_split_3x5_3(
       KC_LBRC, KC_AMPR, KC_ASTR, KC_EQUAL,KC_RBRC,                      _______, _______, _______, _______, _______,
       KC_LPRN, KC_DLR,  KC_PERC, KC_CIRC, KC_RPRN,                      RCTL(KC_B),KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
       KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_BSLS,                      _______, _______, _______, _______, _______,
                                  KC_SCLN, _______, KC_MINUS,   _______, _______, _______
    ),

    [_MOU] = LAYOUT_split_3x5_3(
       _______, LGUI(KC_TAB), LGUI(KC_F),TH_FOC_L, TH_FOC_R,              _______, _______, _______, _______, _______,
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
       LSFT(KC_F11), LCTL(KC_F11), KC_F7, _______, _______,                    _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
       LSFT(KC_F5), LCTL(LSFT(KC_F5)),  KC_F5, _______, _______,                 _______, _______,  _______, _______, _______,
                                  _______, _______, _______,    KC_MSTP, KC_MPLY, KC_MUTE
    ),

    [_NUM] = LAYOUT_split_3x5_3(
       KC_SLSH, KC_7,    KC_8,    KC_9,    KC_PLUS,                      _______, _______, _______, _______, _______,
       KC_ASTR, KC_4,    KC_5,    KC_6,   KC_MINUS,                      RCTL(KC_B),KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
       KC_DOT,  KC_1,    KC_2,    KC_3,   KC_EQUAL,                      _______, _______, _______, _______, _______,
                                  KC_0,   _______, LSFT(KC_ENT),      _______, _______, _______
    ),

    [_NAV] = LAYOUT_split_3x5_3(
       LGUI(KC_Q), LCTL(KC_W), LCTL(KC_T), C(S(KC_TAB)),LCTL(KC_TAB),       KC_PSCR, _______, _______, _______, _______,
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,LCTL(KC_B),                    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT,
       LCTL(KC_Z), LCTL(KC_X),  LCTL(KC_C), LCTL(KC_V), LCTL(KC_A),                    _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                  _______, _______, _______,  RCTL(KC_DEL),RCTL(KC_BSPC), RSFT(KC_TAB)
    ),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPC_MOU:
            return 200;
        case TH_FOC_L:
        case TH_FOC_R:
        case Z_GUI:
        case X_ALT:
        case C_CTL:
        case V_MED:
        case M_FUN:
        case COMMA_CTL:
        case DOT_ALT:
        case SLSH_GUI:
            return 250;
        default:
            return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPC_MOU:
        case Z_GUI:
        case X_ALT:
        case C_CTL:
        case V_MED:
        case M_FUN:
        case COMMA_CTL:
        case DOT_ALT:
        case SLSH_GUI:
            return false;
        default:
            return true;
    }
}

// uint16_t get_autoshift_timeout(uint16_t keycode, keyrecord_t *record) {
//   switch(keycode) {
//     case KC_Q: case KC_A: case KC_Z:
//     case KC_SCLN: case KC_O: case KC_SLSH:
//       return 160;
//   }

//   return AUTO_SHIFT_TIMEOUT;
// }
