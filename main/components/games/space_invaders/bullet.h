#ifndef BULLET_H
#define BULLET_H

#define MAX_BULLETS 5

typedef struct {
  float x, y;
  bool active;
} bullet_t;

static bullet_t bullets[MAX_BULLETS];

static void fire_bullet(float x, float y)
{
  for(int i = 0; i < MAX_BULLETS; i++)
  {
    if(!bullets[i].active)
    {
      bullets[i].x = x + 6;
      bullets[i].y = y;
      bullets[i].active = true;
    }
  }
}

static void draw_bullets()
{
  for(int i = 0; i < MAX_BULLETS; i++)
  {
    if(bullets[i].active)
    {
      ssd1306_draw_pixel((int)bullets[i].x, (int)bullets[i].y, 1);
      ssd1306_draw_pixel((int)bullets[i].x, (int)bullets[i].y + 1, 1);
    }
  }  
}

static void update_bullets()
{
  for(int i = 0; i < MAX_BULLETS; i++)
  {
    if(bullets[i].active)
    {
      bullets[i].y -= 2.5f;
      if(bullets[i].y < 0) bullets[i].active = false;
    }
  }
}

#endif
