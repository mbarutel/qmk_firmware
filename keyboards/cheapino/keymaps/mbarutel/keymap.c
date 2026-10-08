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
#define Z_GUI MT(MOD_LGUI, KC_Z)
#define X_ALT MT(MOD_LALT, KC_X)
#define C_CTL MT(MOD_LCTL, KC_C)
#define V_MED LT(_MED, KC_V)

#define M_FUN      LT(_FUN, KC_M)
#define COMMA_CTL  MT(MOD_RCTL, KC_COMMA)
#define DOT_ALT    MT(MOD_RALT, KC_DOT)
#define SLSH_GUI   MT(MOD_LGUI, KC_SLSH)

enum cheapino_layers {
    _BASE,
    _SYM,
    _MOU,
    _FUN,
    _MED,
    _NUM,
    _NAV,
};

// Custom tap/hold keys.
// Each key is LT(0, kc): layer 0 is _BASE so the hold does nothing on its own, and
// process_record_user() below sends `tap` or `hold` based on record->tap.count.
// These keys go through the normal tapping-term / hold-on-other-key-press logic,
// so they can be tuned in get_tapping_term() like the mod-taps.
// To add one: define a new LT(0, <unique basic keycode>) and add a row to tap_holds[].
#define TH_B      LT(0, KC_B)   // tap B,       hold ;
#define TH_K      LT(0, KC_K)   // tap K,       hold -
#define TH_FOC_L  LT(0, KC_E)   // tap Alt+E,   hold Ctrl+Alt+Left
#define TH_FOC_R  LT(0, KC_I)   // tap Alt+I,   hold Ctrl+Alt+Right

typedef struct {
    uint16_t keycode;
    uint16_t tap;
    uint16_t hold;
} tap_hold_t;

static const tap_hold_t tap_holds[] = {
    { TH_B,     KC_B,       KC_SCLN       },
    { TH_K,     KC_K,       KC_MINS       },
    { TH_FOC_L, LALT(KC_E), LCA(KC_LEFT)  },
    { TH_FOC_R, LALT(KC_I), LCA(KC_RIGHT) },
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    for (uint8_t i = 0; i < ARRAY_SIZE(tap_holds); i++) {
        if (tap_holds[i].keycode != keycode) continue;
        uint16_t kc = record->tap.count ? tap_holds[i].tap : tap_holds[i].hold;
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
        KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                          KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
        Z_GUI,   X_ALT,   C_CTL,   V_MED,    TH_B,                          TH_K,    M_FUN,  COMMA_CTL, DOT_ALT, SLSH_GUI,
                          ESC_LSFT,SPC_MOU, ENT_NAV,    DEL_NUM, BSCP_SYM, TAB_SHFT
    ),

    [_SYM] = LAYOUT_split_3x5_3(
       KC_LBRC, KC_AMPR, KC_ASTR, KC_EQUAL,KC_RBRC,                      _______, _______, _______, _______, _______,
       KC_LPRN, KC_DLR,  KC_PERC, KC_CIRC, KC_RPRN,                      RCTL(KC_B),KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
       KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_BSLS,                      _______, _______, _______, _______, _______,
                                  KC_SCLN, _______, KC_MINUS,   _______, _______, _______
    ),

    [_MOU] = LAYOUT_split_3x5_3(
       TH_FOC_L,LALT(KC_7),LALT(KC_8),LALT(KC_9),TH_FOC_R,                     _______, _______, _______, _______, _______,
       LALT(LCTL(KC_B)),LALT(KC_4),LALT(KC_5),LALT(KC_6),LALT(KC_F),                    _______, MS_LEFT, MS_DOWN, MS_UP,  MS_RGHT,
       LALT(LCTL(KC_S)),LALT(KC_1),LALT(KC_2),LALT(KC_3),LALT(LCTL(KC_F)),                     _______, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR,
                                  LALT(KC_0), _______, LALT(LSFT(KC_0)),    MS_BTN1, MS_BTN2, MS_BTN3
    ),

    [_FUN] = LAYOUT_split_3x5_3(
       KC_F12,  KC_F7,   KC_F8,   KC_F9,   QK_BOOT,                      _______, _______, _______, _______, _______,
       KC_F11,  KC_F4,   KC_F5,   KC_F6,   _______,                      _______, _______, _______, _______, _______,
       KC_F10,  KC_F1,   KC_F2,   KC_F3,   _______,                      _______, _______, _______, _______, _______,
                                  _______, _______, _______,    _______, _______, _______
    ),

    [_MED] = LAYOUT_split_3x5_3(
       _______, _______,  _______, _______, _______,                     SGUI(KC_ENT),SGUI(KC_B),SGUI(KC_R),SGUI(KC_Z),SGUI(KC_X),
       LSFT(KC_F11), LCTL(KC_F11),  KC_F7, _______, _______,                    _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
       LSFT(KC_F5), LGUI(LSFT(KC_F5)),  KC_F5, _______, _______,                 _______, _______,  _______, _______, _______,
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
            return 200;
        case V_MED:
        case M_FUN:
            return 180;
        case Z_GUI:
        case X_ALT:
        case C_CTL:
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
