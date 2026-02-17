#ifndef RENDERER_H
#define RENDERER_H

#include <stdlib.h>

#include "../../ssd1306.h"

#define SIN(a) sin_table[(uint8_t)(a)]
#define COS(a) sin_table[(uint8_t)((a) + 64)]

const int16_t sin_table[256] = {
      0,   6,  13,  19,  25,  31,  38,  44,  50,  56,  62,  68,  74,  80,  86,  92,
     98, 104, 109, 115, 121, 126, 132, 137, 142, 147, 152, 157, 162, 167, 172, 177,
    181, 185, 190, 194, 198, 202, 206, 209, 213, 216, 220, 223, 226, 229, 231, 234,
    237, 239, 241, 243, 245, 247, 248, 250, 251, 252, 253, 254, 255, 255, 256, 256,
    256, 256, 256, 255, 255, 254, 253, 252, 251, 250, 248, 247, 245, 243, 241, 239,
    237, 234, 231, 229, 226, 223, 220, 216, 213, 209, 206, 202, 198, 194, 190, 185,
    181, 177, 172, 167, 162, 157, 152, 147, 142, 137, 132, 126, 121, 115, 109, 104,
     98,  92,  86,  80,  74,  68,  62,  56,  50,  44,  38,  31,  25,  19,  13,   6,
      0,  -6, -13, -19, -25, -31, -38, -44, -50, -56, -62, -68, -74, -80, -86, -92,
    -98,-104,-109,-115,-121,-126,-132,-137,-142,-147,-152,-157,-162,-167,-172,-177,
   -181,-185,-190,-194,-198,-202,-206,-209,-213,-216,-220,-223,-226,-229,-231,-234,
   -237,-239,-241,-243,-245,-247,-248,-250,-251,-252,-253,-254,-255,-255,-256,-256,
   -256,-256,-256,-255,-255,-254,-253,-252,-251,-250,-248,-247,-245,-243,-241,-239,
   -237,-234,-231,-229,-226,-223,-220,-216,-213,-209,-206,-202,-198,-194,-190,-185,
   -181,-177,-172,-167,-162,-157,-152,-147,-142,-137,-132,-126,-121,-115,-109,-104,
    -98, -92, -86, -80, -74, -68, -62, -56, -50, -44, -38, -31, -25, -19, -13,  -6
};

static inline void render_bresenham(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
  int16_t dx = abs(x1 - x0);
  int16_t sx = x0 < x1 ? 1 : -1;
  int16_t dy = -abs(y1 - y0);
  int16_t sy = y0 < y1 ? 1 : -1;
  int16_t err = dx + dy;
  int16_t e2;

  while(1)
  {
    ssd1306_draw_pixel(x0, y0, true);

    if(x0 == x1 && y0 == y1) break;

    e2 = (err << 1);

    if(e2 >= dy)
    { err += dy; x0 += sx; }

    if(e2 <= dx)
    { err += dx; y0 += sy; }
  }
}

static inline void ast_render_triangle(int16_t x0, int16_t y0,
                                 int16_t x1, int16_t y1,
                                 int16_t x2, int16_t y2)
{
  render_bresenham(x0, y0, x1, y1);
  render_bresenham(x1, y1, x2, y2);
  render_bresenham(x2, y2, x0, y0);
}

static inline void ast_render_circle(int16_t circle_x, int16_t circle_y, int16_t radius)
{
  int16_t x = radius;
  int16_t y = 0;
  int16_t err = 0;

  while(x >= y)
  {
    ssd1306_draw_pixel(circle_x + x, circle_y + y, true);
    ssd1306_draw_pixel(circle_x + y, circle_y + x, true);
    ssd1306_draw_pixel(circle_x - y, circle_y + x, true);
    ssd1306_draw_pixel(circle_x - x, circle_y + y, true);
    ssd1306_draw_pixel(circle_x + x, circle_y - y, true);
    ssd1306_draw_pixel(circle_x - y, circle_y - x, true);
    ssd1306_draw_pixel(circle_x + y, circle_y - x, true);
    ssd1306_draw_pixel(circle_x - x, circle_y - y, true);

    y++;

    if(err <= 0)
    { err += (y << 1) + 1; }
    else
    { x--; err -= (y << 1) + 1; }
  }
}

#endif
