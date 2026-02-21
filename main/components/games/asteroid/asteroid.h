#ifndef ASTEROID_H
#define ASTEROID_H

#include "../../ssd1306.h"
#include "../../font.h"

#include "renderer.h"
#include "player.h"
#include "balls.h"
#include "ast_bullet.h"

static inline void ast_collision_detect()
{
  for(int i = 0; i < MAX_ASTEROIDS; i++)
  {
    if(asteroids[i].is_destroyed) continue;

    int16_t dx = abs(player.x - (asteroids[i].x >> 4));

    if(dx > asteroids[i].rad) continue;
    
    int16_t dy = abs(player.y - (asteroids[i].y >> 4));

    if(dy > asteroids[i].rad) continue; 

    if((dx * dx) + (dy * dy) < asteroids[i].rad * asteroids[i].rad)
    {
      ssd1306_clear();
      draw_string(30, 24, "TEST");
      ssd1306_update();

      vTaskDelay(pdMS_TO_TICKS(25));
    }
  }
}

static inline void run_asteroid(void)
{
  ast_init_player();

  for(int k = 0; k < MAX_ASTEROIDS; k++)
  { spawn_asteroid(k); }

  while(1)
  {
    ssd1306_clear();

    ast_handle_shooting();
    ast_update_bullets();
    update_asteroids();
    ast_update_player();

    ast_check_bullet_collision();
    ast_collision_detect();

    ast_render_bullets();
    render_asteroids();
    ast_render_player(player.x, player.y, player.angle);
  
    ssd1306_update();

    vTaskDelay(pdMS_TO_TICKS(33));
  }
}

#endif
