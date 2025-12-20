#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "components/i2c_drivers/ssd1306.h"

void app_main(void)
{
  printf("Initializing SSD1306...\n");
  ssd1306_init();

  int16_t inv_x = 60;
  int16_t inv_y = 0;
  int16_t y_speed = 1;
  static const uint8_t invader_sprite[] = {0x18, 0x3C, 0x7E, 0xDB, 0xFF, 0x24, 0x5A, 0xA5};

  while(1)
  {
    ssd1306_clear();
    inv_y += y_speed;

    if(inv_y >= 56 || inv_y <= 0)
    {
      y_speed *= -1;
    }

    ssd1306_draw_sprite(inv_x, inv_y, 8, 8, invader_sprite);
    ssd1306_update();

    vTaskDelay(pdMS_TO_TICKS(16));
  }
}
