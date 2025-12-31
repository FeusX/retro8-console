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
static bool wave_pending;

static inline void run_invaders(void)
{
  if(!aliens_init)
  {
    init_aliens();
    aliens_init = true;
    wave_pending = true;
  }
  else if(aliens_alive <= 0 && !wave_pending)
  {
    wave_pending = true;
  }

  if(wave_pending)
  {
    init_aliens();
    aliens_alive = MAX_ALIENS;

    horde_speed = 2;

    wave_pending = false;
  }

  ssd1306_clear();

  update_player();
  handle_firing(is_pressed(BTN_A), ship.x + 1, 52);
  
  update_bullets();
  update_alien_bullets();
  update_aliens();
  
  alien_bullet_collision();
  bunker_bullet_collision();
  player_bullet_collision();

  draw_player();
  draw_bullets();
  draw_aliens();
  draw_alien_bullets();
  draw_bunkers();
    
  ssd1306_update();
}


#endif
