#ifndef GAME_REG_H
#define GAME_REG_H

#include "games/space_invaders/invaders.h"
#include "games/snake/snake.h"
#include "games/tetris/tetris.h"
#include "games/pacman/pacman.h"

typedef void (*game_loop)(void);
typedef struct {
  system_state_t state;
  game_loop run;
} game_reg_t;

static const game_reg_t games_list[] = {
    { STATE_GAME_SPACE_INVADERS, run_invaders },
    { STATE_GAME_SNAKE,          run_snake    },
    { STATE_GAME_TETRIS,         run_tetris   },
    { STATE_GAME_PACMAN,         run_pacman   }
};

#endif