#include QMK_KEYBOARD_H
#include "keymap_steno.h"

#define _BASE 0
#define _SYMNUM 1
#define _SPEC 2
#define _ARROWS 3
#define _FUNC 4
#define _STENO 5

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
#define TO_STN TO(_STENO)

const rgblight_segment_t PROGMEM my_default_layer[] = RGBLIGHT_LAYER_SEGMENTS({0,1,HSV_BLACK});
const rgblight_segment_t PROGMEM symnum_layer[] = RGBLIGHT_LAYER_SEGMENTS({0,1,HSV_RED});
const rgblight_segment_t PROGMEM spec_layer[] = RGBLIGHT_LAYER_SEGMENTS({0,1,HSV_BLUE});
const rgblight_segment_t PROGMEM arrows_layer[] = RGBLIGHT_LAYER_SEGMENTS({0,1,HSV_GREEN});
const rgblight_segment_t PROGMEM func_layer[] = RGBLIGHT_LAYER_SEGMENTS({0,1,HSV_PURPLE});
const rgblight_segment_t PROGMEM steno_layer[] = RGBLIGHT_LAYER_SEGMENTS({0,1,HSV_TEAL});

const rgblight_segment_t* const PROGMEM my_rgblight_layers[] = RGBLIGHT_LAYERS_LIST(
	my_default_layer,
	symnum_layer,
	spec_layer,
	arrows_layer,
	func_layer,
	steno_layer
);

void eeconfig_init_user()
{
	steno_set_mode(STENO_MODE_GEMINI);
}

void keyboard_post_init_user(void)
{
	rgblight_layers = my_rgblight_layers;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (Colemak)
     * +-----------------------------------------+                             +-----------------------------------------+
     * | TAB  |   q  |   w  |   f  |   p  |   g  |                             |   j  |   l  |   u  |   y  |   ;  |   \  |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | CTRL |a/ARRW|   r  |   s  |   t  |   d  |                             |   h  |   n  |   e  |   i  |o/ARRW| '/CTL|
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | SHFT |   z  |   x  |   c  |   v  |   b  |                             |   k  |   m  |   ,  |   .  |   /  | SHFT |
     * +------+------+------+------+-------------+------+               +------+-------------+------+------+------+------+
     *               | META | ALT  |SP/SYM|ENT/FN|ESCSPC|               |ESCSPC| BKSP |SP/SYM|  ALT | MENU |
     *               +-------------+-------------+------+               +------+-------------+-------------+
     */
    [_BASE] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,               		KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
        KC_LCTL, L_ARRW,  KC_R,    KC_S,    KC_T,    KC_D,               		KC_H,    KC_N,    KC_E,    KC_I,    R_ARRW,  CTL_QU,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,               		KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_LGUI, KC_LALT, SYMNUM,  ENT_FN, SPEC,		SPEC,	KC_BSPC, SYMNUM,  KC_RALT, KC_APP
    ),

    /* Symbols/Numbers
     * +-----------------------------------------+                             +-----------------------------------------+
     * |  =   |   !  |   @  |   {  |   }  |   &  |                             |   /  |   7  |   8  |   9  |      |   -  |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |      |   #  |   $  |   (  |   )  |   ~  |                             |   *  |   4  |   5  |   6  |   +  |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |      |   %  |   ^  |   [  |   ]  |      |                             | NUMLK|   1  |   2  |   3  | ENTER|      |
     * +------+------+------+------+-------------+------+               +------+-------------+------+------+------+------+
     *               |      |      |      |      |      |               |      |  DEL |      |   0  |   .  |
     *               +-------------+-------------+------+               +------+-------------+-------------+
	 */
    [_SYMNUM] = LAYOUT(
        KC_EQL,  KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_AMPR,              		     KC_PSLS, KC_P7,   KC_P8,   KC_P9,   _______, KC_MINS,
        _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                		 KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
        _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, _______,               		 KC_NUM,  KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
                          _______, _______, _______, _______, _______,		_______, KC_DEL,  _______, KC_P0,   KC_PDOT
	),

    /* Specials
     * +-----------------------------------------+                             +-----------------------------------------+
     * |      |      |      |      |      |      |                             | VOL+ |      | CALC | PRSCR|      | STENO|
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                             | HOME | PGDN | PGUP |  END | CAPS |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                             | VOL- | PREV | PLAY | NEXT | SCRLK|      |
     * +------+------+------+------+-------------+------+               +------+-------------+------+------+------+------+
     *               |      |      |      |      |      |               |      |      |      |      |      |
     *               +-------------+-------------+------+               +------+-------------+-------------+
	 */
    [_SPEC] = LAYOUT(
		_______, _______, _______, _______, _______, _______,              			 KC_VOLU, _______, KC_CALC, KC_PSCR, _______, TO_STN,
        _______, _______, _______, _______, _______, _______,               		 KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_CAPS, _______,
        _______, _______, _______, _______, _______, _______,               		 KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, KC_SCRL, _______,
                       	  _______, _______, _______, _______, _______,		_______, _______, _______, _______, _______
	),

    /* Arrows
     * +-----------------------------------------+                             +-----------------------------------------+
     * |      |      |      |  UP  |      |      |                             |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |      |      | LEFT | DOWN | RIGHT|      |                             | LEFT | DOWN |  UP  | RIGHT|      |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | RESET|      |      |      |      |      |                             |      |      |      |      |      | RESET|
     * +------+------+------+------+-------------+------+               +------+-------------+------+------+------+------+
     *               |      |      |      |      |      |               |      |      |      |      |      |
     *               +-------------+-------------+------+               +------+-------------+-------------+
	 */
    [_ARROWS] = LAYOUT(
		_______, _______, _______, KC_UP,   _______, _______,             			 _______, _______, _______, _______, _______, _______,
        _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______,             			 KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,
        QK_BOOT, _______, _______, _______, _______, _______,             			 _______, _______, _______, _______, _______, QK_BOOT,
                    	  _______, _______, _______, _______, _______,		_______, _______, _______, _______, _______
	),

    /* Functions
     * +-----------------------------------------+                             +-----------------------------------------+
     * |      |      |      |      |      |      |                             |      |  F7  |  F8  |  F9  |  F10 |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                             |      |  F4  |  F5  |  F6  |  F11 |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                             |      |  F1  |  F2  |  F3  |  F12 |      |
     * +------+------+------+------+-------------+------+               +------+-------------+------+------+------+------+
     *               |      |      |      |      |      |               |      |      |      |      |      |
     *               +-------------+-------------+------+               +------+-------------+-------------+
	 */
    [_FUNC] = LAYOUT(
		_______, _______, _______, _______, _______, _______,              			 _______, KC_F7,   KC_F8,   KC_F9,   KC_F10, _______,
        _______, _______, _______, _______, _______, _______,               		 _______, KC_F4,   KC_F5,   KC_F6,   KC_F11, _______,
        _______, _______, _______, _______, _______, _______,               		 _______, KC_F1,   KC_F2,   KC_F3,   KC_F12, _______,
            		   	  _______, _______, _______, _______, _______,		_______, _______, _______, _______, _______
	),

    /* Stenography
     * +-----------------------------------------+                             +-----------------------------------------+
     * |  #1  |  #2  |  #3  |  #4  |  #5  |  #6  |                             |  #7  |  #8  |  #9  |  #A  |  #B  |  #C  |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |  FN  |      |   T  |   P  |   H  |      |                             |      |   F  |   P  |   L  |   T  |   D  |
     * |------+   S  +------+------+------+   *  |                             |   *  +------+------+------+------+------|
     * |      |      |   K  |   W  |   R  |      |                             |      |   R  |   B  |   G  |   S  |   Z  |
     * +------+------+------+------+-------------+------+               +------+-------------+------+------+------+------+
     *               | BASE |      |   A  |   O  |      |               |      |   E  |   U  | RES1 | RES2 |
     *               +-------------+-------------+------+               +------+-------------+-------------+
	 */
    [_STENO] = LAYOUT(
		STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,              			 STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC,
		STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,              			 STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
        _______, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,               		 STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
            		   	  TO_BSE, _______,  STN_A,   STN_O,   _______,		_______, STN_E,   STN_U,   STN_RE1, STN_RE2
	)
};

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

layer_state_t default_layer_state_set_user(layer_state_t state)
{
	rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
	return state;
}

layer_state_t layer_state_set_user(layer_state_t state)
{
	rgblight_set_layer_state(1, layer_state_cmp(state, _SYMNUM));
	rgblight_set_layer_state(2, layer_state_cmp(state, _SPEC));
	rgblight_set_layer_state(3, layer_state_cmp(state, _ARROWS));
	rgblight_set_layer_state(4, layer_state_cmp(state, _FUNC));
	rgblight_set_layer_state(5, layer_state_cmp(state, _STENO));
	return state;
}
