#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


extern uint8_t is_master;

#define _QWERTY 0
#define _RAISE 1
#define _EMOJI 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  RAISE,
  EMOJI,
};

enum unicode_name {
  TADA,
  HEART,
  COOL,
  MOON,
  SHRUG,
  SKULL,
  JOY,
  SMILE,
  OKAY,
  THINK,
  NEUT,
  GRIM,
  PTUP,
  PTLEFT,
  PTDOWN,
  PTRIGHT,
  FIRST,
  CHECK,
  NOPE,
  THMUP,
  THMDN,
  PRAY,
  WAVE,
  PEACE,
  HUG,
};

const uint32_t PROGMEM unicode_map[] = {
  [TADA] = 0x1F389, // 🎉
  [HEART] = 0x1F5A4, // 🖤
  [COOL] = 0x1F192, // 🆒
  [MOON] = 0x1F31D, // 🌝
  [SHRUG] = 0x1F937, // 🤷‍♂️
  [SKULL] = 0x2620, // ☠️
  [JOY] = 0x1F602, // 😂
  [SMILE] = 0x1F603, // 😃
  [OKAY] = 0x1F642, // 🙂
  [THINK] = 0x1F914, // 🤔
  [NEUT] = 0x1F611, // 😐
  [GRIM] = 0x1F62C, // 😬
  [PTUP] = 0x261D, // ☝️
  [PTLEFT] = 0x1F448, // 👈
  [PTDOWN] = 0x1F447, // 👇
  [PTRIGHT] = 0x1F449, // 👉
  [FIRST] = 0x1F947, // 🥇
  [CHECK] = 0x2705, // ✅
  [NOPE] = 0x274C, // ❌
  [THMUP] = 0x1F44D, // 👍
  [THMDN] = 0x1F44E, // 👎
  [PRAY] = 0x1F64F, // 🙏
  [WAVE] = 0x1F44B, // 👋
  [PEACE] = 0x270C, // ✌️
  [HUG] = 0x1F917 // 🫂
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
 *                   |   =  | LAlt | LGUI | /Space  /       \Space \  |RAISE |   [  |   ]  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

  [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,  KC_BSPC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT, \
                           KC_EQL, KC_LALT, KC_LGUI, KC_SPC,   KC_SPC,   RAISE,   KC_LBRC, KC_RBRC \
  ),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |      |  =   |  \   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |   7  |   8  |  9   |                    |   {  |  }   |  UP  |  [   |  ]   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |   4  |   5  |  6   |-------.    ,-------|      | Left | DOWN |Right |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |   1  |   2  |  3   |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |   0  |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

  [_RAISE] = LAYOUT( \
    KC_F1,   KC_F2,   KC_F3,  KC_F4,  KC_F5,   KC_F6,                        KC_F7,   KC_F8, _______,  KC_EQL, KC_BSLS, _______, \
    KC_F9,  KC_F10,  KC_F11,   KC_7,   KC_8,    KC_9,                      KC_LCBR, KC_RCBR,   KC_UP, KC_LBRC, KC_RBRC, _______, \
   KC_F12, _______, _______,   KC_4,   KC_5,    KC_6,                      _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
  _______, _______, _______,   KC_1,   KC_2,    KC_3,  _______, _______,   _______, _______, _______, _______, _______,  _______, \
                               KC_0,_______, _______,  _______, _______,  _______, _______, _______ \
  ),

  /* EMOJI
 *
 * NOTE: Not in use since unicode input doesn't work without changing keyboard
 * to "unicode hex input", but that disables left ALT, so it's not an option
 * since I use left ALT all the time.
 *
 * Input key for unicode hex input is supposedly customizable, but doesn't seem
 * to actually work, at least as described here:
 * https://beta.docs.qmk.fm/using-qmk/software-features/feature_unicode#input-key-configuration
 *
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |   ☝️  |     |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   🎉 |   🖤  |  🆒  |  🌝  |  🤷‍♂️  |  ☠️  |-------.    ,-------|   👈  |  👇  |  👉  |  🥇  |   ✅  |  ❌  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |  😂  |   😃  |  🙂  |  🤔  |  😐  |  😬  |-------|    |-------|  👍   |  👎  |  🙏  |  👋  |  ✌️   |  🫂  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_EMOJI] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                     _______, X(PTUP), _______, _______, _______, _______, \
  X(TADA), X(HEART), X(COOL),X(MOON),X(SHRUG), X(SKULL),                     X(PTLEFT), X(PTDOWN), X(PTRIGHT), X(FIRST), X(CHECK), X(NOPE), \
  X(JOY), X(SMILE), X(OKAY), X(THINK), X(NEUT), X(GRIM),  _______, _______,  X(THMUP), X(THMDN), X(PRAY), X(WAVE), X(PEACE), X(HUG), \
                             _______, _______, _______,  _______, _______,  _______, _______, _______ \
  )
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return rotation;
}

static void render_logo(void) {
  static const char PROGMEM my_logo[] = {
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

void oled_task_user(void) {
  // Todo: something fancier with the oled's
  // - Randomly pick from a selection of images?
  if (is_keyboard_master()) {
    render_logo();
  } else {
    render_logo();
  }
}

void matrix_init_user(void) {
    wait_ms(500); // give time for usb to initialize. Not sure this is needed?
    set_unicode_input_mode(UC_MAC);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case EMOJI:
      if (record->event.pressed) {
        layer_on(_EMOJI);
      } else {
        layer_off(_EMOJI);
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
  }
  return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            // Arrow down on raise, otherwise volume up.
            if (layer_state_is(_RAISE)) {
                tap_code(KC_PGDN);
            } else if (layer_state_is(_EMOJI)) {
                tap_code16(LGUI(KC_KP_PLUS));
            } else {
                tap_code(KC_VOLU);
            }
        } else {
            // Arrow up on raise, otherwise volume down.
            if (layer_state_is(_RAISE)) {
                tap_code(KC_PGUP);
            } else if (layer_state_is(_EMOJI)) {
                tap_code16(LGUI(KC_MINS));
            } else {
                tap_code(KC_VOLD);
            }
        }
    }
}
