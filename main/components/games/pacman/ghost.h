#ifndef GHOST_H
#define GHOST_H

#define MAX_GHOSTS 3

#include <stdlib.h>

#include "esp_system.h"
#include "esp_random.h"

#include "maze.h"

typedef struct {
  uint8_t x, y, tick;
} ghost_t;

static ghost_t spawn_ghost(int start_x, int start_y)
{
  ghost_t g;
  g.x = start_x;
  g.y = start_y;

  return g;
}

static bool try_ghost_move(int x, int y, 
                           const uint8_t maze_map[MAZE_HEIGHT][MAZE_WIDTH], 
                           ghost_t *all_ghosts, ghost_t *current_ghost)
{
  if(x < 0 || x >= MAZE_WIDTH || y < 0 || y >= MAZE_HEIGHT) return false;
  if(maze_map[y][x] == 1) return false;

  for(int i = 0; i < MAX_GHOSTS; i++)
  {
    if(&all_ghosts[i] == current_ghost) continue;
    if(all_ghosts[i].x == x && all_ghosts[i].y == y) return false;
  }

  return true;
}

static inline void update_ghosts(ghost_t *current_ghost, ghost_t *all_ghosts, int target_x, int target_y)
{
  current_ghost->tick++;
  
  if(current_ghost->tick < 25) return; 
  current_ghost->tick = 0;
  
  int8_t directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  int16_t best_dist = 9999;
  int8_t best_dir_index = -1;

  for(int i = 0; i < 4; i++)
  {
    int16_t next_x = current_ghost->x + directions[i][0];
    int16_t next_y = current_ghost->y + directions[i][1];

    if(try_ghost_move(next_x, next_y, maze_map, all_ghosts, current_ghost))
    {
      int dist = abs(next_x - target_x) + abs(next_y - target_y);

      if(dist < best_dist)
      {
        best_dist = dist;
        best_dir_index = i;
      }
    }
  }

  if(best_dir_index != -1)
  {
    if((esp_random() % 5) > 0)
    {
      current_ghost->x += directions[best_dir_index][0];
      current_ghost->y += directions[best_dir_index][1];
    }
    else
    {
      int8_t rand_dir = esp_random() % 4;
      uint16_t rand_x = current_ghost->x + directions[(rand_dir)][0];
      uint16_t rand_y = current_ghost->y + directions[(rand_dir)][1];
      if(try_ghost_move(rand_x, rand_y, maze_map, all_ghosts, current_ghost))
      {
        current_ghost->x = (uint8_t)rand_x;
        current_ghost->y = (uint8_t)rand_y;
      }
      else
      {
        current_ghost->x += directions[best_dir_index][0];
        current_ghost->y += directions[best_dir_index][1];
      }
    }
  }
}

static void draw_ghost(const ghost_t *g, const uint8_t *bitmap)
{
  int16_t px = g->x * TILE_SIZE;
  int16_t py = g->y * TILE_SIZE;
  draw_sprite_h(px, py, 8, 8, bitmap);
}

#endif
