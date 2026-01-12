#ifndef MAZE_H
#define MAZE_H

#define MAZE_WIDTH  21
#define MAZE_HEIGHT 10
#define TILE_SIZE   6   

static const uint8_t maze_map[MAZE_HEIGHT][MAZE_WIDTH] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1},
  {1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,1},
  {1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1},
  {1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void draw_maze(void)
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
        ssd1306_draw_pixel(px + 2, py + 2, true);
        ssd1306_draw_pixel(px + 3, py + 3, true);   
      }
    }
  }  
}

#endif
