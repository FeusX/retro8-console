#ifndef INVADERS_H
#define INVADERS_H

#include "../ssd1306.h"
#include "../input.h"
#include "../assets.h"

int16_t alien_x = 50;
int16_t alien_y = 20;

static inline void run_invaders(void)
{
  while(1)
  {
    ssd1306_clear();
    draw_string(5, 0, "--- SPACE GAME ---");

    draw_sprite_h(alien_x, alien_y, 8, 8, invader_small);

    if(is_pressed(BTN_LEFT)) alien_x -= 2;
    if(is_pressed(BTN_RIGHT)) alien_x += 2;
    if(is_pressed(BTN_UP)) alien_y -= 2;
    if(is_pressed(BTN_DOWN)) alien_y += 2;

    alien_x = CLAMP(alien_x, 0, 112);
    alien_y = CLAMP(alien_y, 10, 48);

    ssd1306_update();

    vTaskDelay(pdMS_TO_TICKS(33));
  }  
}

#endif
