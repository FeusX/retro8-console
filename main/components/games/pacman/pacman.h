#ifndef PACMAN_H
#define PACMAN_H

#include "maze.h"

void run_pacman(void)
{
  ssd1306_clear();
  draw_maze();
  ssd1306_update();
}

#endif
