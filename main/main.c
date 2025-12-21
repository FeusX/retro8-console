#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "components/i2c_drivers/ssd1306.h"

void app_main(void)
{
    printf("Initializing SSD1306...\n");
    ssd1306_init();
    
    static const uint8_t invader_lt[] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};
    static const uint8_t invader_lb[] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
    static const uint8_t invader_rt[] = {0xE7, 0xE7, 0xFF, 0x18, 0xE6, 0x18, 0x66, 0x00};
    static const uint8_t invader_rb[] = {0xE7, 0xE7, 0xFF, 0x18, 0x67, 0x18, 0x66, 0x00};
    ssd1306_clear();
    
    ssd1306_draw_sprite(50, 20, 8, 8, invader_lt);
    ssd1306_draw_sprite(58, 20, 8, 8, invader_rt);
    ssd1306_draw_sprite(50, 28, 8, 8, invader_lb);
    ssd1306_draw_sprite(58, 28, 8, 8, invader_rb);
    ssd1306_update();

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
