#ifndef PACMAN_H
#define PACMAN_H

#include "../../ssd1306.h"
#include "../../input.h"
#include "../../font.h"
#include "../../assets.h"
#include "../../states.h"

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

  ghosts[0] = spawn_ghost(4, 1);
  ghosts[1] = spawn_ghost(14, 1);
  ghosts[2] = spawn_ghost(14, 6);

  for(int y = 0; y < MAZE_HEIGHT; y++)
  {
    for(int x = 0; x < MAZE_WIDTH; x++)
    { game_map[y][x] = maze_map[y][x]; }
  }

  eaten_pellets = 0;
}

static inline void collision_detect(ghost_t *all_ghosts)
{
	for(int i = 0; i < MAX_GHOSTS; i++)
	{
    if(player_x < all_ghosts[i].x * TILE_SIZE + 6 &&
       player_x + 6 > all_ghosts[i].x * TILE_SIZE &&
       player_y < all_ghosts[i].y * TILE_SIZE + 6 &&
       player_y + 6 > all_ghosts[i].y * TILE_SIZE)
    {
      pacman_initialized = false;
      ssd1306_clear();
      draw_string(30, 24, "GAME OVER");
      ssd1306_update();
      vTaskDelay(pdMS_TO_TICKS(1000));
      char score[16];
      ssd1306_clear();
      sprintf(score, "PELLETS %d", eaten_pellets);
      draw_string(20, 24, score);
      ssd1306_update();
      vTaskDelay(pdMS_TO_TICKS(1000));
      current_state = STATE_MENU;
      return;
    }
    else if(eaten_pellets >= 51)
    {
      pacman_initialized = false;
      ssd1306_clear();
      draw_string(30, 24, "YOU WON");
      ssd1306_update();
      vTaskDelay(pdMS_TO_TICKS(1000));
      current_state = STATE_MENU;
      return;
    }
	}
}

void run_pacman(void)
{
  if(!pacman_initialized)
  {
    init_game();
    pacman_initialized = true;
  }
  while(1)
  {
    ssd1306_clear();
    update_pacman(game_map);
    draw_maze(game_map);
    for(int i = 0; i < MAX_GHOSTS; i++)
    { update_ghosts(&ghosts[i], ghosts, player_x / TILE_SIZE, player_y / TILE_SIZE); }
    for(int i = 0; i < MAX_GHOSTS; i++)
    { draw_ghost(&ghosts[i], ghost_sprite); }
    collision_detect(ghosts);
    ssd1306_update();
    if(!pacman_initialized)
    { break; }

    vTaskDelay(pdMS_TO_TICKS(33));
  }
}

#endif
