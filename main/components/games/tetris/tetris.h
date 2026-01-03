#ifndef TETRIS_H
#define TETRIS_H

#define FIELD_W 10
#define FIELD_H 20

#include "../../assets.h"

uint8_t field[FIELD_H][FIELD_W];

static void draw_block(int gx, int gy)
{
  int px = gx * 4;
  int py = gy * 4;

  for(int y = 0; y < 4; y++)
  {
    for(int x = 0; x < 4; x++)
    {
      ssd1306_draw_pixel(px + x, py + y, true);
    }
  }
}

static void run_tetris(void)
{
  draw_block(20, 30);
}

#endif
