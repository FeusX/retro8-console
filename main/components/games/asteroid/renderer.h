#ifndef RENDERER_H
#define RENDERER_H

#include "../../ssd1306.h"

static inline void render_bresenham(int8_t x0, int8_t x1, int8_t y0, int8_t y1)
{
  int8_t dx = abs(x1 - x0);
  int8_t sx = x0 < x1 ? 1 : -1;
  int8_t dy = -abs(y1 - y0);
  int8_t sy = y0 < y1 ? 1 : -1;
  int8_t err = dx + dy;

  while(1)
  {
    ssd1306_draw_pixel(x0, y0, true);

    if(x0 == x1 && y0 == y1) break;

    if(2 * err >= dy)
    { err += dy; x0 += sx; }

    if(2 * err <= dx)
    { err += dx; y0 += sy; }
  }
}

static inline void render_player(int8_t x0, int8_t y0,
                                 int8_t x1, int8_t y1,
                                 int8_t x2, int8_t y2)
{
  render_bresenham(x0, x1, y0, y1);
  render_bresenham(x1, x2, y1, y2);
  render_bresenham(x2, x0, y2, y0);
}

static inline void render_circle(int8_t circle_x, int8_t circle_y, int8_t radius)
{
  
}

#endif
