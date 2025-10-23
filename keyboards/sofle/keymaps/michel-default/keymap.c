// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "quantum.h"

#define SPC_NAV  LT(_NAV, KC_SPC)
#define ENT_NUM  LT(_NUM, KC_ENT)
#define BCSP_SYM LT(_SYM, KC_BSPC)
#define ESC_MOU LT(_MOU, KC_ESC)
#define TAB_MED LT(_MED, KC_TAB)
#define DEL_FUN LT(_FUN, KC_DEL)

// #define HM_Z LGUI_T(KC_Z)
// #define HM_X LALT_T(KC_X)
// #define HM_C LCTL_T(KC_C)
// #define HM_V LSFT_T(KC_V)
//
// #define HM_SLASH RGUI_T(KC_SLASH)
// #define HM_DOT RALT_T(KC_DOT)
// #define HM_COMMA RCTL_T(KC_COMMA)
// #define HM_M RSFT_T(KC_M)
/*#define ESC_GUI  MT(MOD_LGUI, KC_ESC)*/
/*#define SCLN_GUI MT(MOD_RGUI, KC_SCLN)*/

// #define BCSP_SHFT  MT(MOD_RSFT, KC_BSPC)
// #define CBCSP_SHFT  MT(MOD_RSFT, LCTL(KC_BSPC))

// #define EQUAL_SHFT  MT(MOD_LSFT, KC_EQUAL)

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _BASE,
    _NUM,
    _SYM,
    _NAV,
    _MOU,
    _FUN,
    _MED
};

// enum custom_keycodes {
    // TMUX_SHFT = SAFE_RANGE,
    // QUOTE_GRV,
    // MOU_BSPC,
    // SHFT_BSPC = SAFE_RANGE
// };

// typedef struct {
//     bool     down;
//     bool     hold;
//     uint16_t timer;
// } dual_state_t;

// typedef struct {
//     bool     down;
//     uint16_t timer;
// } single_state_t;

// static dual_state_t shft = {0};
// static dual_state_t tmux = {0};
// static dual_state_t mb = {0};
// static single_state_t qg = {0};

// const uint16_t PROGMEM left_ctrl[] = {KC_S, KC_T, COMBO_END};
// const uint16_t PROGMEM left_alt[] = {KC_T, KC_D, COMBO_END};
// const uint16_t PROGMEM left_sft[] = {KC_M, KC_E, COMBO_END};
// const uint16_t PROGMEM right_ctrl[] = {KC_N, KC_E, COMBO_END};
// const uint16_t PROGMEM right_alt[] = {KC_N, KC_H, COMBO_END};
// const uint16_t PROGMEM right_sft[] = {KC_V, KC_S, COMBO_END};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT,  _______,
      _______,   KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,  _______,
      _______,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,      XXXXXXX,KC_K,    KC_M, KC_COMMA,  KC_DOT, KC_SLASH,  _______,
                     _______, _______, TAB_MED, ESC_MOU, SPC_NAV,        ENT_NUM,  BCSP_SYM, DEL_FUN, _______,_______
    ),
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, LSFT(KC_F5), KC_F5, KC_F9, KC_F10, KC_F11,                     KC_PSCR, _______, _______, _______, _______, _______,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_BSPC,                   KC_CAPS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,
      _______, _______, _______, LCTL(KC_F7), KC_F12, LCTL(KC_F12), _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______,
                         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_SYM] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, KC_LBRC, KC_AMPR, KC_ASTR, KC_EQUAL, KC_RBRC,                   _______, _______, _______, _______, _______, _______,
      _______, KC_LPRN, KC_DLR, KC_PERC, KC_CIRC, KC_RPRN,                   KC_BSPC, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______,
      _______, KC_GRV,  KC_EXLM, KC_AT, KC_HASH, KC_BSLS, _______, _______, _______, _______, _______, _______, _______,  _______,
                         _______, _______, KC_PLUS, KC_SCLN, KC_MINUS, _______, _______, _______, _______, _______
    ),
    [_NUM] = LAYOUT(
      _______, _______, _______, _______,  _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, KC_SLSH, KC_7, KC_8, KC_9, KC_PLUS,                   _______, _______, _______, _______, _______, _______,
      _______, KC_ASTR, KC_4, KC_5, KC_6, KC_MINUS,                   KC_BSPC, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______,
      _______, KC_DOT,  KC_1, KC_2, KC_3, KC_EQUAL, _______, _______, _______, _______, _______, _______, _______,  _______,
                         _______, _______, _______, KC_0, _______, _______, _______, _______, _______, _______
    ),
    [_MOU] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, _______, LSFT(KC_F2), LSFT(KC_F3), LSFT(KC_F4), _______,                   _______, _______, _______, _______, _______, _______,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_BSPC,                   _______, MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, _______,
                         _______, _______, _______, _______, _______, MS_BTN1, MS_BTN2, MS_BTN3, _______, _______
    ),
    [_FUN] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, KC_F12, KC_F7, KC_F8, KC_F9, _______,                   _______, _______, _______, _______, _______, _______,
      _______, KC_F11, KC_F4, KC_F5, KC_F6, _______,                   KC_BSPC, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______,
      _______, KC_F10, KC_F1, KC_F2, KC_F3, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
                         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_MED] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                   KC_FIND, KC_PASTE, KC_COPY, KC_CUT, KC_UNDO, _______,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_BSPC,                   _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, _______,
                         _______, _______, _______, _______, _______, KC_MSTP, KC_MPLY, KC_MUTE, _______, _______
    ),
};

// uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case HM_Z: return 250;   // Pinky
//     case HM_X: return 250;   // Ring
//     case HM_C: return 250;   // Middle
//     case HM_V: return 250;   // Index
//     case HM_M: return 250;
//     case HM_COMMA: return 250;
//     case HM_DOT: return 250;
//     case HM_SLASH: return 250;
//   }
//   return TAPPING_TERM;
// }

// bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case HM_Z: case HM_X: case HM_C: case HM_V:
//     case HM_M: case HM_COMMA: case HM_DOT: case HM_SLASH:
//       return false;  // Only for HRMs (keeps other Mod-Taps normal)
//   }
//   return true;
// }

// bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case HM_A: case HM_R: case HM_S: case HM_T:
//     case HM_N: case HM_E: case HM_I: case HM_O:
//       return true;
//   }
//   return false;
// }

// If you like quick re-taps to *always* be taps on HRMs:
// uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case HM_A: case HM_R: case HM_S: case HM_T:
//     case HM_N: case HM_E: case HM_I: case HM_O:
//       return 150; // per-key quick-tap window
//   }
//   return QUICK_TAP_TERM;
// }
