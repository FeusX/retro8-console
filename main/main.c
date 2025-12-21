#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "components/i2c_drivers/ssd1306.h"
#include "components/bootloader/bootloader.h"

void app_main(void)
{
  printf("Initializing SSD1306...\n");
  ssd1306_init();

  // LEFT TOWER (8x16)
  static const uint8_t invader_left[] = {
    0x03, 0x0F, 0x1F, 0x33, 0x3F, 0x0F, 0x0A, 0x12, // Top 8 rows
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // Bottom 8 rows (if any)
  };

// RIGHT TOWER (8x16)
  static const uint8_t invader_right[] = {
    0xC0, 0xF0, 0xF8, 0xCC, 0xFC, 0xF0, 0x50, 0x48, // Top 8 rows
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // Bottom 8 rows
  };
    
  /*static const uint8_t invader_lt[] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};
  static const uint8_t invader_lb[] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
  static const uint8_t invader_rt[] = {0xE7, 0xE7, 0xFF, 0x18, 0xE6, 0x18, 0x66, 0x00};
  static const uint8_t invader_rb[] = {0xE7, 0xE7, 0xFF, 0x18, 0x67, 0x18, 0x66, 0x00};
  ssd1306_clear();
  
  ssd1306_draw_sprite(50, 20, 8, 8, invader_lt);
  ssd1306_draw_sprite(58, 20, 8, 8, invader_rt);
  ssd1306_draw_sprite(50, 28, 8, 8, invader_lb);
  ssd1306_draw_sprite(58, 28, 8, 8, invader_rb);
  ssd1306_update();
		
	ssd1306_clear();

	draw_boot_logo();*/

	draw_sprite_h(50, 20, 8, 16, invader_left);
	draw_sprite_h(58, 20, 8, 16, invader_right);
	ssd1306_update();
		
  while(1)
	{
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
