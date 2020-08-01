#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6464
#define DEVICE_VER      0x0001

//  Modified by Amanuense_del_Diavolo
#define MANUFACTURER "QMK"
#define PRODUCT "Olivetti_ET-121"
#define DESCRIPTION "QMK keyboard firmware with ChibiOS"

/* key matrix size */
//  Modified by Amanuense_del_Diavolo
#define MATRIX_ROWS 8
#define MATRIX_COLS 10
#define DIODE_DIRECTION ROW2COL

// Iso fix for Space Cadet, comment for ANSI layouts
#define LSPO_KEY KC_8
#define RSPC_KEY KC_9
