// Based off of "brandon" keymap
#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif
#include "action_tapping.h"
#include "version.h"

extern keymap_config_t keymap_config;

// Keymap layers
enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  KEYBOARD_LAYER
};

#define ___x___ KC_NO
#define _______ KC_TRNS

// Layer Defs
#define _QWERTY  0 // QUERTY layer
#define _LOWER   1 // Lower layer
#define _RAISE   2 // Raise layer
#define _CUSTOM 3  // Custom layer (LOWER + RAISE)
#define KEYBOARD_LAYER  4 
#define LALT_BRACE 5
#define LGUI_BRACE 6


#define WM_UP S(LALT(KC_K))
#define WM_DOWN S(LALT(KC_J))
#define WM_LEFT S(LALT(KC_H))
#define WM_RIGHT S(LALT(KC_L))


#define WM_F_UP S(LGUI(KC_K))
#define WM_F_DOWN S(LGUI(KC_J))
#define WM_F_LEFT S(LGUI(KC_H))
#define WM_F_RIGHT S(LGUI(KC_L))

#define WM_S_UP S(LALT(KC_W))
#define WM_S_DOWN S(LALT(KC_S))
#define WM_S_LEFT S(LALT(KC_A))
#define WM_S_RIGHT S(LALT(KC_D))


#define WM_M_UP LCTL(KC_UP)
#define WM_M_DOWN LCTL(KC_DOWN)
#define WM_M_LEFT LCTL(KC_LEFT)
#define WM_M_RIGHT LCTL(KC_RIGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer (Qwerty)
   *                ,-----------------------------------------------------------------------.
   *                | Esc | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   | BSPC|
   *                |-----------------------------------------------------------------------|
   *                | Tab | A   | S   | D   | F   | G   | H   | J   | K   | L   |;   |Enter | 
   *                |-----------------------------------------------------------------------|
   *   Tap for ( -- |Shift| Z   | X   | C   | V   | B   | N   | M   | ,   | .   | /   |Shift| -- Tap for )
   *                |-------------------------------------------------------------------------------------------------------------|
   *   Tap for [ -- |Ctrl | Tap-Gui("{") | Tap-Alt ("}") | Tap-KBfunc("]") | Lower |   Space   | Raise | Left  | Down | Up | Right|
   *                `-------------------------------------------------------------------------------------------------------------`
   */
  [_QWERTY] = {
    {KC_ESC,  KC_Q,           KC_W,          KC_E,    KC_R,  KC_T,   KC_Y,    KC_U,  KC_I,    KC_O,          KC_P,           KC_BSPC},
    {KC_TAB,  KC_A,           KC_S,          KC_D,    KC_F,  KC_G,   KC_H,    KC_J,  KC_K,    KC_L,          KC_SCLN,        KC_ENT},
    {KC_LSPO, KC_Z,           KC_X,          KC_C,    KC_V,  KC_B,   KC_N,    KC_M,  KC_COMM, KC_DOT,        KC_SLSH,        KC_RSPC},
    {LCTL_T(KC_LBRC), F(1), F(2), LT(KEYBOARD_LAYER, KC_RBRC), MO(_LOWER), KC_SPC, KC_SPC, TT(_RAISE), WM_F_LEFT, WM_F_DOWN, WM_F_UP, WM_F_RIGHT}
  },
  /* Symbols and Nav Layer
   *                ,-----------------------------------------------------------------------.
   *                |  ~  | 1  | 2    | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 0   |BSPC |
   *                |-----------------------------------------------------------------------|
   *                | TAB | =   | +   | -   | 5   | 5   |Left |Down | UP  |Right| ;   |  '  |
   *                |-----------------------------------------------------------------------|
   *                |Shift| -   | =   | `   | \   |  \  |  /  |  /  | ,   | .   | /   |Shift|
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     |   Space   |     |     |     |     |     |
   *                `-----------------------------------------------------------------------'
   */
  [_LOWER] = {
    {KC_TILD, KC_1,        KC_2,       KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,  KC_0,    KC_BSPC},
    {KC_TAB,  KC_EQL,         KC_PLUS,       KC_MINS, KC_5,    KC_5,   KC_LEFT,    KC_DOWN,    KC_UP,  KC_RIGHT, KC_SCLN,  KC_QUOT},
    {KC_LSPO, KC_MINS,        KC_EQL,        KC_GRV,  KC_BSLS, KC_PIPE, KC_SLSH, KC_SLSH, KC_COMM, KC_DOT,   KC_SLSH,     KC_RSPC},
    {_______, _______, _______, _______, _______, _______, _______, _______, WM_LEFT, WM_DOWN, WM_UP, WM_RIGHT}
  },

 /* GUI (mouse/media controls) layer
   *
   *        Mouse keys -----/```````````````````\               /```````````````````\----- Window manager
   *                ,-----------------------------------------------------------------------.
   *                |     |Ms B2|Ms Up|Ms B1|Ms WD|     |     |Prev | NW  |  N  | NE  |     |
   *                |-----------------------------------------------------------------------|
   *                |     |Ms L |Ms Dn|Ms R |Ms WU|     |     |Full |  W  |Centr|  E  |     |
   *                |-----------------------------------------------------------------------|
   *                |     |Ms WL|Ms B3|Ms WR|     |     |     |Next | SW  |  S  | SE  |     |
   *                |-----------------------------------------------------------------------|
   *                |     |Prev |Play |Next |Brig-|   Sleep   |Brig+|Mute |Vol- |Vol+ |     |
   *                `-----------------------------------------------------------------------'
   *                        \___ Media ___/   \___ Screen/sleep __/   \___ Volume __/
   */

  [_RAISE] = {
    {_______, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U, ___x___, ___x___, KC_7,    KC_8,    KC_9, KC_PLUS, KC_MINUS},
    {_______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, ___x___, ___x___, KC_4,   KC_5,  KC_6, KC_ASTERISK,   KC_SLASH},
    {_______, KC_VOLD, KC_MUTE, KC_VOLU, ___x___, ___x___, ___x___, KC_1,   KC_2,  KC_3, KC_0, KC_DOT},
    {_______, _______, _______, _______, _______, _______, _______, _______, WM_S_LEFT, WM_S_DOWN, WM_S_UP, WM_S_RIGHT}
  },
    /* Keyboard settings layer
   *                ,-----------------------------------------------------------------------.
   *    Firmware -- |     |Reset|     |     |     |     |     |     |     |     |     |     |
   *                |-----------------------------------------------------------------------|
   *   Set layer -- |     |Qwert|Colem|Steno| ... |     |     |     |     |     |     |     |
   *                |-----------------------------------------------------------------------|
   *       Audio -- |     |Voic-|Voic+|Mus +|Mus -|MIDI+|MIDI-|     |     |Aud +|Aud -|     |
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     |  Toggle   |     |Toggl| BL- | BL+ |     |
   *                `-----------------------------------------------------------------------'
   *                                                    \_____________\_ Backlight _/
   */
  [KEYBOARD_LAYER] = {
    {___x___, ___x___,   ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, RESET},
    {KC_CAPS, MU_MOD,  ___x___, ___x___,   ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___},
    {___x___, MUV_DE,  MUV_IN,  MU_ON,  MU_OFF, ___x___,   ___x___,  ___x___, ___x___, AU_ON,   AU_OFF,   ___x___},
    {___x___, ___x___, ___x___, _______, _______, ___x___, ___x___, _______, _______, ___x___,  ___x___,  ___x___}
  },


  [_CUSTOM] = {
    {___x___, ___x___,   ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, KC_NO},
    {KC_CAPS, MU_MOD,  ___x___, ___x___,   ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___},
    {___x___, MUV_DE,  MUV_IN,  MU_ON,  MU_OFF, ___x___,   ___x___,  ___x___, ___x___, AU_ON,   AU_OFF,   ___x___},
    {___x___, ___x___, ___x___, _______, _______, ___x___, ___x___, _______, WM_M_LEFT, WM_M_DOWN, WM_M_UP, WM_M_RIGHT}
  }
};

const uint16_t PROGMEM fn_actions[] = { 
  [1] = ACTION_MACRO_TAP(LGUI_BRACE),
  [2] = ACTION_MACRO_TAP(LALT_BRACE),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case LGUI_BRACE:
      if (record->event.pressed) {
        register_mods(MOD_LGUI);
      } else {
        unregister_mods(MOD_LGUI);
        if (record->tap.count && !record->tap.interrupted) {
          add_weak_mods(MOD_LSFT);
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          del_weak_mods(MOD_LSFT);
        }

        record->tap.count = 0;
      }
      break;
    case LALT_BRACE:
      if (record->event.pressed) {
        register_mods(MOD_LALT);
      } else {
        unregister_mods(MOD_LALT);
        if (record->tap.count && !record->tap.interrupted) {
          add_weak_mods(MOD_LSFT);
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
          del_weak_mods(MOD_LSFT);
        }

        record->tap.count = 0;
      }
      break;
    }
    return MACRO_NONE;
  }

uint32_t layer_state_set_user(uint32_t state) {
   state = update_tri_layer_state(state, _LOWER, _RAISE, _CUSTOM);
   return state;
 }