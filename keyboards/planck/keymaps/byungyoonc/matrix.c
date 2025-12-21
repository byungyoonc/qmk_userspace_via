/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2017 Alex Ong<the.onga@gmail.com>
 * Copyright 2021 Simon Arlott
 * Copyright 2021 Choi Byungyoon <byungyoonc@gmail.com>
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

 /* custom matrix scan implementation for sym_eager_pk debounce */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "debug.h"
#include "matrix.h"
#include <stdlib.h>

/*
 *     col: { B11, B10, B2, B1, A7, B0 }
 *     row: { A10, A9, A8, B15, C13, C14, C15, A2 }
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_COLS];
typedef uint8_t debounce_counter_t;
static debounce_counter_t *debounce_counters;
static fast_timer_t        last_time;
static bool                counters_need_update;
static bool                matrix_need_update;

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

void matrix_init(void) {
    dprintf("matrix init\n");
    // debug_matrix = true;

    // actual matrix setup
    palSetPadMode(GPIOB, 11, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 7, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 0, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPadMode(GPIOA, 10, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 9, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 8, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 15, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 13, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 14, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 15, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 2, PAL_MODE_INPUT_PULLDOWN);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));
    debounce_counters = (debounce_counter_t *)malloc(MATRIX_ROWS * MATRIX_COLS * sizeof(debounce_counter_t));
    memset(debounce_counters, 0, MATRIX_ROWS * MATRIX_COLS * sizeof(debounce_counter_t));

    matrix_init_user();
}

uint8_t matrix_scan(void) {
    // actual matrix
    bool changed = false;
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;

        // strobe col { B11, B10, B2, B1, A7, B0 }
        switch (col) {
            case 0:
                palSetPad(GPIOB, 11);
                break;
            case 1:
                palSetPad(GPIOB, 10);
                break;
            case 2:
                palSetPad(GPIOB, 2);
                break;
            case 3:
                palSetPad(GPIOB, 1);
                break;
            case 4:
                palSetPad(GPIOA, 7);
                break;
            case 5:
                palSetPad(GPIOB, 0);
                break;
        }

        // need wait to settle pin state
        //wait_us(15);
        for (int i = 0; i < 15; i++) {
            wait_cpuclock(STM32_SYSCLK / 1000000L);
        }

        // read row data { A10, A9, A8, B15, C13, C14, C15, A2 }
        data = ((palReadPad(GPIOA, 10) << 0) | (palReadPad(GPIOA, 9) << 1) | (palReadPad(GPIOA, 8) << 2) | (palReadPad(GPIOB, 15) << 3) | (palReadPad(GPIOC, 13) << 4) | (palReadPad(GPIOC, 14) << 5) | (palReadPad(GPIOC, 15) << 6) | (palReadPad(GPIOA, 2) << 7));

        // unstrobe  col { B11, B10, B2, B1, A7, B0 }
        switch (col) {
            case 0:
                palClearPad(GPIOB, 11);
                break;
            case 1:
                palClearPad(GPIOB, 10);
                break;
            case 2:
                palClearPad(GPIOB, 2);
                break;
            case 3:
                palClearPad(GPIOB, 1);
                break;
            case 4:
                palClearPad(GPIOA, 7);
                break;
            case 5:
                palClearPad(GPIOB, 0);
                break;
        }

        if (matrix_debouncing[col] != data) {
            matrix_debouncing[col] = data;
            changed = true;
        }
    }

    bool updated_last = false;

    if (counters_need_update) {
        fast_timer_t now          = timer_read_fast();
        fast_timer_t elapsed_time = TIMER_DIFF_FAST(now, last_time);

        last_time    = now;
        updated_last = true;
        if (elapsed_time > UINT8_MAX) {
            elapsed_time = UINT8_MAX;
        }

        if (elapsed_time > 0) {
            counters_need_update = false;
            matrix_need_update = false;
            debounce_counter_t *debounce_pointer = debounce_counters;
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    if (*debounce_pointer != 0) {
                        if (*debounce_pointer <= elapsed_time) {
                            *debounce_pointer  = 0;
                            matrix_need_update = true;
                        } else {
                            *debounce_pointer -= elapsed_time;
                            counters_need_update = true;
                        }
                    }
                    debounce_pointer++;
                }
            }
        }
    }

    if (changed || matrix_need_update) {
        if (!updated_last) {
            last_time = timer_read_fast();
        }

        debounce_counter_t *debounce_pointer = debounce_counters;
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            matrix_row_t row_shifter = 1 << row;
            matrix_row_t existing_row = matrix[row];
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                matrix_row_t col_mask = 1 << col;
                matrix_row_t debouncing_cell = (matrix_debouncing[col] & row_shifter ? 1 : 0) << col;
                if (debouncing_cell ^ (existing_row & col_mask)) {
                    if (*debounce_pointer == 0) {
                        *debounce_pointer = DEBOUNCE;
                        counters_need_update = true;
                        existing_row ^= col_mask;
                    }
                }
                debounce_pointer++;
            }
            matrix[row] = existing_row;
        }
    }

    matrix_scan_user();

    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & (1 << col)); }

matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {
    dprintf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        dprintf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1 << col))
                dprintf("1");
            else
                dprintf("0");
        }
        dprintf("\n");
    }
}
