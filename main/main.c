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
#include "components/game_reg.h"

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
    if(current_state == STATE_MENU)
    { run_menu(); }
    else
    {
      bool game_found = false;

      for(int i = 0; i < GAME_COUNT; i++)
      {
        if(current_state == games_list[i].state)
        {
          game_found = true;
          games_list[i].run();
          break;
        }
      }

      if(!game_found)
      { current_state = STATE_MENU; }
    }
  }
}