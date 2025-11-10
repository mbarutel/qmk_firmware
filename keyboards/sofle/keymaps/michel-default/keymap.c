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

enum sofle_layers {
    _BASE,
    _SYM,
    _MOU,
    _FUN,
    _MED,
    _NUM,
    _NAV
};

enum custom_keycodes {
    COLON_EQ = SAFE_RANGE,
};

const uint16_t PROGMEM left_ret[] = {KC_T, KC_D, COMBO_END};
const uint16_t PROGMEM left_ctrl[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM left_alt[] = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM left_gui[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM right_ctrl[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM right_alt[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM right_gui[] = {KC_COMMA, KC_M, COMBO_END};

combo_t key_combos[] = {
    COMBO(left_ret, KC_ENT),
    COMBO(left_ctrl, KC_LCTL),
    COMBO(left_alt, KC_LALT),
    COMBO(left_gui, KC_LGUI),
    COMBO(right_ctrl, KC_RCTL),
    COMBO(right_alt, KC_RALT),
    COMBO(right_gui, KC_RGUI),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT,  _______,
      _______,   KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,  _______,
      _______,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,      XXXXXXX,KC_K,    KC_M, KC_COMMA,  KC_DOT, KC_SLASH,  _______,
                     _______, _______, TAB_MED, ESC_MOU, SPC_NAV,        ENT_NUM,  BCSP_SYM, DEL_FUN, _______,_______
    ),
    [_SYM] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, KC_LBRC, KC_AMPR, KC_ASTR, KC_EQUAL, KC_RBRC,                   _______, _______, _______, _______, _______, _______,
      _______, KC_LPRN, KC_DLR, KC_PERC, KC_CIRC, KC_RPRN,                   RCTL(KC_B), KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______,
      _______, KC_GRV,  KC_EXLM, KC_AT, KC_HASH, KC_BSLS, _______, _______, _______, _______, _______, _______, _______,  _______,
                         _______, _______, COLON_EQ, KC_SCLN, KC_MINUS, _______, _______, _______, _______, _______
    ),
    [_MOU] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, _______, LSFT(KC_F2), LSFT(KC_F3), LSFT(KC_F4), _______, _______, RGUI(KC_G), RGUI(KC_E), RGUI(KC_I), RGUI(KC_SCLN), _______,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, LCTL(KC_B),                   _______, MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, _______,
      _______, LCTL(KC_A), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), _______, _______, _______, _______, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, _______,
                         _______, _______, _______, _______, _______, MS_BTN1, MS_BTN2, MS_BTN3, _______, _______
    ),
    [_FUN] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, KC_F12, KC_F7, KC_F8, KC_F9, _______,                   _______, _______, _______, _______, _______, _______,
      _______, KC_F11, KC_F4, KC_F5, KC_F6, _______,                   RCTL(KC_B), KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______,
      _______, KC_F10, KC_F1, KC_F2, KC_F3, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
                         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_MED] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                   KC_FIND, KC_PASTE, KC_COPY, KC_CUT, KC_UNDO, _______,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, LCTL(KC_B),                   _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, _______,
                         _______, _______, _______, _______, _______, KC_MSTP, KC_MPLY, KC_MUTE, _______, _______
    ),
    [_NUM] = LAYOUT(
      _______, _______, _______, _______,  _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, KC_SLSH, KC_7, KC_8, KC_9, KC_PLUS,                   _______, _______, _______, _______, _______, _______,
      _______, KC_ASTR, KC_4, KC_5, KC_6, KC_MINUS,                   RCTL(KC_B), KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______,
      _______, KC_DOT,  KC_1, KC_2, KC_3, KC_EQUAL, _______, _______, _______, _______, _______, _______, _______,  _______,
                         _______, _______, _______, KC_0, _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, LSFT(KC_F5), KC_F5, KC_F9, KC_F10, KC_F11,                     KC_PSCR, _______, _______, _______, _______, _______,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, LCTL(KC_B),                   KC_CAPS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,
      _______, TG(_NUM), _______, LCTL(KC_F7), KC_F12, LCTL(KC_F12), _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______,
                         _______, _______, _______, _______, _______, RSFT(KC_ENT), LCTL(KC_BSPC), LCTL(KC_DEL), _______, _______
    ),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SPC_NAV: case ENT_NUM:
            return 160;
  }
  return TAPPING_TERM;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SPC_NAV: case ENT_NUM:
      return false;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case COLON_EQ:
            if (record->event.pressed) {
                SEND_STRING(":=");
            }
            return false;
    }
    return true;
}

uint16_t get_autoshift_timeout(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_Q: case KC_A: case KC_Z:
    case KC_SCLN: case KC_O: case KC_SLSH:
      return 140;
  }

  return AUTO_SHIFT_TIMEOUT;
}
