#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "esp_system.h"
#include "esp_random.h"
#include "../../states.h"
#include "../../ssd1306.h"
#include "../../input.h"

#define MAX_LENGTH 100

typedef struct {
  int8_t x, y;
} pos_t;

static pos_t snake[MAX_LENGTH];
static pos_t food = {10, 5};
static int8_t snake_len = 3;
static int8_t dir = 3;
static uint8_t frame_skip = 0;
static uint8_t apples = 0;
static bool active = false;

static bool food_pos_check(int8_t x, int8_t y)
{
  for(int i = 0; i < snake_len; i++)
  {
    if(snake[i].x == x && snake[i].y == y)
    {
      return true;
    }
  }

  return false;
}

static void run_snake(void)
{
  if(!active)
  {
    snake_len = 3;
    apples = 0;
    dir = 3;

    snake[0].x = 10; snake[0].y = 5;
    snake[1].x = 9;  snake[1].y = 5;
    snake[2].x = 8;  snake[2].y = 5;

    active = true;
  }
  
  ssd1306_clear();
  draw_string(5, 0, "--- SNAKE GAME ---");

  char score_str[16];
  sprintf(score_str, "SCORE: %d", apples);
  draw_string(30, 55, score_str);

  if(frame_skip++ > 2)
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
    if(snake[0].y < 3)  snake[0].y = 13;
    if(snake[0].y > 13) snake[0].y = 3;

    // food collision
    if(snake[0].x == food.x && snake[0].y == food.y)
    {
      if(snake_len < MAX_LENGTH) snake_len++;
      do{
        food.x = esp_random() % 32;
        food.y = 3 + (esp_random() % 11);
      }while(food_pos_check(food.x, food.y));
      apples++;
    }

    for(int i = 1; i < snake_len; i++)
    {
      if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
      {
        active = false;
        ssd1306_clear();
        draw_string(3, 20, "GAME OVER");
        ssd1306_update();
        vTaskDelay(pdMS_TO_TICKS(2000));
        current_state = STATE_MENU;
        return;
      }
    }
  }

  if(is_pressed(BTN_UP) && dir != 1) dir = 0;
  if(is_pressed(BTN_DOWN) && dir != 0) dir = 1;
  if(is_pressed(BTN_LEFT) && dir != 3) dir = 2;
  if(is_pressed(BTN_RIGHT) && dir != 2) dir = 3;

  ssd1306_draw_pixel(food.x * 4 + 1, food.y * 4 + 1, 1);

  for(int i = 0; i < snake_len; i++)
  {
    int px = snake[i].x * 4;
    int py = snake[i].y * 4;
    for(int w = 0; w < 3; w++)
    {
      for(int h = 0; h < 3; h++)
      { ssd1306_draw_pixel(px + w, py + h, 1); }
    }
  }

  ssd1306_update();
}

#endif
