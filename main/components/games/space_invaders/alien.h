#ifndef ALIEN_H
#define ALIEN_H

#include "../../ssd1306.h"
#include "../../assets.h"

#define ALIEN_ROWS 3
#define ALIEN_COLS 8

typedef struct {
  float x, y;
  bool active;
} alien_t;

static alien_t swarm[ALIEN_ROWS][ALIEN_COLS];
static int8_t swarm_dir = 1;
static float swarm_speed = 0.06f;

static void init_aliens()
{
  for(int r = 0; r < ALIEN_ROWS; r++)
  {
    for(int c = 0; c < ALIEN_COLS; c++)
    {
      swarm[r][c].x = c * 14 + 10;
      swarm[r][c].y = r * 10 + 10;
      swarm[r][c].active = true;
    }
  }
}

static void draw_alien(int x, int y)
{
  for(int row = 0; row < ALIEN_ROWS; row++)
  {
    uint8_t row_data = invader_small[row];
    for(int col = 0; col < 8; col++)
    {
      if(row_data & (0x80 >> col))
      {
        ssd1306_draw_pixel(x + col, y + row, 1);
      }
    }
  }
}

static void update_aliens()
{
  bool hit_edge = false;

  for(int r = 0; r < ALIEN_ROWS; r++)
  {
    for(int c = 0; c < ALIEN_COLS; c++)
    {
      if(swarm[r][c].active)
      {
        swarm[r][c].x += (swarm_dir * swarm_speed);
        if(swarm[r][c].x > 120 || swarm[r][c].x < 0)
        { hit_edge = true; }
      }
    }
  }

  if(hit_edge)
  {
    swarm_dir *= -1;
    for (int r = 0; r < ALIEN_ROWS; r++)
    {
      for (int c = 0; c < ALIEN_COLS; c++)
      {
        swarm[r][c].y += 4; // Shift down
      }
    }
  }
}

#endif
