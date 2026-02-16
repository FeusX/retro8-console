#ifndef ASTEROID_H
#define ASTEROID_H

#include "renderer.h"
#include "player.h"

static asteroid_player_t player;

static inline void run_asteroid(void)
{
  player.x = 64;
  player.y = 32;
  player.angle = 0;
  player.hp = 3;

  while(1)
  {
    ssd1306_clear();

    player.angle += 3;

    render_player(player.x, player.y, player.angle);

    ssd1306_update();
    vTaskDelay(pdMS_TO_TICKS(33));
  }
}

#endif
