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

// Tap Dance declarations
enum {
    TD_FOCUS_LEFT,    // Tap: LALT(KC_N), Hold: LALT(KC_G)
    TD_FOCUS_RIGHT,   // Tap: LALT(KC_O), Hold: LALT(KC_SCLN)
};

// Tap Dance state
typedef struct {
    bool is_press_action;
    uint8_t state;
} tap_state_t;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    // DOUBLE_HOLD,
    // DOUBLE_SINGLE_TAP,
    // MORE_TAPS
};

// Function to determine the current tap dance state
static uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    }
    // } else if (state->count == 2) {
        // if (state->interrupted) return DOUBLE_SINGLE_TAP;
        // else if (state->pressed) return DOUBLE_HOLD;
        // else return DOUBLE_TAP;
    // }
    return DOUBLE_TAP;
}

// TD_E_LEFT tap dance functions
static tap_state_t td_focus_left_state = {
    .is_press_action = true,
    .state = 0
};

void td_focus_left_finished(tap_dance_state_t *state, void *user_data) {
    td_focus_left_state.state = dance_step(state);
    switch (td_focus_left_state.state) {
        case SINGLE_TAP:
            register_code(KC_LALT);
            register_code(KC_N);
            break;
        case SINGLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LEFT);
            break;
    }
}

void td_focus_left_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_focus_left_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_N);
            unregister_code(KC_LALT);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LEFT);
            unregister_code(KC_LCTL);
            break;
    }
    td_focus_left_state.state = 0;
}

// TD_I_RIGHT tap dance functions
static tap_state_t td_focus_right_state = {
    .is_press_action = true,
    .state = 0
};

void td_focus_right_finished(tap_dance_state_t *state, void *user_data) {
    td_focus_right_state.state = dance_step(state);
    switch (td_focus_right_state.state) {
        case SINGLE_TAP:
            register_code(KC_LALT);
            register_code(KC_O);
            break;
        case SINGLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_RIGHT);
            break;
    }
}

void td_focus_right_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_focus_right_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_O);
            unregister_code(KC_LALT);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_RIGHT);
            unregister_code(KC_LCTL);
            break;
    }
    td_focus_right_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_FOCUS_LEFT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_focus_left_finished,  td_focus_left_reset),
    [TD_FOCUS_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_focus_right_finished, td_focus_right_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_F, KC_P,  KC_G,                          KC_J,    KC_L,  KC_U, KC_Y, KC_QUOT,
        KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                          KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
        Z_GUI,   X_ALT,   C_CTL,   V_MED,    KC_B,                          KC_K,    M_FUN,  COMMA_CTL, DOT_ALT, SLSH_GUI,
                          ESC_LSFT,SPC_MOU, ENT_NAV,    DEL_NUM, BSCP_SYM, TAB_SHFT
    ),

    [_SYM] = LAYOUT_split_3x5_3(
       KC_LBRC, KC_AMPR, KC_ASTR, KC_EQUAL,KC_RBRC,                      _______, _______, _______, _______, _______,
       KC_LPRN, KC_DLR,  KC_PERC, KC_CIRC, KC_RPRN,                      RCTL(KC_B),KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
       KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_BSLS,                      _______, _______, _______, _______, _______,
                                  KC_SCLN, _______, KC_MINUS,   _______, _______, _______
    ),

    [_MOU] = LAYOUT_split_3x5_3(
       _______, _______, LALT(KC_F), TD(TD_FOCUS_LEFT), TD(TD_FOCUS_RIGHT),              _______, _______, _______, _______, _______,
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, LCTL(KC_B),                    _______, MS_LEFT, MS_DOWN, MS_UP,  MS_RGHT,
       _______,_______,_______,_______,_______,                      _______, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR,
                                  _______, _______, _______,    MS_BTN1, MS_BTN2, MS_BTN3
    ),

    [_FUN] = LAYOUT_split_3x5_3(
       KC_F12,  KC_F7,   KC_F8,   KC_F9,   QK_BOOT,                      _______, _______, _______, _______, _______,
       KC_F11,  KC_F4,   KC_F5,   KC_F6,   _______,                      _______, _______, _______, _______, _______,
       KC_F10,  KC_F1,   KC_F2,   KC_F3,   _______,                      _______, _______, _______, _______, _______,
                                  _______, _______, _______,    _______, _______, _______
    ),

    [_MED] = LAYOUT_split_3x5_3(
       _______, _______,  _______, _______, _______,                     SGUI(KC_ENT),SGUI(KC_B),SGUI(KC_R),SGUI(KC_Z),SGUI(KC_X),
       _______, _______,  _______, _______, _______,                    _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
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
            return 140;
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
