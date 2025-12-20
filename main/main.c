#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void) {
    printf("Console Initializing...\n");
    while(1) {
        printf("Hello from Tiny Console!\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Wait 1 second
    }
}
