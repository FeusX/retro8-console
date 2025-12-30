#ifndef BULLET_H
#define BULLET_H

#define FIRE_DELAY 250
#define MAX_PLAYER_BULLETS 1

typedef struct {
  float x, y;
  bool active;
} player_bullet_t;

static player_bullet_t bullets[MAX_PLAYER_BULLETS];

static void fire_bullet(float x, float y)
{
  for(int i = 0; i < MAX_PLAYER_BULLETS; i++)
  {
    if(!bullets[i].active)
    {
      bullets[i].x = x + 2;
      bullets[i].y = y;
      bullets[i].active = true;
      break;
    }
  }
}

static void handle_firing(bool fired, float x, float y)
{
  static uint32_t last_fire = 0;
  uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;

  if(fired && (now - last_fire) >= FIRE_DELAY)
  {
    fire_bullet(x, y);
    last_fire = now;
  }
}

static void draw_bullets()
{
  for(int i = 0; i < MAX_PLAYER_BULLETS; i++)
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
  for(int i = 0; i < MAX_PLAYER_BULLETS; i++)
  {
    if(bullets[i].active)
    {
      bullets[i].y -= 2.5f;
      if(bullets[i].y < 8) bullets[i].active = false;
    }
  }
}

static inline bool aabb_overlap(
  int ax, int ay, int aw, int ah,
  int bx, int by, int bw, int bh
)
{
  return !(ax + aw <= bx ||
           ax >= bx + bw ||
           ay + ah <= by ||
           ay >= by + bh);
}

#endif
