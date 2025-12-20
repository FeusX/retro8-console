#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "components/i2c_drivers/ssd1306.h"

void app_main(void)
{
  printf("Initializing SSD1306...\n");
  ssd1306_init();
  ssd1306_send_command(0xA7);
  while(1)
  {
    printf("Running...\n");
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}
