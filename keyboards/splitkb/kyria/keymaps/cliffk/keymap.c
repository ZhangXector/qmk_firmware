/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _SYMNUM,
    _SPEC,
    _ARROWS,
    _GAME,
    _FUNC,
};

#define SFT_ESC  SFT_T(KC_ESC)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_SPC  ALT_T(KC_SPC)
#define SFT_ENT  SFT_T(KC_ENT)

#define SYMNUM LT(_SYMNUM, KC_SPC)
#define SPEC LT(_SPEC, KC_ESC)
#define L_ARRW LT(_ARROWS, KC_A)
#define R_ARRW LT(_ARROWS, KC_O)
#define ENT_FN LT(_FUNC, KC_ENT)
#define CTL_QU RCTL_T(KC_QUOT)
#define TO_BSE TO(_BASE)
#define TO_GME TO(_GAME)

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record)
{
	switch (keycode)
	{
		case RCTL_T(KC_QUOT):
			return TAPPING_TERM + 500;
		default:
			return TAPPING_TERM;
	}
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base (Colemak)
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   F  |   P  |   G  |                              |   J  |   L  |   U  |   Y  |   ;  |    \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Ctrl  |   A  |   R  |   S  |   T  |   D  |                              |   H  |   N  |   E  |   I  |   O  |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |      |  |  Del | Menu |   K  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Meta | LAlt |SP/SYM|ENT/FN|ESCSPC|  |ESCSPC| Bksp |SP/SYM| RAlt | Meta |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT(
     KC_TAB,   KC_Q,   KC_W,   KC_F,    KC_P,    KC_G,                                          KC_J,   KC_L,   KC_U,    KC_Y,   KC_SCLN, KC_BSLS,
     KC_LCTL,  L_ARRW, KC_R,   KC_S,    KC_T,    KC_D,                                          KC_H,   KC_N,   KC_E,    KC_I,   R_ARRW,  CTL_QU,
     KC_LSFT,  KC_Z,   KC_X,   KC_C,    KC_V,    KC_B,   _______,_______,     KC_DEL,  KC_APP,  KC_K,   KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                               KC_LGUI, KC_LALT, SYMNUM, ENT_FN, SPEC,        SPEC   , KC_BSPC, SYMNUM, KC_RALT,KC_RGUI
    ),

/*
 * Symbols/Numbers
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    =   |  !   |  @   |  {   |  }   |  &   |                              |   /  |  7   |  8   |  9   |      |   -    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |   *  |  4   |  5   |  6   |  +   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |      |      |      |  |      |      | NUMLK|  1   |  2   |  3   | ENTER|        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |  0   |  .   |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMNUM] = LAYOUT(
     KC_EQL,   KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_AMPR,          	                           KC_PSLS, KC_P7,   KC_P8,   KC_P9,  _______, KC_MINS,
     _______,  KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,           	                           KC_PAST, KC_P4,   KC_P5,   KC_P6,  KC_PPLS, _______,
     _______,  KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, _______, _______, 	_______, _______, _______, KC_NUM,  KC_P1,   KC_P2,   KC_P3,  KC_PENT, _______,
                                 _______, _______, _______, _______, 	_______, _______, _______, _______, KC_P0,   KC_PDOT
    ),

/*
 * Specials
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | Vol+ |      | Calc | PrScr|      | GAME   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              | Home | PgDn | PgUp |  End | Caps |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      | Vol- | Prev | Play | Next | ScrLk|        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SPEC] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                    	                  KC_VOLU, _______, KC_CALC, KC_PSCR, _______, TO_GME,
      _______, _______, _______, _______, _______, _______,                    	                  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_CAPS, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, 	_______, _______, KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, KC_SCRL, _______,
                                 _______, _______, _______, _______, _______, 	_______, _______, _______, _______, _______
    ),

/*
 * Arrows
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |  Up  |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Left | Down | Right|      |                              | Left | Down |  Up  | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ARROWS] = LAYOUT(
      _______, _______, _______, KC_UP,   _______, _______,                   	                  _______, _______, _______, _______, _______, _______,
      _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______,                   	                  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, 	_______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, 	_______, _______, _______, _______, _______
    ),

/*
 * Gaming
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    T   | Tab  |   Q  |   W  |   E  |   R  |                              |      |      |      |      |      |  BASE  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    H   | Shift|   A  |   S  |   D  |   F  |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    I   | Ctrl |   Z  |   X  |   C  |   V  |   G  |   B  |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |   M  | ALT  | SPC  |      | ESC  |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME] = LAYOUT(
      KC_T,   KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,                 	                 	  _______, _______, _______, _______, _______, TO_BSE,
      KC_H,   KC_LSFT, KC_A,  KC_S,    KC_D,    KC_F,                   	                  _______, _______, _______, _______, _______, _______,
      KC_I,   KC_LCTL, KC_Z,  KC_X,    KC_C,    KC_V,   KC_G,    KC_B, 		_______, _______, _______, _______, _______, _______, _______, _______,
                              KC_M,    KC_LALT, KC_SPC, _______, KC_ESC, 	_______, _______, _______, _______, _______
    ),

/*
 * Functions
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F10 |  F7  |  F8  |  F9  |      |                              |      |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F11 |  F4  |  F5  |  F6  |      |                              |      |  F4  |  F5  |  F6  |  F11 |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F12 |  F1  |  F2  |  F3  |      |      |      |  |      |      |      |  F1  |  F2  |  F3  |  F12 |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNC] = LAYOUT(
      _______,  KC_F10,  KC_F7,  KC_F8,   KC_F9,   _______,                  	                  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______,  KC_F11,  KC_F4,  KC_F5,   KC_F6,   _______,                  	                  _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,
      _______,  KC_F12,  KC_F1,  KC_F2,   KC_F3,   _______, _______, _______, 	_______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______,
                                 _______, _______, _______, _______, _______, 	_______, _______, _______, _______, _______
    )

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev2.1\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _BASE:
                oled_write_P(PSTR("Colemak\n"), false);
                break;
            case _SYMNUM:
                oled_write_P(PSTR("Symbols\n"), false);
                break;
            case _SPEC:
                oled_write_P(PSTR("Special\n"), false);
                break;
            case _ARROWS:
                oled_write_P(PSTR("Arrows\n"), false);
                break;
            case _GAME:
                oled_write_P(PSTR("Game\n"), false);
                break;
            case _FUNC:
                oled_write_P(PSTR("Function\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
    	static const char PROGMEM lotus_logo[] = {
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,248,248,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,192,224,240,248,252,255,255,255,255,252,248,240,224,224,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 15,  8,  8,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,240,248,252,252,254,255,255,255,255,255,127,127, 63, 31, 15,  7,  7, 15, 31, 63,127,127,255,255,255,255,255,254,252,252,248,240,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,248,252,  4,  4,252,248,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
			0,  0,  0,  0,  0, 16,112,224,224,192,192,192,192,192,224,224,224,224,240,240,240,240,252,254,255,255,255,255,127, 63, 63, 31, 15, 15,  7,  3,  3,  1,129,128,192,192,224,240,248,255,255,248,240,224,192,192,128,129,  1,  3,  3,  7, 15, 15, 31, 63, 63,127,255,255,255,255,254,252,240,240,240,240,224,224,224,224,192,192,192,192,192,224,224,112, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 65,241,241, 65, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
			0,  0,  0,  0,  0,  0,192,255,255,255,255,255,  3,  7,  7, 99,195,195,195,207,255,255,255,255,  7,  3,  1,  0,  0,192,224,240,248,252,252,254,126, 63, 63, 31, 31, 15, 15,  7,131,225,225,131,  7, 15, 15, 31, 31, 63, 63,126,254,252,252,248,240,224,192,  0,  0,  1,  3,  7,255,255,255,255,207,195,195,195,227,  7,  7,  3,251,255,255,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 31, 16, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
			0,  0,  0,  0,  0,252,255,255,255, 63,  7,  0,  0,  0,  0,240,255,255,127,  3,  3,  3,  7, 15, 24, 32, 64,  0, 31,127,255,  7,  3,  1,  0,192,240,240,120, 60, 60, 30, 31, 15,  7,  3,  3,  7, 15, 31, 30, 62, 60,120,248,240,192,  0,  1,  3,  7,255,127, 31,  0,  0, 32, 24, 15,  7,  3,  3,  3,127,255,255,240,  0,  0,  0,  0,  7, 63,255,255,255,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,252,252,  0,  0,252,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
			0,  0,  0,  0,  0, 15, 63,127,255,248,192,128,  0,  0,  0, 31, 63,127,224,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  4,  0,  0,  3, 15, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16, 15,  3,  0,  0,  4,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,127, 63, 31,  0,  0,  0,128,192,248,255,127, 31,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,193, 65, 65, 65,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
			0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  3,  3,  2,  2,  6,  6,  4,  4,  5, 13,  9,  9,  9,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  9,  9, 13,  5,  4,  4,  6,  6,  2,  2,  3,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9, 19, 19, 18, 30, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		};
        // clang-format on
        oled_write_raw_P(lotus_logo, sizeof(lotus_logo));
    }
    return false;
}
#endif

/* DELETE THIS LINE TO UNCOMMENT (1/2)
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
DELETE THIS LINE TO UNCOMMENT (2/2) */
