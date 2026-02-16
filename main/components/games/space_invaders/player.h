#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>

#include "../../ssd1306.h"
#include "../../input.h"
#include "../../assets.h"
#include "../../font.h"
#include "../../states.h"
#include "alien.h"
#include "bullet.h"

typedef struct {
  float x;
  int8_t hp;
} player_t;

typedef struct {
  int8_t x, hp;
  bool alive;
} player_bunker_t;

static player_t ship = {63, 3};

static player_bunker_t player_bunker[3] = {
  {20, 5, true},
  {55, 5, true},
  {90, 5, true}
};

static inline void update_player()
{
  if(is_pressed(BTN_LEFT) && ship.x > 0) ship.x -= 2.0f;
  if(is_pressed(BTN_RIGHT) && ship.x < 112) ship.x += 2.0f;
}

static inline void draw_player()
{
  draw_sprite_h(ship.x, 52, 8, 4, player_ship);
}

static inline void bunker_bullet_collision(void)
{
  for(int i = 0; i < MAX_ALIEN_BULLETS; i++)
  {
    if(!alien_bullets[i].active) continue;

    int bx = (int)alien_bullets[i].x;
    int by = (int)alien_bullets[i].y;

    for(int j = 0; j < 3; j++)
    {
      if(!player_bunker[j].alive) continue;

      int ax = player_bunker[j].x;
      int ay = 40;

      if(aabb_overlap(bx, by, 1, 2, ax, ay, 8, 8))
      {
        alien_bullets[i].y = ay - 2;
        
        alien_bullets[i].active = false;
        player_bunker[j].hp--;
        if(player_bunker[j].hp <= 0)
        {
          player_bunker[j].alive = false;
        }

        return;
      }
    }
  }
}

static inline void draw_bunkers(void)
{
  for(int i = 0; i < 3; i++)
  {
    if(!player_bunker[i].alive) continue;

    draw_sprite_h(player_bunker[i].x, 40, 8, 8, player_bunker_sprite);
  }
}

static inline void player_bullet_collision(void)
{
  for(int i = 0; i < MAX_ALIEN_BULLETS; i++)
  {
    if(!alien_bullets[i].active) continue;

    int bx = (int)alien_bullets[i].x;
    int by = (int)alien_bullets[i].y;

    int ax = (int)ship.x;
    int ay = 52;
  
    if(aabb_overlap(bx, by, 1, 2, ax, ay, 8, 4))
    {
      alien_bullets[i].active = false;

      ship.hp--;
      
      ssd1306_clear();
      if(ship.hp > 0)
      {
        char status[16];
        sprintf(status, "%d hp left", ship.hp);
        draw_string(10, 30, status);
        ssd1306_update();
        vTaskDelay(pdMS_TO_TICKS(2000));
      }
      else
      {
        draw_string(21, 28, "GAME OVER");

        ssd1306_update();
        vTaskDelay(pdMS_TO_TICKS(2000));
        player_init = false;
        current_state = STATE_MENU;
      }
    }
  }
}

#endif
