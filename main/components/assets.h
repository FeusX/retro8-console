#ifndef ASSETS_H
#define ASSETS_H

// ---- SPACE INVADERS ----

static const uint8_t invader_small[] = { 0x18, 0x3C, 0x7E, 0xDB, 0xFF, 0x24, 0x5A, 0xA5 };

static const uint8_t player_ship[] = {
  0x18, 0x3C, 0x7E, 0xFF
};

static const uint8_t player_bunker_sprite[] = {
  0x5A, 0xDB, 0xDB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF  
};

// ---- TETRIS ----
const uint16_t tetrominoes[7][4] = {
  { // I
    0x0F00,
    0x2222,
    0x0F00,
    0x4444
  },

  { // T
    // brb
  },
};

#endif
