#ifndef PACMAN_PLAYER_H
#define PACMAN_PLAYER_H

#include "../../input.h"
#include "../../ssd1306.h"
#include "../../assets.h"
#include "maze.h"

static int16_t player_x, player_y;
static int8_t player_dir;
static uint8_t anim_frame, frame_tick;

static inline void init_pacman(void)
{
  player_x = 1 * TILE_SIZE;
  player_y = 1 * TILE_SIZE;
  player_dir = 0;
  anim_frame = 0;
  frame_tick = 0;
}

static inline void update_pacman(uint8_t map[MAZE_HEIGHT][MAZE_WIDTH])
{
  int draw_x = player_x - 1;
  int draw_y = player_y - 1;

  for(int i = 0; i < 8; i++) // this is for clearing just the pacman
  {
    for(int j = 0; j < 8; j++)
    {
      ssd1306_draw_pixel(draw_x + i, draw_y + j, false);
    }
  }

  int dx = 0;
  int dy = 0;

  if(is_pressed(BTN_UP)) { dy = -1; player_dir = 2; }
  if(is_pressed(BTN_DOWN)) { dy = 1; player_dir = 3; }
  if(is_pressed(BTN_RIGHT)) { dx = 1; player_dir = 0; }
  if(is_pressed(BTN_LEFT)) { dx = -1; player_dir = 1; }

  int next_x = player_x + dx;
  int next_y = player_y + dy;

  int grid_x1 = next_x / TILE_SIZE;
  int grid_y1 = next_y / TILE_SIZE;
  int grid_x2 = (next_x + TILE_SIZE - 1) / TILE_SIZE;
  int grid_y2 = (next_y + TILE_SIZE - 1) / TILE_SIZE;

  if(map[grid_y1][grid_x1] != 1 && 
     map[grid_y1][grid_x2] != 1 &&
     map[grid_y2][grid_x1] != 1 && 
     map[grid_y2][grid_x2] != 1) // this is for checking the walls for potential blocking
  {
    player_x = next_x;
    player_y = next_y;

    frame_tick++;
    if(frame_tick > 3)
    {
      anim_frame = !anim_frame;
      frame_tick = 0;
    }
  }

  int center_x = (player_x + TILE_SIZE / 2) / TILE_SIZE;
  int center_y = (player_y + TILE_SIZE / 2) / TILE_SIZE;
  if(map[center_y][center_x] == 0)
  { map[center_y][center_x] = 2; }

  draw_x = player_x - 1;
  draw_y = player_y - 1;

  draw_sprite_h(draw_x, draw_y, 8, 8, pacman[player_dir].frame[anim_frame]);
}

#endif
