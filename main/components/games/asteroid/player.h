#ifndef ASTEROID_PLAYER_H
#define ASTEROID_PLAYER_H

#include <stdint.h>

typedef struct {
  int16_t x;
  int16_t y;
  int8_t vx;
  int8_t vy;
  uint8_t angle;
  uint8_t hp;
} ast_player_t;

static ast_player_t player;

static inline void ast_init_player(void)
{
  player.x = 64;
  player.y = 32;
  player.angle = 0;
  player.hp = 3;
  player.vx = 0;
  player.vy = 0;
}

static inline void ast_update_player(void)
{
  
}

#endif
