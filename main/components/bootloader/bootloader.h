#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../i2c_drivers/ssd1306.h"

static const uint8_t boot_logo_tl[] = {};
static const uint8_t boot_logo_tm[] = {};
static const uint8_t boot_logo_tr[] = {};
static const uint8_t boot_logo_ml[] = {};
static const uint8_t boot_logo_mm[] = {};
static const uint8_t boot_logo_mr[] = {};
static const uint8_t boot_logo_bl[] = {};
static const uint8_t boot_logo_bm[] = {};
static const uint8_t boot_logo_br[] = {};

static inline void draw_boot_logo(int x, int y)
{
  
}

#endif
