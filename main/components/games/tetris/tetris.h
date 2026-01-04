#ifndef TETRIS_H
#define TETRIS_H

#define BOARD_WIDTH  10
#define BOARD_HEIGHT 20
#define BLOCK_SIZE   3

#include "esp_system.h"
#include "esp_random.h"

#include "../../ssd1306.h"
#include "../../assets.h"

struct {
  int x, y;
  int type;
  int rotation;
} current_piece;

uint8_t board[BOARD_WIDTH][BOARD_HEIGHT] = {0};

static inline bool check_collision(int next_x, int next_y, int next_rot)
{
  uint16_t mask = pieces[current_piece.type].rotation[next_rot];

  for(int i = 0; i < 16; i++)
  {
    if(mask & 0x8000 >> i)
    {
      int px = next_x + (i % 4);
      int py = next_y + (i / 4);
      if(px < 0 || px >= BOARD_WIDTH || py > BOARD_HEIGHT) return true;
      if(py >= 0 && board[px][py]) return true;
    }
  }

  return false;
}

static inline void spawn piece()
{
  current_piece.type = esp_random() % 7;
  current_piece.rotation = 0;
  current_piece.x = BOARD_WIDTH / 2 - 2;
  current_piece.y = 0;

  if(check_collision(current_piece.x, current_piece.y, current_piece.rotation))
  {
    for(int x=0; x<BOARD_WIDTH; x++) for(int y=0; y<BOARD_HEIGHT; y++) board[x][y] = 0;
  }
}

static void run_tetris(void)
{
  
}

#endif
