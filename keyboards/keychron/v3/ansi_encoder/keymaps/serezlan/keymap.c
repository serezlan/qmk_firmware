/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <sys/types.h>

#include "action.h"
#include "action_layer.h"
#include "config.h"
#include "keycode.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "send_string_keycodes.h"
#include QMK_KEYBOARD_H

// clang-format off
enum layers {
  MAC_BASE,
  MAC_FN,
  MAC_MEDIA,
  MAC_SPACE,
  NAV_LAYER,
  WIN_BASE,
  WIN_FN
};

// Define a type for as many tap dance states as you need
typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP,
  TD_DOUBLE_HOLD } td_state_t;
// clang-format on

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    TD_GRV_MEDIA_LAYER,
    TD_SPACE_LAYER,
    TD_BSPC_INS,
    TD_DOUBLE_SEMI,
    TD_SHIFT_LOCK,
};

// clang-format on
// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void grv_media_layer_finished(tap_dance_state_t *state, void *user_data);
void grv_media_layer_reset(tap_dance_state_t *state, void *user_data);
void space_mac_space_finished(tap_dance_state_t *state, void *user_data);
void space_mac_space_reset(tap_dance_state_t *state, void *user_data);
void bspc_raise_layer_finished(tap_dance_state_t *state, void *user_data);
void bspc_raise_layer_reset(tap_dance_state_t *state, void *user_data);
void double_semi_finished(tap_dance_state_t *state, void *user_data);
void double_semi_reset(tap_dance_state_t *state, void *user_data);
void shift_lock_finished(tap_dance_state_t *state, void *user_data);
void shift_lock_reset(tap_dance_state_t *state, void *user_data);

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// --------------------
// MACRO
// --------------------
enum custom_keycodes {
    M_OPEN_NEW_TAB = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_OPEN_NEW_TAB:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_F10) SS_UP(X_LSFT) SS_DELAY(300) SS_TAP(X_DOWN) SS_TAP(X_ENTER) SS_DELAY(50) SS_TAP(X_TAB));
            } else {
                // when keycode QMKBEST is released
            }
            break;
    }
    return true;
};

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_tkl_f13_ansi(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_MUTE,  KC_PSCR,  KC_NO,    RM_NEXT,
        TD(TD_GRV_MEDIA_LAYER),   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        TD(TD_BSPC_INS),  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     TD(TD_DOUBLE_SEMI),  KC_QUOT,              KC_ENT,
        TD(TD_SHIFT_LOCK),            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LALT,  KC_LWIN,  KC_LCTL,                                TD(TD_SPACE_LAYER),                                 KC_RALT,  KC_RWIN,  MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_tkl_f13_ansi(
				   _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RM_VALD,  RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    RM_TOGG,  DT_UP,  DT_DOWN,  DT_PRNT,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

    [MAC_MEDIA] = LAYOUT_tkl_f13_ansi(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_MUTE,  KC_PSCR,  KC_NO,    RM_NEXT,
        _______,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_VOLD,     KC_MUTE,     KC_VOLU,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        KC_INS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_MPRV,     KC_MPLY,     KC_MNXT,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_RALT,  KC_LWIN,  KC_RCTL,                                KC_SPC,                                 KC_RALT,  KC_RWIN,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_SPACE] = LAYOUT_tkl_f13_ansi(
				   _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RM_VALD,  RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    RM_TOGG,  _______,  _______,  RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
				   _______,            _______,  _______,  _______,  _______,  _______,  M_OPEN_NEW_TAB,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

    [NAV_LAYER] = LAYOUT_tkl_f13_ansi(
				   _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RM_VALD,  RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    RM_TOGG,  _______,  _______,  RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,  _______,  KC_HOME,  KC_UP,  KC_END,  _______,  _______,  _______,    _______,  _______,  _______,  _______, 
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  _______,  _______,              _______,
				   _______,            _______,  _______,  _______,  _______,  _______,  M_OPEN_NEW_TAB,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_tkl_f13_ansi(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_MUTE,  KC_PSCR,  KC_NO,    RM_NEXT,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_tkl_f13_ansi(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RM_VALD,  RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    RM_TOGG,  _______,  _______,  RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_DOWN, KC_UP)},
    [MAC_FN]   = {ENCODER_CCW_CW(RM_VALD, RM_VALU)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = {ENCODER_CCW_CW(RM_VALD, RM_VALU)},
};
#endif // ENCODER_MAP_ENABLE

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed)
            return TD_SINGLE_TAP;
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (!state->pressed)
            return TD_DOUBLE_TAP;
        else
            return TD_DOUBLE_HOLD;
    } else
        return TD_UNKNOWN;
}

static bool is_shift_lock = false;
// Initialize tap structure associated with example tap dance key
static td_tap_t grv_media_layer_tap_state   = {.is_press_action = true, .state = TD_NONE};
static td_tap_t space_mac_space_tap_state = {.is_press_action = true, .state = TD_NONE};
static td_tap_t bspc_raise_layer_tap_state        = {.is_press_action = true, .state = TD_NONE};
static td_tap_t double_semi_tap_state     = {.is_press_action = true, .state = TD_NONE};
static td_tap_t shift_lock_tap_state      = {.is_press_action = true, .state = TD_NONE};

// --------------------
// implementation of our tap dance function
// --------------------

void grv_media_layer_finished(tap_dance_state_t *state, void *user_data) {
    grv_media_layer_tap_state.state = cur_dance(state);
    switch (grv_media_layer_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_GRV);
            break;
        case TD_SINGLE_HOLD:
            layer_on(MAC_MEDIA);
            break;
        default:
            break;
    }
}

void grv_media_layer_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (grv_media_layer_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(MAC_MEDIA);
    }
    grv_media_layer_tap_state.state = TD_NONE;
}

// ####################
void space_mac_space_finished(tap_dance_state_t *state, void *user_data) {
    space_mac_space_tap_state.state = cur_dance(state);
    switch (space_mac_space_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SPACE);
            break;
        case TD_SINGLE_HOLD:
            layer_on(NAV_LAYER);
            break;
        case TD_DOUBLE_HOLD:
            layer_on(MAC_SPACE);
            break;
        default:
            break;
    }
}

void space_mac_space_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    switch (space_mac_space_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_off(NAV_LAYER);
            break;
        case TD_DOUBLE_HOLD:
            layer_off(MAC_SPACE);
            break;
        default:
            break;
    }

    space_mac_space_tap_state.state = TD_NONE;
}

// ####################
void shift_lock_finished(tap_dance_state_t *state, void *user_data) {
    shift_lock_tap_state.state = cur_dance(state);
    switch (shift_lock_tap_state.state) {
        case TD_SINGLE_TAP: {
            if (is_shift_lock) {
                unregister_mods(MOD_BIT(KC_LSFT));
                is_shift_lock = false;
            }
        } break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_TAP: {
            if (is_shift_lock) {
                unregister_mods(MOD_BIT(KC_LSFT));
                is_shift_lock = false;
            } else {
                register_mods(MOD_BIT(KC_LSFT));
                is_shift_lock = true;
            }
        } break;
        default:
            break;
    }
}

void shift_lock_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (shift_lock_tap_state.state == TD_SINGLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LSFT));
    }
    shift_lock_tap_state.state = TD_NONE;
}

// ####################
void bspc_raise_layer_finished(tap_dance_state_t *state, void *user_data) {
    bspc_raise_layer_tap_state.state = cur_dance(state);
    switch (bspc_raise_layer_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_BSPC);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_INS);
            break;
        default:
            break;
    }
}

void bspc_raise_layer_reset(tap_dance_state_t *state, void *user_data) {
    if (bspc_raise_layer_tap_state.state == TD_SINGLE_HOLD) {
        unregister_code(KC_INS);
    }
    bspc_raise_layer_tap_state.state = TD_NONE;
}

// ####################
void double_semi_finished(tap_dance_state_t *state, void *user_data) {
    double_semi_tap_state.state = cur_dance(state);
    switch (double_semi_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SEMICOLON);
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING(SS_TAP(X_END) SS_TAP(X_SEMICOLON));
            break;
        default:
            break;
    }
}

void double_semi_reset(tap_dance_state_t *state, void *user_data) {
    double_semi_tap_state.state = TD_NONE;
}

// --------------------
// Associate our tap dance key with its functionality
// --------------------

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    [TD_GRV_MEDIA_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, grv_media_layer_finished, grv_media_layer_reset),
    [TD_SPACE_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, space_mac_space_finished, space_mac_space_reset),
    [TD_BSPC_INS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bspc_raise_layer_finished, bspc_raise_layer_reset),
    [TD_DOUBLE_SEMI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, double_semi_finished, double_semi_reset),
    [TD_SHIFT_LOCK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_lock_finished, shift_lock_reset),
};
// clang-format on

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            /* return 275; */
	  return TAPPING_TERM;
        default:
            return 140;
    }
}
