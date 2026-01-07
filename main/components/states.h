#ifndef STATES_H
#define STATES_H

typedef enum {
  STATE_MENU,
  STATE_GAME_SPACE_INVADERS,
  STATE_GAME_SNAKE,
  STATE_GAME_TETRIS
} system_state_t;

extern system_state_t current_state;

#endif
