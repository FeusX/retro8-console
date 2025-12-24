#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "components/ssd1306.h"
//#include "components/bootloader.h"
#include "components/input.h"
#include "components/font.h"
#include "components/menu.h"
#include "components/states.h"
#include "components/games/invaders.h"
#include "components/games/snake.h"

system_state_t current_state = STATE_MENU;

void app_main(void)
{
  printf("Initializing SSD1306...\n");
  ssd1306_init();
  inputs_init();

  ssd1306_clear();

  while(1)
  {
    switch(current_state)
    {
      case STATE_MENU:
        run_menu();
        break;
      case STATE_GAME_SPACE_INVADERS:
        run_invaders();
        break;
      case STATE_GAME_SNAKE:
        run_snake();
        break;
      default:
        current_state = STATE_MENU;
        break;
    }

    vTaskDelay(pdMS_TO_TICKS(33));
  }
}
