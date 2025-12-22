#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ssd1306.h"

static const uint8_t boot_logo_tl[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t boot_logo_tm[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t boot_logo_tr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t boot_logo_ml[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t boot_logo_mm[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t boot_logo_mr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t boot_logo_bl[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t boot_logo_bm[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t boot_logo_br[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

static inline void draw_boot_logo(void)
{	
	// draw the top tiles
	draw_sprite_h(52, 20, 8, 8, boot_logo_tl);
	draw_sprite_h(60, 20, 8, 8, boot_logo_tm);
	draw_sprite_h(68, 20, 8, 8, boot_logo_tr);

	// draw the middle tiles
	draw_sprite_h(52, 28, 8, 8, boot_logo_ml);
	draw_sprite_h(60, 28, 8, 8, boot_logo_mm);
	draw_sprite_h(68, 28, 8, 8, boot_logo_mr);

	// draw the bottom tiles
	draw_sprite_h(52, 36, 8, 8, boot_logo_bl);
	draw_sprite_h(60, 36, 8, 8, boot_logo_bm);
	draw_sprite_h(68, 36, 8, 8, boot_logo_br);
}

#endif
