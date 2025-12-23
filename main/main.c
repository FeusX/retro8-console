#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "components/ssd1306.h"
#include "components/bootloader.h"
#include "components/input.h"
#include "components/font.h"

void app_main(void)
{
  printf("Initializing SSD1306...\n");
  ssd1306_init();
  inputs_init();

  int alien_x = 50;
  int alien_y = 20;

  static const uint8_t invader_left[] = {
    0x03, 0x0F, 0x1F, 0x33, 0x3F, 0x0F, 0x0A, 0x12,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

  static const uint8_t invader_right[] = {
    0xC0, 0xF0, 0xF8, 0xCC, 0xFC, 0xF0, 0x50, 0x48,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
		
  while(1)
	{
    if(is_pressed(BTN_LEFT)) alien_x -= 2;
    if(is_pressed(BTN_RIGHT)) alien_x += 2;
    if(is_pressed(BTN_UP)) alien_y -= 2;
    if(is_pressed(BTN_DOWN)) alien_y += 2;

    alien_x = CLAMP(alien_x, 0, 128 - 16);
    alien_y = CLAMP(alien_y, 0, 64 - 16);

		ssd1306_clear();

		draw_sprite_h(alien_x, alien_y, 8, 16, invader_left);
		draw_sprite_h(alien_x + 8, alien_y, 8, 16, invader_right);
		draw_string(0, 0, "--- SPACE GAME ---");

		ssd1306_update();

		vTaskDelay(pdMS_TO_TICKS(20));
  }
}
