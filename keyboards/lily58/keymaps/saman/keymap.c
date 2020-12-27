#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _RAISE 1
#define _ADJUST 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  RAISE,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| MUTE  |    |BackSP |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |Enter |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |ADJUST| LAlt | LGUI | /Space  /       \Space \  |RAISE |   [  |   ]  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

  [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,  KC_BSPC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT, \
                            ADJUST, KC_LALT, KC_LGUI, KC_SPC,   KC_SPC,   RAISE,   KC_LBRC, KC_RBRC \
  ),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |   7  |   8  |  9   |                    | PGUP |      |  UP  |      |  [   |  ]   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |   4  |   5  |  6   |-------.    ,-------| PGDN | Left | DOWN |Right |  {   |  }   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |   1  |   2  |  3   |-------|    |-------|   -  |   +  |   =  |   \  |   |  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |   0  |  .   | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

  [_RAISE] = LAYOUT( \
  KC_F1,     KC_F2,    KC_F3, KC_F4,   KC_F5,  KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, \
  _______, _______, _______,   KC_7,   KC_8,    KC_9,                      KC_PGUP, _______,   KC_UP, _______, KC_LBRC, KC_RBRC, \
  _______, _______, _______,   KC_4,   KC_5,    KC_6,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_LCBR, KC_RCBR, \
  _______, _______, _______,   KC_1,   KC_2,    KC_3,  _______, _______,   KC_MINS, KC_PLUS,  KC_EQL, KC_BSLS, KC_PIPE, _______, \
                            _______,   KC_0,  KC_DOT,  _______, _______,  _______, _______, _______ \
  ),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |RGBTST|XMAS  |SNAKE |RAINBW|PLAIN |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |GRADE |KNIGHT|SWIRL |BREATH|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, RGB_M_T, RGB_M_X, RGB_M_SN, RGB_M_R, RGB_M_P, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_M_G, RGB_M_K, RGB_M_SW, RGB_M_B, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, \
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  )
};

int RGB_current_mode;

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

static void render_logo(void) {
  static const char PROGMEM my_logo[] = {
// 'lily58', 32x128px
// 'lily58', 128x32px
0x00, 0x7c, 0x82, 0x3e, 0xc2, 0x04, 0x08, 0x10, 0x60, 0xa0, 0x22, 0x24, 0x20, 0x20, 0x20, 0x20,
0x24, 0x24, 0x24, 0x22, 0x20, 0xe0, 0x20, 0x20, 0xe0, 0x22, 0x24, 0x22, 0x20, 0x20, 0x20, 0x20,
0x20, 0x22, 0x24, 0x24, 0x24, 0xa0, 0x40, 0x40, 0x40, 0x44, 0x48, 0x50, 0x40, 0x40, 0x40, 0x44,
0x48, 0x48, 0x44, 0x40, 0x40, 0x40, 0x70, 0x88, 0x84, 0xc2, 0xa2, 0xa2, 0x82, 0xc2, 0xbc, 0xc2,
0xa2, 0x92, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x92, 0x8a,
0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0xc4, 0xa4, 0x84, 0x84, 0x84, 0x84, 0x88,
0x90, 0xa0, 0xc0, 0x00, 0x08, 0x10, 0x20, 0x10, 0x08, 0x00, 0x80, 0x88, 0x90, 0x80, 0x80, 0x00,
0x00, 0x00, 0x00, 0xa8, 0x20, 0xd8, 0x20, 0xa8, 0x00, 0x00, 0x00, 0x10, 0x28, 0x40, 0x00, 0x00,
0x00, 0x00, 0x07, 0x08, 0x13, 0x5c, 0x90, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x20, 0x20, 0x20, 0x20, 0x23, 0x3c, 0x20, 0x21, 0x1e, 0x10, 0x10, 0x10, 0x10, 0x90, 0x50,
0x10, 0x10, 0x10, 0x20, 0x21, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xa0, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
0x02, 0x01, 0x00, 0xfc, 0x12, 0x09, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40,
0x80, 0x00, 0x00, 0xc0, 0x30, 0x88, 0xc4, 0x44, 0x8c, 0x32, 0xc8, 0x24, 0x10, 0x00, 0x00, 0xc0,
0x20, 0x10, 0x1f, 0xf0, 0x10, 0x08, 0x84, 0xd4, 0x16, 0xa5, 0x14, 0x04, 0x66, 0x15, 0x84, 0x04,
0xc4, 0x08, 0x10, 0xe0, 0x00, 0x08, 0xd0, 0x20, 0x10, 0x90, 0x90, 0x10, 0x20, 0xd0, 0x08, 0x00,
0x00, 0x00, 0xe0, 0x10, 0xc8, 0x3a, 0x09, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
0x08, 0x04, 0x04, 0x04, 0x04, 0xc4, 0x3c, 0x04, 0x84, 0x78, 0x08, 0x08, 0x08, 0x08, 0x09, 0x0a,
0x08, 0x08, 0x08, 0x04, 0x84, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02,
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x05, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
0x40, 0x80, 0x00, 0x3f, 0x48, 0x90, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02,
0x01, 0x00, 0x00, 0x03, 0x0c, 0x11, 0x23, 0x22, 0x31, 0x4c, 0x13, 0x24, 0x08, 0x00, 0x00, 0x03,
0x04, 0x08, 0xf8, 0x0f, 0x08, 0x10, 0x21, 0x2b, 0x68, 0xa5, 0x28, 0x20, 0x66, 0xa8, 0x21, 0x20,
0x23, 0x10, 0x08, 0x07, 0x00, 0x10, 0x0b, 0x04, 0x08, 0x09, 0x09, 0x08, 0x04, 0x0b, 0x10, 0x00,
0x00, 0x3e, 0x41, 0x7c, 0x43, 0x20, 0x10, 0x08, 0x06, 0x45, 0x24, 0x04, 0x04, 0x04, 0x04, 0x04,
0x24, 0x24, 0x24, 0x44, 0x04, 0x07, 0x04, 0x04, 0x07, 0x44, 0x24, 0x44, 0x04, 0x04, 0x04, 0x04,
0x04, 0x44, 0x24, 0x24, 0x24, 0x05, 0x02, 0x02, 0x02, 0x22, 0x12, 0x0a, 0x02, 0x02, 0x02, 0x22,
0x12, 0x12, 0x22, 0x02, 0x02, 0x02, 0x0e, 0x11, 0x21, 0x43, 0x45, 0x45, 0x41, 0x43, 0x3d, 0x43,
0x45, 0x49, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x49, 0x51,
0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x23, 0x25, 0x21, 0x21, 0x21, 0x21, 0x11,
0x09, 0x05, 0x03, 0x00, 0x10, 0x08, 0x04, 0x08, 0x10, 0x00, 0x01, 0x11, 0x09, 0x01, 0x01, 0x00,
0x00, 0x00, 0x00, 0x15, 0x04, 0x1b, 0x04, 0x15, 0x00, 0x00, 0x00, 0x08, 0x14, 0x02, 0x00, 0x00
  };

  oled_write_raw_P(my_logo, sizeof(my_logo));
}

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
          render_logo();

    // If you want to change the display of OLED, you need to change here
    // oled_write_ln(read_layer_state(), false);
    // oled_write_ln(read_keylog(), false);
    // oled_write_ln(read_keylogs(), false);


    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    render_logo();
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
  }
  return true;
}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            // Arrow down on raise, otherwise volume up.
            if (layer_state_is(_RAISE)) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_VOLU);
            }
        } else {
            // Arrow up on raise, otherwise volume down.
            if (layer_state_is(_RAISE)) {
                tap_code(KC_PGUP);
            } else {
                tap_code(KC_VOLD);
            }
        }

    }
}
#endif
