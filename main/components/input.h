#ifndef INPUT_H
#define INPUT_H

#include "driver/gpio.h"

#define BTN_UP 12
#define BTN_DOWN 27
#define BTN_LEFT 13
#define BTN_RIGHT 14
#define BTN_A 16
#define BTN_B 18

static inline void inputs_init()
{
  gpio_config_t io_conf = {
    .intr_type = GPIO_INTR_DISABLE,
    .mode = GPIO_MODE_INPUT,
    .pin_bit_mask = (1ULL << BTN_UP) | (1ULL << BTN_DOWN) | (1ULL << BTN_LEFT)
                    | (1ULL << BTN_RIGHT) | (1ULL << BTN_A) | (1ULL << BTN_B),
    .pull_down_en = 0,
    .pull_up_en = 1
  };

  gpio_config(&io_conf);
}

static inline bool is_pressed(int btn_pin)
{
  return gpio_get_level(btn_pin) == 0;
}

#endif
