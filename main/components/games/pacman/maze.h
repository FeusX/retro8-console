#ifndef MAZE_H
#define MAZE_H

#define MAZE_HEIGHT 16
#define MAZE_WIDTH 10

static const uint8_t *maze_bitmap[10][10] = {
  {1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,1,1,0,0,0,1},
  {1,0,1,0,0,0,0,1,0,1},
  {1,0,0,0,1,1,0,0,0,1},
  {1,0,0,1,1,1,1,0,0,1},
  {1,0,1,1,1,1,1,1,0,1},
  {1,0,0,0,1,1,0,0,0,1},
  {1,1,1,0,0,0,0,1,1,1},
  {1,1,1,1,1,1,1,1,1,1}
};

void draw_maze(void)
{
  
}

#endif
