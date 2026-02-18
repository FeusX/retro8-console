#ifndef ASTEROID_H
#define ASTEROID_H

#include "renderer.h"
#include "player.h"
#include "balls.h"

/*static inline void ast_collision_detect()
{
  
}*/

static inline void run_asteroid(void)
{
  ast_init_player();

  for(int k = 0; k < MAX_ASTEROIDS; k++)
  { spawn_asteroid(k); }

  while(1)
  {
    ssd1306_clear();

    update_asteroids();
    ast_update_player();

    //ast_collision_detect();

    render_asteroids();
    
    ast_render_player(player.x, player.y, player.angle);
    
    ssd1306_update();

    vTaskDelay(pdMS_TO_TICKS(33));
  }
}

#endif
