#ifndef ALIEN_H
#define ALIEN_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../../ssd1306.h"
#include "../../assets.h"

#define ALIEN_ROWS 3
#define ALIEN_COLS 5
#define MAX_ALIENS (ALIEN_ROWS * ALIEN_COLS)

#define ALIEN_HEIGHT 8
#define ALIEN_WIDTH 8

typedef struct {
  int8_t x, y;
  bool alive;
} alien_t;

static alien_t aliens[MAX_ALIENS];

static int8_t horde_x, horde_y, horde_dir;

static TickType_t step_delay;
static TickType_t last_step_time;

static void init_aliens(void)
{
  int i = 0;
  for(int r = 0; r < ALIEN_ROWS; r++)
  {
    for(int c = 0; c < ALIEN_COLS; c++)
    {
      aliens[i].x = c * (ALIEN_WIDTH + 4);
      aliens[i].y = r * (ALIEN_HEIGHT + 4);
      aliens[i].alive = true;
      i++;
    }
  }

  horde_x = 8;
  horde_y = 16;
  horde_dir = 1;

  step_delay = pdMS_TO_TICKS(600);
  last_step_time = xTaskGetTickCount();
}

static void draw_aliens(void)
{
  for(int i = 0; i < MAX_ALIENS; i++)
  {
    if(!aliens[i].alive) continue;

    int x = horde_x + aliens[i].x + 5;
    int y = horde_y + aliens[i].y;

    draw_sprite_h(x, y, 8, 8, invader_small);
  }
}

#endif
