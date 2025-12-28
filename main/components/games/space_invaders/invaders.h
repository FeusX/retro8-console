#ifndef INVADERS_H
#define INVADERS_H

#include "../../ssd1306.h"
#include "../../input.h"
#include "../../assets.h"
#include "../../font.h"
#include "bullet.h"
#include "player.h"

static inline void run_invaders()
{
  ssd1306_clear();

  draw_string(3, 0, "-- SPACE INVADERS --");

  update_player();
  
  draw_player();

  handle_firing(is_pressed(BTN_A), ship.x + 1, 52);

  draw_bullets();
  update_bullets();
    
  ssd1306_update();
}


#endif
