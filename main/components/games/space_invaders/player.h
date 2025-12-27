#ifndef PLAYER_H
#define PLAYER_H

#include "../../ssd1306.h"
#include "../../input.h"
#include "../../assets.h"

typedef struct {
  float x;
  int8_t hp;
} player_t;

static player_t ship = {60, 3};

static void update_player()
{
  if(is_pressed(BTN_LEFT) && ship.x > 0) ship.x -= 1.5f;
  if(is_pressed(BTN_RIGHT) && ship.x < 120) ship.x += 1.5f;
}

/*static void draw_ship()
{
  for(int row = 0; row < 6; row++)
  {
    uint16_t row_data = player_ship[row];
    for(int col = 0; col < 13; col++)
    {
      if(row_data & (0x1000 >> col))
      {
        ssd1306_draw_pixel((int)ship.x + col, 56 + row, 1);
      }
    }
  }
}*/

#endif
