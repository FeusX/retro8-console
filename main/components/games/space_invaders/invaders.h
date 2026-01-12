#ifndef INVADERS_H
#define INVADERS_H

#include <stdbool.h>

#include "../../ssd1306.h"
#include "../../input.h"
#include "../../assets.h"
#include "../../font.h"

static bool aliens_init = false;
static bool player_init = false;
static bool wave_pending;

#include "bullet.h"
#include "player.h"
#include "alien.h"

static inline void reset_invaders(void)
{
  ship.x = 63;
  ship.hp = 3;

  int start_x[3] = {20, 55, 90};

  for(int i = 0; i < 3; i++)
  {
    player_bunker[i].x = start_x[i];
    player_bunker[i].hp = 5;
    player_bunker[i].alive = true;
  }

  for(int i = 0; i < MAX_ALIEN_BULLETS; i++)
  { alien_bullets[i].active = false; }

  bullets[0].active = false;

  aliens_init = false;
  player_init = true;
}

static inline void run_invaders(void)
{
  if(!player_init)
  { reset_invaders(); }
  if(!aliens_init)
  {
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
