#ifndef AST_BULLET_H
#define AST_BULLET_H

#define AST_MAX_BULLETS 5

#include <stdint.h>

#include "../../ssd1306.h"
#include "../../input.h"
#include "renderer.h"
#include "balls.h"

static int8_t fire_cooldown = 0;

typedef struct {
  int16_t x, y;
  uint8_t angle;
  bool is_active;
} ast_bullet_t;

static ast_bullet_t ast_bullets[AST_MAX_BULLETS];

static inline void ast_shoot(void)
{
  for(int i = 0; i < AST_MAX_BULLETS; i++)
  {
    if(!ast_bullets[i].is_active)
    {
      ast_bullets[i].is_active = true;
      ast_bullets[i].x = player.x;
      ast_bullets[i].y = player.y;
      ast_bullets[i].angle = player.angle;

      break;
    }
  }
}

static inline void ast_handle_shooting(void)
{
  if(fire_cooldown > 0) fire_cooldown--;

  if(is_pressed(BTN_A) && fire_cooldown == 0)
  { ast_shoot(); fire_cooldown = 5;}
}

static inline void ast_update_bullets(void)
{
  for(int i = 0; i < AST_MAX_BULLETS; i++)
  {
    if(ast_bullets[i].is_active)
    {
      ast_bullets[i].x += (COS(ast_bullets[i].angle) >> 6);
      ast_bullets[i].y += (SIN(ast_bullets[i].angle) >> 6);

      if(ast_bullets[i].x < 0 || ast_bullets[i].x >= SCREEN_W || 
         ast_bullets[i].y < 0 || ast_bullets[i].y >= SCREEN_H)
      { ast_bullets[i].is_active = false; }
    }
  }
}

static inline void ast_render_bullets(void)
{
  for(int i = 0; i < AST_MAX_BULLETS; i++)
  {
    if(ast_bullets[i].is_active)
    { ssd1306_draw_pixel(ast_bullets[i].x, ast_bullets[i].y, true); }
  }
}

static inline void ast_check_bullet_collision(void)
{
  for(int i = 0; i < AST_MAX_BULLETS; i++)
  {
    if(!ast_bullets[i].is_active) continue;
    for(int j = 0; j < MAX_ASTEROIDS; j++)
    {
      if(asteroids[j].is_destroyed) continue;

      int16_t bdx = abs(ast_bullets[i].x - (asteroids[j].x >> 4));
      if(bdx > asteroids[j].rad + 1) continue;
      
      int16_t bdy = abs(ast_bullets[i].y - (asteroids[j].y >> 4));
      if(bdy > asteroids[j].rad + 1) continue;

      if((bdx * bdx) + (bdy * bdy) < (asteroids[j].rad * asteroids[j].rad))
      {
        ast_bullets[i].is_active = false; 
        asteroids[j].is_destroyed = true;
        
        ssd1306_clear();
        draw_string(30, 24, "HIT");
        ssd1306_update();

        vTaskDelay(pdMS_TO_TICKS(25));

        break;
      }
    }
  }
}

#endif