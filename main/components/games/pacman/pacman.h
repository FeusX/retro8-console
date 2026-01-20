#ifndef PACMAN_H
#define PACMAN_H

#include "../../ssd1306.h"
#include "../../input.h"
#include "../../font.h"
#include "../../assets.h"

#include "maze.h"
#include "player.h"
#include "ghost.h"

static inline void init_pacman(void);
static inline void update_pacman(uint8_t map[MAZE_HEIGHT][MAZE_WIDTH]);

static uint8_t game_map[MAZE_HEIGHT][MAZE_WIDTH];
static ghost_t ghosts[MAX_GHOSTS];
static bool pacman_initialized = false;

static inline void init_game(void)
{
  init_pacman();

  ghosts[0] = spawn_ghost(1, 1);
  ghosts[1] = spawn_ghost(14, 1);
  ghosts[2] = spawn_ghost(14, 6);

  for(int y = 0; y < MAZE_HEIGHT; y++)
  {
    for(int x = 0; x < MAZE_WIDTH; x++)
    { game_map[y][x] = maze_map[y][x]; }
  }
}

void run_pacman(void)
{
  if(!pacman_initialized)
  {
    init_game();
    pacman_initialized = true;
  }

  ssd1306_clear();
  update_pacman(game_map);
  draw_maze(game_map);
  for(int i = 0; i < MAX_GHOSTS; i++)
  { update_ghosts(&ghosts[i], ghosts); }
  for(int i = 0; i < MAX_GHOSTS; i++)
  { draw_ghost(&ghosts[i], ghost_sprite); }
  ssd1306_update();
}

#endif
