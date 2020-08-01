/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// Define layer names
#define _NORMAL 0
#define _FNONE 1
#define _FNTWO 2

// Highly Modified by Amanuense_del_diavolo
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NORMAL] = LAYOUT_Olivetti_ET_121(
 KC_S,  KC_D, KC_H, KC_6,    KC_DOT,  KC_P,    KC_NO,   KC_ALGR,   KC_RSFT,  KC_NO, \
 KC_Z,  KC_E, KC_Y, KC_J,    KC_L,    KC_M,    KC_ESC,  KC_ENT,    KC_CAPS,  KC_NO, \
 KC_1,  KC_2, KC_5, KC_N,    KC_O,    KC_SCLN, KC_LCTL, KC_SPC,    KC_LOPT,  KC_NO, \
 KC_W,  KC_X, KC_B, KC_U,    KC_8,    KC_9,    KC_GRV,  KC_BSPC,   KC_NUBS,  KC_NO, \
 KC_NO, KC_C, KC_V, KC_7,    KC_0,    KC_NUHS, KC_TAB,  KC_CANCEL, KC_NO,    KC_NO, \
 KC_A,  KC_F, KC_G, KC_I,    KC_LBRC, KC_RBRC, KC_NO,   KC_NO,     KC_RIGHT, KC_NO, \
 KC_Q,  KC_R, KC_T, KC_K,    KC_QUOT, KC_MINS,          KC_LEFT,   KC_DOWN,  KC_NO, \
 KC_NO, KC_3, KC_4, KC_COMM, KC_SLSH, KC_EQL,           KC_UP,     KC_NO,    KC_NO),
/*        
  [_FNONE] = LAYOUT_seventy_iso(
  KC_TRNS, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_TRNS,KC_MUTE,KC_VOLD,KC_VOLU, KC_TRNS,KC_TRNS,KC_NLCK, KC_CALC, KC_TRNS,KC_TRNS,KC_TRNS, \
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_P7,  KC _P8,  KC_P9,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_P4,   KC_P5,  KC_P6,  KC_PPLS, KC_TRNS, KC_TRNS,         KC_TRNS, \
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_P1,  KC_P2,  KC_P3,  KC_PAST, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_P0,  KC_PDOT,KC_PENT, KC_PSLS,   KC_TRNS,KC_TRNS,KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS ),

  [_FNTWO] = LAYOUT_seventy_iso(
  KC_TRNS, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_TRNS,KC_MUTE,KC_VOLD,KC_VOLU, KC_TRNS,KC_TRNS,KC_NLCK, KC_CALC, KC_TRNS,KC_TRNS,KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_P7,  KC_P8,  KC_P9,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_P4,  KC_P5,  KC_P6,  KC_PPLS, KC_TRNS, KC_TRNS,         KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_P1,  KC_P2,  KC_P3,  KC_PAST, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_P0,  KC_PDOT,KC_PENT, KC_PSLS,  KC_TRNS,KC_TRNS,KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS ),
*/
};

/* Layer based ilumination, just binary */
uint32_t layer_state_set_user(uint32_t state) {
/*  switch (biton32(state)) {
  case _FNONE:
    palSetPad(GPIOA, 0);  //OFF Color A
    palClearPad(GPIOA, 1); //ON Color B
    break;
  case _FNTWO:
    palClearPad(GPIOA, 0); //ON Color A
    palClearPad(GPIOA, 1);  //ON Color B
    break;
  default: //  for any other layers, or the default layer
    palClearPad(GPIOA, 0); //ON Color A
    palSetPad(GPIOA, 1);  //OFF Color B
    break;
    }
*/
  return state;
}
