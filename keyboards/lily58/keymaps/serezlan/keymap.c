#include QMK_KEYBOARD_H

enum layer_number {
  _BASE = 0,
  _NAV,
  _SYMBOL,
  _NUMBER,
  _MULTIMEDIA,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,    KC_F6,                     KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_BSPC,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LALT, KC_LGUI, KC_LCTL, KC_SPC, KC_SPC, KC_RALT, KC_BSPC, KC_RGUI
),

[_NAV] = LAYOUT(
  XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
  XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
  XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                     KC_LEFT,    KC_UP,    KC_DOWN,    KC_RIGHT,    XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,    KC_HOME,    KC_PGUP, KC_PGDN,  KC_END,  XXXXXXX,
                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

[_NUMBER] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                        XXXXXXX,    KC_7,    KC_8,    KC_9,    XXXXXXX,    XXXXXXX,
  XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,                       XXXXXXX, KC_4, KC_5, KC_6,   XXXXXXX, XXXXXXX,
  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, KC_1, KC_2,  KC_3, KC_LBRC, KC_RBRC,
                             XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  KC_0, XXXXXXX, XXXXXXX
),
};

