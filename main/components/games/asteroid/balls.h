#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#define MAX_ASTEROIDS 4

#include <stdlib.h>

#include "esp_system.h"
#include "esp_random.h"

#include "renderer.h"

#include "../../ssd1306.h"

typedef struct {
  int16_t x, y, vx, vy;
  uint8_t rad;
  bool is_destroyed;
} asteroid_t;

static asteroid_t asteroids[MAX_ASTEROIDS];

static inline void spawn_asteroid(int idx)
{
  asteroids[idx].x = (esp_random() % SCREEN_W) << 4;
  asteroids[idx].y = (esp_random() % SCREEN_H) << 4;

  uint8_t angle = esp_random() % 256;

  asteroids[idx].vx = (COS(angle) >> 5);
  asteroids[idx].vy = (SIN(angle) >> 5);

  asteroids[idx].rad = 6;
  asteroids[idx].is_destroyed = false;
}

static inline void update_asteroids(void)
{
  for(int i = 0; i < MAX_ASTEROIDS; i++)
  {
    if(asteroids[i].is_destroyed) continue;

    asteroids[i].x += asteroids[i].vx;
    asteroids[i].y += asteroids[i].vy;

    if(asteroids[i].x < 0) asteroids[i].x = SCREEN_W << 4;
    if(asteroids[i].x > (SCREEN_W << 4)) asteroids[i].x = 0;

    if(asteroids[i].y < 0) asteroids[i].y = SCREEN_H << 4;
    if(asteroids[i].y > (SCREEN_H << 4)) asteroids[i].y = 0;
  }
}

static inline void render_asteroids(void)
{
  for(int i = 0; i < MAX_ASTEROIDS; i++)
  {
    if(!asteroids[i].is_destroyed)
    { ast_render_circle(asteroids[i].x >> 4, asteroids[i].y >> 4, asteroids[i].rad); }
  }
}


#endif
