#ifndef GHOST_H
#define GHOST_H

typedef struct {
  uint8_t x;
  uint8_t y;
} ghost_t;

ghost_t spawn_ghost(int start_x, int start_y)
{
  ghost_t g;
  g.x = start_x;
  g.y = start_y;

  return g;
}

void move_ghost(ghost_t *g, int8_t dx, int8_t dy)
{
  g->x += dx;
  g->y += dy;
}

uint8_t get_x(const ghost_t *g)
{ return g->x; }

uint8_t get_y(const ghost_t *g)
{ return g->y; }

#endif
