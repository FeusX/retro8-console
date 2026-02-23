#ifndef ASTEROID_H
#define ASTEROID_H

#include <stdio.h>

#include "../../ssd1306.h"
#include "../../font.h"
#include "../../states.h"

#include "renderer.h"
#include "player.h"
#include "balls.h"
#include "ast_bullet.h"

static inline bool ast_collision_detect()
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
      char ast_status[16];
      ssd1306_clear();
      player.hp--;
      asteroids[i].is_destroyed = true; // destroy the asteroid upon impact
      if(player.hp <= 0)
      {
        draw_string(30, 24, "GAME OVER");
        ssd1306_update();
        vTaskDelay(pdMS_TO_TICKS(1000));

        ssd1306_clear();
        sprintf(ast_status, "%d ASTEROIDS", destroyed_asteroids);
        draw_string(20, 24, ast_status);
        draw_string(25, 33, "DESTROYED");
        ssd1306_update();
        vTaskDelay(pdMS_TO_TICKS(1000));

        return true;
      }
      
      sprintf(ast_status, "%d HP LEFT", player.hp);
      draw_string(30, 24, ast_status);
      ssd1306_update();

      vTaskDelay(pdMS_TO_TICKS(500));
    }
  }

  return false;
}

static inline void run_asteroid(void)
{
  ast_init_player();

  destroyed_asteroids = 0;

  for(int i = 0; i < MAX_ASTEROIDS; i++)
  { asteroids[i].is_destroyed = true; }

  for(int k = 0; k < MAX_ASTEROIDS - 3; k++)
  { spawn_asteroid(k); }

  while(1)
  {
    ssd1306_clear();

    ast_handle_shooting();
    ast_update_bullets();
    update_asteroids();
    ast_update_player();

    ast_check_bullet_collision();
    
    if(ast_collision_detect() == true)
    { current_state = STATE_MENU; break; }

    int8_t active_asteroids = 0;
    for(int i = 0; i < MAX_ASTEROIDS; i++)
    { if(!asteroids[i].is_destroyed) active_asteroids++; }

    if(active_asteroids < 5 && esp_random() % 50 < 1) // spawn asteroid by 2% chance per frame
    {
      for(int i = 0; i < MAX_ASTEROIDS; i++)
      {
        if(asteroids[i].is_destroyed)
        { spawn_asteroid(i); break; }
      }
    }

    ast_render_bullets();
    render_asteroids();
    ast_render_player(player.x, player.y, player.angle);
  
    ssd1306_update();

    vTaskDelay(pdMS_TO_TICKS(33));
  }
}

#endif