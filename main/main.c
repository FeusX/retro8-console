#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "components/ssd1306.h"
#include "components/bootloader.h"
#include "components/input.h"
#include "components/font.h"
#include "components/menu.h"
#include "components/states.h"

// include the games
#include "components/games/space_invaders/invaders.h"
#include "components/games/snake/snake.h"
#include "components/games/tetris/tetris.h"
#include "components/games/pacman/pacman.h"

system_state_t current_state = STATE_MENU;

void app_main(void)
{
  retro8_boot();

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
      case STATE_GAME_TETRIS:
        run_tetris();
        break;
      case STATE_GAME_PACMAN:
        run_pacman();
        break;
      default:
        current_state = STATE_MENU;
        break;
    }

    vTaskDelay(pdMS_TO_TICKS(33));
  }
}
