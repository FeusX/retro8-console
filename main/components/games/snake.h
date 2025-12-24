#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>

#include "states.h"
#include "ssd1306.h"
#include "input.h"

#define MAX_LENGTH 100

typedef struct {
  int8_t x, y;
} pos_t;

static pos_t snake[MAX_LENGTH];
static pos_t food = {10, 5};
static int8_t snake_len = 3;
static int8_t dir = 3;
static uint8_t frame_skip = 0;

static inline void run_snake(void)
{
  ssd1306_clear();
  draw_string(5, 0, "--- SNAKE GAME ---");

  if(frame_skip++ > 5)
  {
    frame_skip = 0;

    // move the body
    for(int16_t i = snake_len - 1; i > 0; i--)
    { snake[i] = snake[i - 1]; }

    // move the head
    if(dir == 0) snake[0].y--;
    if(dir == 1) snake[0].y++;
    if(dir == 2) snake[0].x--;
    if(dir == 3) snake[0].x++;

    // wrap
    if(snake[0].x < 0)  snake[0].x = 31;
    if(snake[0].x > 31) snake[0].x = 0;
    if(snake[0].y < 3)  snake[0].y = 14;
    if(snake[0].y > 14) snake[0].y = 3;

    // food collision
    if(snake[0].x == food.x && snake[0].y == food.y)
    {
      if(snake_len < MAX_LENGTH) snake_len++;
      food.x = rand() % 32;
      food.y = 2 + (rand() % 14);
    }
  }

  if(is_pressed(BTN_UP) && dir != 1) dir = 0;
  if(is_pressed(BTN_DOWN) && dir != 0) dir = 1;
  if(is_pressed(BTN_LEFT) && dir != 3) dir = 2;
  if(is_pressed(BTN_RIGHT) && dir != 2) dir = 3;

  ssd1306_draw_pixel(food.x * 4 + 1, food.y * 4 + 1, 1);

  for(int16_t i = 0; i < snake_len; i++)
  {
    int16_t px = snake[i].x * 4;
    int16_t py = snake[i].y * 4;
    for(int16_t w = 0; w < 3; w++)
    {
      for(int16_t h = 0; h < 3; h++)
      { ssd1306_draw_pixel(px + w, py + h, 1); }
    }
  }

  if(is_pressed(BTN_B)) current_state = STATE_MENU;
  ssd1306_update();
}

#endif
