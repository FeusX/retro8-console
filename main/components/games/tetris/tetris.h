#ifndef TETRIS_H
#define TETRIS_H

#define BOARD_WIDTH  10
#define BOARD_HEIGHT 20
#define BLOCK_SIZE   3

#include "esp_system.h"
#include "esp_random.h"

#include "../../input.h"
#include "../../ssd1306.h"
#include "../../assets.h"
#include "../../font.h"

struct {
  int x, y;
  int type;
  int rotation;
} current_piece;

static uint8_t board[BOARD_WIDTH][BOARD_HEIGHT] = {0};
static int16_t score = 0;
static bool initialized = false;
static bool game_over = false;

static inline bool check_collision(int next_x, int next_y, int next_rot)
{
  uint16_t mask = pieces[current_piece.type].rotation[next_rot];

  for(int i = 0; i < 16; i++)
  {
    if(mask & 0x8000 >> i)
    {
      int px = next_x + (i % 4);
      int py = next_y + (i / 4);
      if(px < 0 || px >= BOARD_WIDTH || py >= BOARD_HEIGHT) return true;
      if(py >= 0 && board[px][py]) return true;
    }
  }

  return false;
}

static inline void spawn_piece()
{
  current_piece.type = esp_random() % 7;
  current_piece.rotation = 0;
  current_piece.x = BOARD_WIDTH / 2 - 2;
  current_piece.y = 0;

  if(check_collision(current_piece.x, current_piece.y, current_piece.rotation))
  {
    game_over = true;
  }
}

static void reset_game()
{
  for(int x = 0; x < BOARD_WIDTH; x++)
  {
    for(int y = 0; y < BOARD_HEIGHT; y++)
    {
      board[x][y] = 0;
    }
  }

  score = 0;
  game_over = false;
  spawn_piece();
}

static inline void draw_game()
{
  ssd1306_clear();

  for(int y = 0; y < (BOARD_HEIGHT * BLOCK_SIZE); y++) ssd1306_draw_pixel(9, y, true);
  for(int y = 0; y < (BOARD_HEIGHT * BLOCK_SIZE); y++) ssd1306_draw_pixel(10 + (BOARD_WIDTH * BLOCK_SIZE), y, true);
  for(int x = 9; x <= 10 + (BOARD_WIDTH * BLOCK_SIZE); x++) ssd1306_draw_pixel(x, BOARD_HEIGHT * BLOCK_SIZE, true);

  for(int x = 0; x < BOARD_WIDTH; x++)
  {
    for(int y = 0; y < BOARD_HEIGHT; y++)
    {
      if(board[x][y])
      {
        for(int i = 0; i < BLOCK_SIZE; i++)
        {
          for(int j = 0; j < BLOCK_SIZE; j++)
          { ssd1306_draw_pixel(x * BLOCK_SIZE + i + 10, y * BLOCK_SIZE + j, true); }
        }
      }
    }
  }

  uint16_t mask = pieces[current_piece.type].rotation[current_piece.rotation];

  for(int i = 0; i < 16; i++)
  {
    if(mask & (0x8000 >> i))
    {
      int px = current_piece.x + (i % 4);
      int py = current_piece.y + (i / 4);

      for(int dx = 0; dx < BLOCK_SIZE; dx++)
      {
        for(int dy=0; dy<BLOCK_SIZE; dy++)
        { ssd1306_draw_pixel(px*BLOCK_SIZE + dx + 10, py*BLOCK_SIZE + dy, true); }
      } 
    }
  }
    
  ssd1306_update();
}

static void clear_lines()
{
  for(int y = BOARD_HEIGHT - 1; y >= 0; y--)
  {
    bool full = true;
    for(int x = 0; x < BOARD_WIDTH; x++)
    {
      if(!board[x][y]) { full = false; break; }
    }

    if(full)
    {
      for(int y1 = y; y1 > 0; y1--)
      {
        for(int x1 = 0; x1 < BOARD_WIDTH; x1++)
        { board[x1][y1] = board[x1][y1 - 1]; }
      }

      for(int x1 = 0; x1 < BOARD_WIDTH; x1++)
      { board[x1][0] = 0; }

      y++;
      score += 100;
    }
  }
}

static void lock_piece()
{
  uint16_t mask = pieces[current_piece.type].rotation[current_piece.rotation];

  for(int i = 0; i < 16; i++)
  {
    if(mask & (0x8000 >> i))
    {
      int px = current_piece.x + (i % 4);
      int py = current_piece.y + (i / 4);
      if(px >= 0 && px < BOARD_WIDTH && py >= 0 && py < BOARD_HEIGHT)
      { board[px][py] = 1; } 
    }
  }

  clear_lines();
  spawn_piece();
}

static void run_tetris(void)
{
  static uint32_t last_time = 0;
  const uint16_t base_delay = 200;
  uint16_t current_delay = base_delay; 
  
  if(!initialized)
  { reset_game(); last_time = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS); initialized = true; }

  if(game_over)
  {
    initialized = false;
    vTaskDelay(pdMS_TO_TICKS(500));
    ssd1306_clear();

    draw_string(21, 28, "GAME OVER");
    ssd1306_update();
    vTaskDelay(pdMS_TO_TICKS(1000));

    current_state = STATE_MENU;
    
    return;
  }

  uint32_t now = (xTaskGetTickCount() * portTICK_PERIOD_MS);

  if(is_pressed(BTN_LEFT))
  {
    if(!check_collision(current_piece.x - 1, current_piece.y, current_piece.rotation))
    {
      current_piece.x--;
      draw_game();
      vTaskDelay(pdMS_TO_TICKS(100));
    }
  }

  if(is_pressed(BTN_RIGHT))
  {
    if(!check_collision(current_piece.x + 1, current_piece.y, current_piece.rotation))
    {
      current_piece.x++;
      draw_game();
      vTaskDelay(pdMS_TO_TICKS(100));
    }
  }

  if(is_pressed(BTN_A))
  {
    int next_rot = (current_piece.rotation + 1) % 4;
    if(!check_collision(current_piece.x, current_piece.y, next_rot))
    {
      current_piece.rotation = next_rot;
      draw_game();
      vTaskDelay(pdMS_TO_TICKS(200));
    }
  }

  if(is_pressed(BTN_DOWN))
  {
    current_delay = 40;
  }

  if(now - last_time > current_delay)
  {
    if(!check_collision(current_piece.x, current_piece.y + 1, current_piece.rotation))
    { current_piece.y++; }
    else { lock_piece(); }

    draw_game();
    last_time = now;
  }
}

#endif
