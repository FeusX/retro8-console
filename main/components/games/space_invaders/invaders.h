#ifndef INVADERS_H
#define INVADERS_H

#include "../../ssd1306.h"
#include "../../input.h"
#include "../../assets.h"
#include "bullet.h"
#include "alien.h"
#include "player.h"

#define MAX_BULLETS 5
#define ALIEN_ROWS 3
#define ALIEN_COLS 8

static bool is_invaders_init = false;
int active_aliens = 0;

static inline void run_invaders() {

    if (!is_invaders_init) {
        init_aliens();      // <--- calling this fixes the unused warning
        
        // Reset player position
        ship.x = 60;
        
        // Reset bullets
        for(int i=0; i<MAX_BULLETS; i++) bullets[i].active = false;

        is_invaders_init = true;
    }
    // 1. Logic Updates
    update_player();
    update_bullets();
    update_aliens();
    bullet_collision(); // We'll put this logic in bullets.h

    // 2. Input
    if(is_pressed(BTN_A)) {
        try_fire(ship.x, 54); 
    }

    // 3. Rendering
    ssd1306_clear();
    
    draw_ship();    // Uses your B-2 model
    draw_bullets();
    
    for(int r = 0; r < ALIEN_ROWS; r++) {
        for(int c = 0; c < ALIEN_COLS; c++) {
            if(swarm[r][c].active) {
                draw_alien((int)swarm[r][c].x, (int)swarm[r][c].y);
                active_aliens++;
            }
        }
    }

    if(active_aliens == 0)
    {
        init_aliens();
        swarm_speed += 1.0f;
    }
    
    ssd1306_update();
}
#endif
