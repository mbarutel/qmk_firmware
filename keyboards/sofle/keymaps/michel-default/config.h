// Copyright 2024 Santosh Kumar (@santosh)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define TAPPING_TERM 180
#define QUICK_TAP_TERM 0
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS
// #define IGNORE_MOD_TAP_INTERRUPT
// Test these if still needed
// #define TAPPING_FORCE_HOLD
// #define RETRO_TAPPING

// Split settings: Sofle defaults use SPLIT_HAND_PIN; usually no need for EE_HANDS.
// If your halves get mis-detected, uncomment EE_HANDS and flash left/right EEPROMs.
// #define EE_HANDS

// Optional: combo config
// #define COMBO_COUNT 2
// #define COMBO_TERM 30

// Auto Shift
// #define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT 140
// #define AUTO_SHIFT_NO_SETUP

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64
