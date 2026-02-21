#ifndef AST_BULLET_H
#define AST_BULLET_H

#define AST_MAX_BULLETS 5

#include <stdint.h>

#include "../../ssd1306.h"
#include "../../input.h"
#include "renderer.h"

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

#endif
