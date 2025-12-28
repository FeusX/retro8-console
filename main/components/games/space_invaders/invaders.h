#ifndef INVADERS_H
#define INVADERS_H

#include "../../ssd1306.h"
#include "../../input.h"
#include "../../assets.h"
#include "../../font.h"
#include "bullet.h"
#include "player.h"
#include "alien.h"

static bool aliens_init = false;

static inline void run_invaders(void)
{
  if(!aliens_init) init_aliens();
  ssd1306_clear();

  draw_string(3, 0, "-- SPACE INVADERS --");

  update_player();
  
  draw_player();

  handle_firing(is_pressed(BTN_A), ship.x + 1, 52);

  draw_bullets();
  update_bullets();
  draw_aliens();
    
  ssd1306_update();
}


#endif
