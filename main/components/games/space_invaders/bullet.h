#ifndef BULLET_H
#define BULLET_H

#include "alien.h"

#define MAX_BULLETS 5

typedef struct {
  float x, y;
  bool active;
} bullet_t;

static bullet_t bullets[MAX_BULLETS];
static uint32_t last_fire_time = 0;

static void fire_bullet(float x, float y)
{
  for(int i = 0; i < MAX_BULLETS; i++)
  {
    if(!bullets[i].active)
    {
      bullets[i].x = x + 6;
      bullets[i].y = y;
      bullets[i].active = true;
    }
  }
}

static void draw_bullets()
{
  for(int i = 0; i < MAX_BULLETS; i++)
  {
    if(bullets[i].active)
    {
      ssd1306_draw_pixel((int)bullets[i].x, (int)bullets[i].y, 1);
      ssd1306_draw_pixel((int)bullets[i].x, (int)bullets[i].y + 1, 1);
    }
  }  
}

static void update_bullets()
{
  for(int i = 0; i < MAX_BULLETS; i++)
  {
    if(bullets[i].active)
    {
      bullets[i].y -= 2.5f;
      if(bullets[i].y < 0) bullets[i].active = false;
    }
  }
}

static void try_fire(float x, float y)
{
  uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;

  if(now - last_fire_time > 200)
  {
    fire_bullet(x, y);
    last_fire_time = now;
  }
}

static void bullet_collision()
{
  for(int i = 0; i < MAX_BULLETS; i++)
  {
    if(!bullets[i].active) continue;

    for(int r = 0; r < ALIEN_ROWS; r++)
    {
      for(int c = 0; c < ALIEN_COLS; c++)
      {
        if(!swarm[r][c].active) continue;

        if (bullets[i].x >= swarm[r][c].x && 
            bullets[i].x <= swarm[r][c].x + 8 &&
            bullets[i].y >= swarm[r][c].y && 
            bullets[i].y <= swarm[r][c].y + 8)
        {
          swarm[r][c].active = false;
          bullets[i].active = false;

          goto next_bullet;
        }
      }
    }
    next_bullet:;
  }
}

#endif
