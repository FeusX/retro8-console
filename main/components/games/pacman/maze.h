#ifndef MAZE_H
#define MAZE_H

#define MAZE_WIDTH 16
#define MAZE_HEIGHT 8
#define TILE_SIZE 8

static const uint8_t maze_map[MAZE_HEIGHT][MAZE_WIDTH] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
  {1,0,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
  {1,0,1,0,1,1,1,0,1,1,1,1,0,1,0,1},
  {1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
  {1,0,1,1,1,0,1,1,1,0,1,0,1,1,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static inline void draw_maze(void)
{
  for(int x = 0; x < MAZE_WIDTH; x++)
  {
    for(int y = 0; y < MAZE_HEIGHT; y++)
    {
      uint8_t tile_type = maze_map[y][x];

      int16_t px = x * TILE_SIZE;
      int16_t py = y * TILE_SIZE;

      if(tile_type == 1)
      {
        for(int i = 0; i < TILE_SIZE; i++)
        {
          for(int j = 0; j < TILE_SIZE; j++)
          {
            ssd1306_draw_pixel(px + i, py + j, true);
          }
        }
      }
      else
      {
        int center = TILE_SIZE / 2;
        ssd1306_draw_pixel(px + center, py + center, true);
        ssd1306_draw_pixel(px + center - 1, py + center, true);    
        ssd1306_draw_pixel(px + center, py + center - 1, true);    
        ssd1306_draw_pixel(px + center - 1, py + center - 1, true);    
      }
    }
  }  
}

#endif
