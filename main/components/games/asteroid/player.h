#ifndef ASTEROID_PLAYER_H
#define ASTEROID_PLAYER_H

#define AST_MAX_BULLETS 5

#include <stdint.h>

#include "../../ssd1306.h"
#include "../../input.h"

typedef struct {
  int16_t x, y, vx, vy;
  uint8_t angle, hp;
} ast_player_t;

static ast_player_t player;

static inline void ast_init_player(void)
{
  player.x = 64;
  player.y = 32;
  player.angle = 0;
  player.hp = 3;
  player.vx = player.vy = 0;
}

static inline void ast_render_player(int16_t ship_x, int16_t ship_y, uint8_t angle)
{
  int16_t rot_x0 = ship_x + ((5 * COS(angle)) >> 8);
  int16_t rot_y0 = ship_y + ((5 * SIN(angle)) >> 8);

  int16_t rot_x1 = ship_x + ((-4 * COS(angle) - -3 * SIN(angle)) >> 8);
  int16_t rot_y1 = ship_y + ((-4 * SIN(angle) + -3 * COS(angle)) >> 8);

  int16_t rot_x2 = ship_x + ((-4 * COS(angle) - 3 * SIN(angle)) >> 8);
  int16_t rot_y2 = ship_y + ((-4 * SIN(angle) + 3 * COS(angle)) >> 8);

  ast_render_triangle(rot_x0, rot_y0, rot_x1, rot_y1, rot_x2, rot_y2);
}

static inline void ast_update_player(void)
{
  if(is_pressed(BTN_LEFT)) player.angle -= 6;
  if(is_pressed(BTN_RIGHT)) player.angle += 6;

  if(is_pressed(BTN_B))
  { player.vx += (COS(player.angle) >> 5); player.vy += (SIN(player.angle) >> 5); } // calculate the velocity depending on
                                                                                    // player's axis components
                                                                                    // SIN is vertical, COS is horizontal
  player.x += (player.vx >> 4);
  player.y += (player.vy >> 4);

  player.x = CLAMP(player.x, 8, 120);
  player.y = CLAMP(player.y, 5, 59);

  player.vx = CLAMP(player.vx, -20, 20);
  player.vy = CLAMP(player.vy, -20, 20);

  if(!is_pressed(BTN_B))
  {
    if(player.vx > 0) player.vx--;
    else if(player.vx < 0) player.vx++;

    if(player.vy > 0) player.vy--;
    else if(player.vy < 0) player.vy++;
  }
}

#endif
