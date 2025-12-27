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
  if(is_pressed(BTN_LEFT) && ship.x > 0) ship.x -= 2.0f;
  if(is_pressed(BTN_RIGHT) && ship.x < 120) ship.x += 2.0f;
}

static void draw_player()
{
  draw_sprite_h(ship.x, 45, 16, 8, player_ship);
}

#endif
