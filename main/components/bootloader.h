#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ssd1306.h"
#include "font.h"
#include "input.h"

static void retro8_boot(void)
{
	// init ssd1306
	ssd1306_init();
	ssd1306_clear();
	draw_string(0, 20, "Initializing SSD1306.");
	ssd1306_update();
	vTaskDelay(pdMS_TO_TICKS(2000));
	ssd1306_clear();
	draw_string(0, 20, "SSD1306 initialized.");
	ssd1306_update();
	vTaskDelay(pdMS_TO_TICKS(1000));

	// init inputs
	ssd1306_clear();
	inputs_init();
	draw_string(0, 20, "Initializing inputs");
	ssd1306_update();
	vTaskDelay(pdMS_TO_TICKS(2000));
	ssd1306_clear();
	draw_string(0, 20, "Inputs initialized.");
	ssd1306_update();
	vTaskDelay(pdMS_TO_TICKS(1000));

	ssd1306_clear();
	draw_string(0,  0, "oooooo. .oooo.");
	draw_string(0,  8, "`888 Y88 d88 8");
	draw_string(0, 16, " 888 d88 Y88 8");
	draw_string(0, 24, " 88888P   888b");
	draw_string(0, 32, " 888`88b .8 88");
	draw_string(0, 40, " 888 88b 8. 8P");
	draw_string(0, 48, "o888o o888 bo8");
	draw_string(0, 56, "BY FEUSX");
	ssd1306_update();
	vTaskDelay(pdMS_TO_TICKS(3000));
}

#endif
