#ifndef MENU_H
#define MENU_H

#include "states.h"
#include "ssd1306.h"
#include "input.h"

typedef struct {
    const char* name;
    system_state_t state;
} game_entry_t;

static const game_entry_t games[] = {
    {"INVADERS", STATE_GAME_SPACE_INVADERS},
    {"SNAKE",    STATE_GAME_SNAKE},
    {"TETRIS",   STATE_GAME_TETRIS},
    {"PACMAN",   STATE_GAME_PACMAN}
};

#define GAME_COUNT (sizeof(games) / sizeof(game_entry_t))

static int8_t menu_cursor = 0;
static int8_t scroll_offset = 0;
static bool last_down = false;
static bool last_up = false;

static inline void run_menu(void)
{
  bool current_down = is_pressed(BTN_DOWN);
  bool current_up = is_pressed(BTN_UP);
  
  ssd1306_clear();
  draw_string(15, 0, "---- RETRO8 ----");

  for(int i = 0; i < 3; i++)
  {
    int8_t idx = i + scroll_offset;

    if(idx < GAME_COUNT)
    {
      int16_t y = 20 + (i * 12);
      if(menu_cursor == idx)
      { draw_string(10, y, ">"); }
      draw_string(25, y, games[idx].name);
    }
  }

  if(current_down && !last_down)
  {
    menu_cursor++;
    if(menu_cursor >= GAME_COUNT)
    {
      menu_cursor = 0;
      scroll_offset = 0;
    }
    else if(menu_cursor >= scroll_offset + 3)
    { scroll_offset++; }
  }
  last_down = current_down;

  if(current_up && !last_up)
  {
    menu_cursor--;
    if(menu_cursor < 0)
    {
      menu_cursor = GAME_COUNT - 1;
      scroll_offset = (GAME_COUNT > 3) ? GAME_COUNT - 3 : 0;
    }
    else if(menu_cursor < scroll_offset)
    { scroll_offset--; }
  }
  last_up = current_up;

  if(is_pressed(BTN_A))
  { current_state = games[menu_cursor].state; }

  ssd1306_update();
}

#endif
