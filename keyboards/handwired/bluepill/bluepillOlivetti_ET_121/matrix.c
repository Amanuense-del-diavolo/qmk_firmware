/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#include "ch.h"
#include "hal.h"

/*
 * scan matrix
 */
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"

//#include "pwm.c"

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

inline uint8_t matrix_rows(void){
  return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void){
  return MATRIX_COLS;
}

/* generic STM32F103C8T6 board */
#ifdef BOARD_GENERIC_STM32_F103
// This could be removed, only used now in matrix_init()
#define LED_ON()    do { palClearPad(GPIOA, 1) ;} while (0)
#define LED_OFF()   do { palSetPad(GPIOA, 1); } while (0)
#endif

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void matrix_init(void)
{
  // initialize row and col
  unselect_rows();
  init_cols();
  // initialize matrix state: all keys off
  for (uint8_t i=0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }
  //debug
  debug_matrix = false;

  /* LED_ON();
  wait_ms(500);
  LED_OFF();
*/

  matrix_init_quantum();
}

uint8_t matrix_scan(void){
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    select_row(i);
    wait_us(30);  // without this wait read unstable value.
    matrix_row_t cols = read_cols();
    if (matrix_debouncing[i] != cols) {
      matrix_debouncing[i] = cols;
      if (debouncing) {
        debug("bounce!: "); debug_hex(debouncing); debug("\n");
      }
    debouncing = DEBOUNCE;
    }
    unselect_rows();
  }

  if (debouncing) {
    if (--debouncing) {
      wait_ms(1);
    } else {
      for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = matrix_debouncing[i];
      }
    }
  }
  matrix_scan_quantum();
  return 1;
}

inline bool matrix_is_on(uint8_t row, uint8_t col){
  return (matrix[row] & ((matrix_row_t)1<<col));
}

inline matrix_row_t matrix_get_row(uint8_t row){
  return matrix[row];
}

void matrix_print(void){
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    phex(row); print(": ");
    pbin_reverse16(matrix_get_row(row));
    print("\n");
  }
}

/* Column pin configuration
 */
//  Modified by Amanuense_del_Diavolo
static void  init_cols(void){
  palSetPadMode(GPIOB, 12, PAL_MODE_INPUT_PULLDOWN);
  palSetPadMode(GPIOB, 13, PAL_MODE_INPUT_PULLDOWN);
  palSetPadMode(GPIOB, 14, PAL_MODE_INPUT_PULLDOWN);
  palSetPadMode(GPIOB, 15, PAL_MODE_INPUT_PULLDOWN);
  palSetPadMode(GPIOA, 8, PAL_MODE_INPUT_PULLDOWN);
  palSetPadMode(GPIOA, 9, PAL_MODE_INPUT_PULLDOWN);
  palSetPadMode(GPIOA, 10, PAL_MODE_INPUT_PULLDOWN);
  palSetPadMode(GPIOA, 11, PAL_MODE_INPUT_PULLDOWN);
  palSetPadMode(GPIOA, 12, PAL_MODE_INPUT_PULLDOWN);
  palSetPadMode(GPIOA, 15, PAL_MODE_INPUT_PULLDOWN);
}

/* Returns status of switches(1:on, 0:off) */
//  Modified by Amanuense_del_Diavolo
static matrix_row_t read_cols(void){
  return ((palReadPad(GPIOB, 12)==PAL_LOW) ? 0 : (1<<0))
    | ((palReadPad(GPIOB, 13)==PAL_LOW) ? 0 : (1<<1))
    | ((palReadPad(GPIOB, 14)==PAL_LOW) ? 0 : (1<<2))
    | ((palReadPad(GPIOB, 15)==PAL_LOW) ? 0 : (1<<3))
    | ((palReadPad(GPIOA, 8)==PAL_LOW) ? 0 : (1<<4))
    | ((palReadPad(GPIOA, 9)==PAL_LOW) ? 0 : (1<<5))
    | ((palReadPad(GPIOA, 10)==PAL_LOW) ? 0 : (1<<6))
    | ((palReadPad(GPIOA, 11)==PAL_LOW) ? 0 : (1<<7))
    | ((palReadPad(GPIOA, 12)==PAL_LOW) ? 0 : (1<<8))
    | ((palReadPad(GPIOA, 15)==PAL_LOW) ? 0 : (1<<9));
}

/* rows pin configuration
 */
//  Modified by Amanuense_del_Diavolo
static void unselect_rows(void){
  palSetPadMode(GPIOB, 11, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 10, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 1, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 0, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 7, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 6, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 5, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 4, PAL_MODE_INPUT);
}

//  Modified by Amanuense_del_Diavolo
static void select_row(uint8_t row){
  (void)row;
  switch (row) {
    case 0:
      palSetPadMode(GPIOB, 11, PAL_MODE_OUTPUT_PUSHPULL);
      palSetPad(GPIOB, 11);
      break;
    case 1:
      palSetPadMode(GPIOB, 10, PAL_MODE_OUTPUT_PUSHPULL);
      palSetPad(GPIOB, 10);
      break;
    case 2:
      palSetPadMode(GPIOB, 1, PAL_MODE_OUTPUT_PUSHPULL);
      palSetPad(GPIOB, 1);
      break;
    case 3:
      palSetPadMode(GPIOB, 0, PAL_MODE_OUTPUT_PUSHPULL);
      palSetPad(GPIOB, 0);
      break;
    case 4:
      palSetPadMode(GPIOA, 7, PAL_MODE_OUTPUT_PUSHPULL);
      palSetPad(GPIOB, 7);
      break;
    case 5:
      palSetPadMode(GPIOA, 6, PAL_MODE_OUTPUT_PUSHPULL);
      palSetPad(GPIOA, 6);
      break;
    case 6:
      palSetPadMode(GPIOA, 5, PAL_MODE_OUTPUT_PUSHPULL);
      palSetPad(GPIOA, 5);
      break;
    case 7:
      palSetPadMode(GPIOA, 4, PAL_MODE_OUTPUT_PUSHPULL);
      palSetPad(GPIOA, 4);
      break;
  }
}
