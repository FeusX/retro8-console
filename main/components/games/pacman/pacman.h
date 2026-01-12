#ifndef PACMAN_H
#define PACMAN_H

#include "maze.h"
#include "player.h"

static inline void init_pacman(void);
static inline void update_pacman(uint8_t map[MAZE_HEIGHT][MAZE_WIDTH]);

static uint8_t game_map[MAZE_HEIGHT][MAZE_WIDTH];

static inline void init_game(void)
{
  init_pacman();

  for(int y = 0; y < MAZE_HEIGHT; y++)
  {
    for(int x = 0; x < MAZE_WIDTH; x++)
    { game_map[y][x] = maze_map[y][x]; }
  }

  ssd1306_clear();
  draw_maze();
  ssd1306_update();
}

void run_pacman(void)
{
  static bool initialized = false;
  if(!initialized)
  {
    init_game();
    initialized = true;
  }

  update_pacman(game_map);
  ssd1306_update();
}

#endif
