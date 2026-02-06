#ifndef DUNGEON_EXPLORER_H
#define DUNGEON_EXPLORER_H

#include <stdlib.h>

#include "esp_system.h"
#include "esp_random.h"

#include "../../ssd1306.h"
#include "../../assets.h"

#include "map.h"

static inline void run_dungeon_explorer(void)
{
  ssd1306_clear();
  
  generate_dungeon();

  draw_dungeon();

  ssd1306_update();

  vTaskDelay(pdMS_TO_TICKS(2000));
  vTaskDelay(pdMS_TO_TICKS(33));
}

#endif
