#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "components/i2c_drivers/ssd1306.h"

void app_main(void)
{
  printf("Initializing SSD1306...\n");
  ssd1306_init();
  ssd1306_clear();

  for(int i = 0; i < 64; i++)
  { ssd1306_draw_pixel(i, i, true); ssd1306_draw_pixel(i, 63 - i, true); ssd1306_draw_pixel(i + 64, i, true); ssd1306_draw_pixel(i + 64, 63 - i, true); }

  ssd1306_update();

  while(1)
  { vTaskDelay(pdMS_TO_TICKS(1000)); }
}
