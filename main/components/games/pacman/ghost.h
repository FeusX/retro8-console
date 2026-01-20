#ifndef GHOST_H
#define GHOST_H

#define MAX_GHOSTS 3

#include "esp_system.h"
#include "esp_random.h"

#include "maze.h"

typedef struct {
  uint8_t x;
  uint8_t y;
} ghost_t;

static ghost_t spawn_ghost(int start_x, int start_y)
{
  ghost_t g;
  g.x = start_x;
  g.y = start_y;

  return g;
}

static inline uint8_t get_x(const ghost_t *g)
{ return g->x; }

static inline uint8_t get_y(const ghost_t *g)
{ return g->y; }

static bool try_ghost_move(ghost_t *current_ghost, int8_t dx, int8_t dy,
                           const uint8_t maze_map[MAZE_HEIGHT][MAZE_WIDTH], ghost_t *all_ghosts)
{
  int16_t new_x = (int16_t)current_ghost->x + dx;
  int16_t new_y = (int16_t)current_ghost->y + dy;

  if(new_x < 0 || new_x >= MAZE_WIDTH || new_y < 0 || new_y >= MAZE_HEIGHT)
  { return false; }

  if(maze_map[new_y][new_x] == 1)
  {
    return false;
  }

  for(int i = 0; i < MAX_GHOSTS; i++)
  {
    if(&all_ghosts[i] == current_ghost) continue;

    if(all_ghosts[i].x == new_x && all_ghosts[i].y == new_y) return false;
  }

  current_ghost->x = (uint8_t)new_x;
  current_ghost->y = (uint8_t)new_y;
  return true;
}

static inline void update_ghosts(ghost_t *current_ghost, ghost_t *all_ghosts)
{
  static uint8_t logic_tick = 0;
  logic_tick++;
  
  if (logic_tick < 10) return; 
  logic_tick = 0;
  
  int8_t directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  for(int i = 0; i < 4; i++)
  {
    int dir_idx = (esp_random() % 4 + 1) % 4;
    int8_t dx = directions[dir_idx][0];
    int8_t dy = directions[dir_idx][1];

    if(try_ghost_move(current_ghost, dx, dy, maze_map, all_ghosts)) return;
  }
}

static void draw_ghost(const ghost_t *g, const uint8_t *bitmap)
{
  int16_t px = g->x * TILE_SIZE;
  int16_t py = g->y * TILE_SIZE;
  draw_sprite_h(px, py, 8, 8, bitmap);
}

#endif
