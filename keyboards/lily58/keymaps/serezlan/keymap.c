#include "action.h"
#include "modifiers.h"
#include QMK_KEYBOARD_H

enum layer_number {
  _BASE = 0,
  _FN,
  _RAISE,
  _SYMBOL,
  _NUMBER,
  _MEDIA,
  _FN2,
};

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
  TD_LSFT_INS = 0,
  QUOT_MEDIA_LAYR, // Our custom tap dance key; add any other tap dance keys to this enum 
  ALPHA_LAYER, 
  BETA_LAYER, 
  TD_CHARLIE_LAYER, 
  TD_DELTA_LAYER, 
};

// Declare the functions to be used with your tap dance key(s)
// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);
void charlie_finished(tap_dance_state_t *state, void *user_data);
void charlie_reset(tap_dance_state_t *state, void *user_data);
void delta_finished(tap_dance_state_t *state, void *user_data);
void delta_reset(tap_dance_state_t *state, void *user_data);

// combo keys
const uint16_t PROGMEM test_combo1[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END};

combo_t key_combos[] = {
    COMBO(test_combo1, KC_DEL),
    COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
  KC_BSPC,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, TD(QUOT_MEDIA_LAYR),
  TD(TD_CHARLIE_LAYER),  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  TD(TD_DELTA_LAYER),
  KC_LALT, KC_LGUI, KC_LCTL, TD(BETA_LAYER), KC_ENT, KC_SPC, TD(ALPHA_LAYER), KC_APPLICATION
),

[_RAISE] = LAYOUT(
  KC_ESC,   _______,   _______,    _______,    _______,    _______,                     _______,    _______,    _______,    _______,    _______,    _______,
  _______,   XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                     KC_LBRC,    KC_LPRN,    KC_RPRN,    KC_RBRC,    KC_BSLS,    XXXXXXX,
  _______,  XXXXXXX,   XXXXXXX,    XXXXXXX,    MO(_FN2),    XXXXXXX,                     KC_LEFT,    KC_UP,    KC_DOWN,    KC_RIGHT,    XXXXXXX, XXXXXXX,
  _______,  XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,  _______,  KC_HOME,    KC_PGUP,    KC_PGDN, KC_END,  XXXXXXX,  QK_LOCK,
  _______, _______, _______, _______, _______, _______, _______, _______ 
),

[_NUMBER] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                        KC_BSLS,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
  XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,                       KC_LBRC, KC_4, KC_5, KC_6,   KC_RBRC, XXXXXXX,
  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, KC_1, KC_2,  KC_3, KC_LBRC, KC_RBRC,
  XXXXXXX, XXXXXXX, XXXXXXX,  KC_LSFT, XXXXXXX,  KC_DOT, XXXXXXX, XXXXXXX
),

[_SYMBOL] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                        XXXXXXX,    KC_LBRC,    KC_RBRC,    XXXXXXX,    XXXXXXX,    XXXXXXX,
  XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,                       KC_BSLS, KC_LPRN, KC_RPRN, XXXXXXX,   KC_RBRC, XXXXXXX,
  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_RBRC,
  XXXXXXX, XXXXXXX, XXXXXXX,  KC_LSFT, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX
),

[_MEDIA] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,    KC_F6,                     KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,                     KC_MPRV,    KC_MPLY,    KC_MNXT,    XXXXXXX,    XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, _______,  _______,  KC_VOLD,    KC_MUTE,    KC_VOLU, XXXXXXX,  XXXXXXX,  XXXXXXX,
  KC_LALT, KC_LGUI, KC_LCTL, MO(_RAISE), KC_ENT, KC_SPC, KC_RALT, KC_RGUI
),

[_FN] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,    KC_F6,                     KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
  _______,   _______,   _______,    _______,    _______,    _______,                     _______,    _______,    _______,    _______,    _______,    _______,
  _______,  _______,   _______,    _______,    _______,    _______,                     _______,    _______,    _______,    _______,    _______, _______,
  _______,  _______,   _______,    _______,    _______,    _______, _______,  _______,  _______,    _______,    _______, _______,  _______,  _______, 
  _______, _______, _______, _______, _______, _______, _______, _______
),

[_FN2] = LAYOUT(
		XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
		XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                     KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
		XXXXXXX,  XXXXXXX,   KC_LALT,    KC_LGUI,    KC_LCTL,    XXXXXXX,                     KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5, KC_F6,
		_______,  XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, 
		_______, _______, _______, _______, _______, _______, _______, _______
),
};

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
	} else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    } else return TD_UNKNOWN;
}

// static vars
static bool insert_hold=false;
static bool isShift_lock=false;

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t alpha_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t beta_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t charlie_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t delta_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_QUOT);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_MEDIA);
            break;
    default:
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_MEDIA);
    }
    ql_tap_state.state = TD_NONE;
}

// alpha
void alpha_finished(tap_dance_state_t *state, void *user_data) {
    alpha_tap_state.state = cur_dance(state);
    switch (alpha_tap_state.state) {
        case TD_SINGLE_TAP:
	  register_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
	  register_mods(MOD_LALT);
            break;
    case TD_DOUBLE_HOLD:
	  register_mods(MOD_LALT|MOD_LGUI);
            break;
    default:
            break;
    }
}

void alpha_reset(tap_dance_state_t *state, void *user_data) {
      switch (alpha_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SPC); break;
        case TD_SINGLE_HOLD: unregister_mods(MOD_LALT); break;
        case TD_DOUBLE_HOLD: unregister_mods(MOD_LALT|MOD_LGUI); break;
        /* case TD_DOUBLE_TAP: unregister_code(KC_ESC); break; */
        /* case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break; */
        /* case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break; */
        default: break;
    }
    
    alpha_tap_state.state = TD_NONE;
}

// beta
void beta_finished(tap_dance_state_t *state, void *user_data) {
    beta_tap_state.state = cur_dance(state);
    switch (beta_tap_state.state) {
        /* case TD_SINGLE_TAP: */
            /* tap_code(KC_); */
            /* break; */
      case TD_SINGLE_TAP:
	  register_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_RAISE);
            break;
    case TD_DOUBLE_HOLD:
            layer_on(_FN2);
            break;
    default:
            break;
    }
}

void beta_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    switch (beta_tap_state.state ) {
              case TD_SINGLE_TAP: unregister_code(KC_SPC); break;

    case TD_SINGLE_HOLD:
        layer_off(_RAISE);
	break;
    case TD_DOUBLE_HOLD:
              layer_off(_FN2);
	      break;
    default:
      break;
    }
    
    beta_tap_state.state = TD_NONE;
}

// charlie
void charlie_finished(tap_dance_state_t *state, void *user_data) {
    charlie_tap_state.state = cur_dance(state);
    switch (charlie_tap_state.state) {
      case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
	  register_mods(MOD_LSFT);
            break;
    case TD_DOUBLE_TAP:
      if(insert_hold) {
	insert_hold=false;
	unregister_code(KC_INS);
      } else {
	insert_hold=true;
	register_code(KC_INS);
      }
     break;
    case TD_DOUBLE_HOLD:
            break;
    default:
            break;
    }
}

void charlie_reset(tap_dance_state_t *state, void *user_data) {
    switch (charlie_tap_state.state ) {
              case TD_SINGLE_TAP:
		break;
    case TD_SINGLE_HOLD:
      unregister_mods(MOD_LSFT);
	break;
    case TD_DOUBLE_HOLD:
	      break;
    default:
      break;
    }
    
    charlie_tap_state.state = TD_NONE;
}

// delta
void delta_finished(tap_dance_state_t *state, void *user_data) {
    delta_tap_state.state=cur_dance(state);
    switch (delta_tap_state.state){
        case TD_SINGLE_HOLD:
	  register_mods(MOD_LSFT);
            break;
    case TD_DOUBLE_TAP:
      if(isShift_lock) {
	isShift_lock=false;
	unregister_mods(MOD_LSFT);
      } else {
	isShift_lock=true;
	register_mods(MOD_LSFT);
      }
     break;
    default:
            break;
    }
}

void delta_reset(tap_dance_state_t *state, void *user_data) {
    switch (delta_tap_state.state ) {
    case TD_SINGLE_HOLD:
      unregister_mods(MOD_LSFT);
	break;
    default:
      break;
    }
    
    delta_tap_state.state = TD_NONE;
}
/********************/
// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_INS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_INS),
    [QUOT_MEDIA_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset),
    [ALPHA_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alpha_finished, alpha_reset),
    [BETA_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, beta_finished, beta_reset),
    [TD_CHARLIE_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, charlie_finished, charlie_reset),
    [TD_DELTA_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, delta_finished, delta_reset),
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}
