#ifndef ASTEROID_H
#define ASTEROID_H

#include "renderer.h"
#include "player.h"

static inline void run_asteroid(void)
{
  ast_init_player();

  while(1)
  {
    ssd1306_clear();

    player.angle += 3;

    ast_render_player(player.x, player.y, player.angle);

    ast_render_circle(5, 7, 3);

    ssd1306_update();
    vTaskDelay(pdMS_TO_TICKS(33));
  }
}

#endif
