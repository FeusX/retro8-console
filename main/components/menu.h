#ifndef MENU_H
#define MENU_H

#include "states.h"
#include "ssd1306.h"
#include "input.h"

static int8_t menu_cursor = 0;
static bool last_down = false;
static bool last_up = false;

static inline void run_menu(void)
{
  bool current_down = is_pressed(BTN_DOWN);
  bool current_up = is_pressed(BTN_UP);
  
  ssd1306_clear();
  draw_string(15, 0, "---- RETRO32 ----");
  draw_string(20, 20, (menu_cursor == 0) ? "> INVADERS" : "  INVADERS");
  draw_string(20, 30, (menu_cursor == 1) ? "> SNAKE"    : "  SNAKE");
  draw_string(20, 40, (menu_cursor == 2) ? "> TETRIS" : "  TETRIS");

  if(current_down && !last_down)
  { menu_cursor = (menu_cursor + 1) % 3; }
  last_down = current_down;

  if(current_up && !last_up)
  {
    menu_cursor--;
    if (menu_cursor < 0) menu_cursor = 2;
  }
  last_up = current_up;

  if(is_pressed(BTN_LEFT))
  {
    if(menu_cursor == 0) current_state = STATE_GAME_SPACE_INVADERS;
    if(menu_cursor == 1) current_state = STATE_GAME_SNAKE;
    if(menu_cursor == 2) current_state = STATE_GAME_TETRIS;
  }

  ssd1306_update();
}

#endif
