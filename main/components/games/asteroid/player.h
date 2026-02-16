#ifndef ASTEROID_PLAYER_H
#define ASTEROID_PLAYER_H

#include <stdint.h>

typedef struct {
  int16_t x;
  int16_t y;
  uint8_t angle;
  uint8_t hp;
} asteroid_player_t;

#endif
