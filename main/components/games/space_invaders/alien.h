#ifndef ALIEN_H
#define ALIEN_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"
#include "esp_system.h"

#include "../../ssd1306.h"
#include "../../assets.h"
#include "bullet.h"

#define ALIEN_ROWS 3
#define ALIEN_COLS 4
#define MAX_ALIENS (ALIEN_ROWS * ALIEN_COLS)
#define MAX_ALIEN_BULLETS 2

#define ALIEN_HEIGHT 8
#define ALIEN_WIDTH 8

typedef struct {
  int8_t x, y;
  bool alive;
} alien_t;

typedef struct {
  float x, y;
  bool active;
} alien_bullet_t;

static alien_t aliens[MAX_ALIENS];

static alien_bullet_t alien_bullets[MAX_ALIEN_BULLETS];

static int8_t horde_x, horde_y, horde_dir;

static int8_t horde_speed = 2;
static int8_t aliens_alive = 12;

static int16_t alien_fire_timer;

static TickType_t step_delay, last_step_time, alien_fire_delay;
static TickType_t last_alien_fire = 0;

static void init_aliens(void)
{
  int i = 0;
  for(int r = 0; r < ALIEN_ROWS; r++)
  {
    for(int c = 0; c < ALIEN_COLS; c++)
    {
      aliens[i].x = c * (ALIEN_WIDTH + 5);
      aliens[i].y = r * (ALIEN_HEIGHT + 5);
      aliens[i].alive = true;
      i++;
    }
  }

  horde_x = 8;
  horde_y = 4;
  horde_dir = 1;

  alien_fire_timer = 1000;
  alien_fire_delay = pdMS_TO_TICKS(alien_fire_timer);
  last_alien_fire = xTaskGetTickCount();

  step_delay = pdMS_TO_TICKS(600);
  last_step_time = xTaskGetTickCount();
}

static void draw_aliens(void)
{
  for(int i = 0; i < MAX_ALIENS; i++)
  {
    if(!aliens[i].alive) continue;

    int x = horde_x + aliens[i].x;
    int y = horde_y + aliens[i].y;

    draw_sprite_h(x, y, 8, 8, invader_small);
  }
}

static void alien_bullet_collision(void)
{
  for(int b = 0; b < MAX_PLAYER_BULLETS; b++)
  {
    if(!bullets[b].active) continue;

    int bx = (int)bullets[b].x;
    int by = (int)bullets[b].y;

    for(int a = 0; a < MAX_ALIENS; a++)
    {
      if(!aliens[a].alive) continue;

      int ax = horde_x + aliens[a].x;
      int ay = horde_y + aliens[a].y;

      if(aabb_overlap(bx, by, 1, 2, ax, ay, ALIEN_WIDTH, ALIEN_HEIGHT))
      {
        bullets[b].active = false;
        aliens[a].alive = false;
        aliens_alive--;
        horde_speed += 1;
        if(alien_fire_timer > 250)
        {
          alien_fire_timer -= 50;
          alien_fire_delay = pdMS_TO_TICKS(alien_fire_timer);
        }
        return;
      }
    }
  }
}

static void alien_bounds(int *left, int *right)
{
  *left = 127;
  *right = 0;

  for(int i = 0; i < MAX_ALIENS; i++)
  {
    if(!aliens[i].alive) continue;

    int x = aliens[i].x;
    if(horde_x + x < *left) *left = horde_x + x;
    if(horde_x + x > *right) *right = horde_x + x;
  }
}

static int alien_shooter(void)
{
  int col = esp_random() % ALIEN_COLS;

  for(int r = ALIEN_ROWS - 1; r >= 0; r--)
  {
    int i = r * ALIEN_COLS + col;
    if(aliens[i].alive) return i;
  }

  return -1;
}

static void alien_fire(void)
{
  TickType_t now = xTaskGetTickCount();
  if(now - last_alien_fire < alien_fire_delay) return;

  for(int b = 0; b < MAX_ALIEN_BULLETS; b++)
  {
    if(!alien_bullets[b].active)
    {
      int a = alien_shooter();
      if(a < 0) return;

      alien_bullets[b].x = horde_x + aliens[a].x + ALIEN_WIDTH / 2;
      alien_bullets[b].y = horde_y + aliens[a].y + ALIEN_HEIGHT;
      alien_bullets[b].active = true;

      last_alien_fire = now;
      return;
    }
  }
}

static void update_alien_bullets(void)
{
  for(int i = 0; i < MAX_ALIEN_BULLETS; i++)
  {
    if(!alien_bullets[i].active) continue;

    alien_bullets[i].y += 2;
    if(alien_bullets[i].y >= 63) alien_bullets[i].active = false;
  }
}

static void update_aliens(void)
{
  TickType_t now = xTaskGetTickCount();

  if(now - last_step_time >= step_delay)
  { 
    last_step_time = now;

    int left, right;
    alien_bounds(&left, &right);

    int next_left = left + horde_dir * horde_speed;
    int next_right = right + horde_dir * horde_speed;

    bool edge_hit = (next_right + ALIEN_WIDTH >= 128 && horde_dir > 0) || (next_left <= 0 && horde_dir < 0);

    if(edge_hit)
    {
      horde_dir = -horde_dir;
      horde_y += 4;
    }
    else
    {
      horde_x += horde_dir * horde_speed;
    }
  }

  alien_fire();

  update_alien_bullets();
}

static void draw_alien_bullets(void)
{
  for(int i = 0; i < MAX_ALIEN_BULLETS; i++)
  {
    if(!alien_bullets[i].active) continue;

    ssd1306_draw_pixel((int)alien_bullets[i].x, (int)alien_bullets[i].y, 1);
    ssd1306_draw_pixel((int)alien_bullets[i].x, (int)alien_bullets[i].y + 1, 1);
  }
}

#endif
