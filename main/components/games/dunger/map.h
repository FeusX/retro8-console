#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

#include "esp_system.h"
#include "esp_random.h"

#include "../../ssd1306.h"
#include "../../assets.h"

#define DUNGEON_TILE_SIZE 4
#define DUNGEON_H 16
#define DUNGEON_W 32

#define ROOM_H    8
#define ROOM_W    8
#define ROOMS_X   (DUNGEON_W / ROOM_W)
#define ROOMS_Y   (DUNGEON_H / ROOM_H)

enum env {
	TILE_WALL = 0,
	TILE_FLOOR,
	TILE_CHEST,
	TILE_EXIT,
	TILE_COUNT
};

typedef struct {
	int8_t x, y, w, h, center_x, center_y;
} room_t;

static const uint8_t *sprite_lookup[TILE_COUNT] = {
	[TILE_WALL] = de_wall,
	[TILE_FLOOR] = NULL,
	[TILE_CHEST] = de_chest,
	[TILE_EXIT] = de_exit
};

static uint8_t dungeon[DUNGEON_W][DUNGEON_H];

static inline void clear_dungeon(void)
{
	for(int i = 0; i < DUNGEON_W; i++)
	{
		for(int j = 0; j < DUNGEON_H; j++)
		{dungeon[i][j] = TILE_WALL;}
	}
}

static inline bool is_moveable(int x, int y)
{
	if(x < 0 || y < 0 || x >= DUNGEON_W || y >= DUNGEON_H) return false;

	return true;
}

static inline void draw_border(void)
{
	for(int x = 0; x < DUNGEON_W; x++)
	{
		dungeon[x][0] = TILE_WALL;
		dungeon[x][DUNGEON_H - 1] = TILE_WALL;
	}

	for(int y = 0; y < DUNGEON_H; y++)
	{
	  dungeon[0][y] = TILE_WALL;
		dungeon[DUNGEON_W-1][y] = TILE_WALL;
	}
}

static inline void generate_dungeon(void)
{
	clear_dungeon();
	int num_rooms = (esp_random() % 3) + 2;

	room_t rooms[4];

	for(int i = 0; i < num_rooms; i++)
	{
		// randomize pos and size
		rooms[i].w = (esp_random() % 4) + 4;
    rooms[i].h = (esp_random() % 4) + 4;
    
    rooms[i].x = (esp_random() % (DUNGEON_W - rooms[i].w - 2)) + 1;
    rooms[i].y = (esp_random() % (DUNGEON_H - rooms[i].h - 2)) + 1;
    
    rooms[i].center_x = rooms[i].x + (rooms[i].w / 2);
    rooms[i].center_y = rooms[i].y + (rooms[i].h / 2);

    for(int x = rooms[i].x; x < rooms[i].x + rooms[i].w; x++)
    {
    	for(int y = rooms[i].y; y < rooms[i].y + rooms[i].h; y++)
    	{ dungeon[x][y] = TILE_FLOOR; }
    }

    if(i > 0)
    {
    	// get start and end pos as horizontal
   		int start_x = (rooms[i - 1].center_x < rooms[i].center_x) ? rooms[i - 1].center_x : rooms[i].center_x;
   		int end_x = (rooms[i].center_x < rooms[i - 1].center_x) ? rooms[i].center_x : rooms[i - 1].center_x;

   		for(int x = start_x; x <= end_x; x++)
   		{ dungeon[x][rooms[i - 1].center_y] = TILE_FLOOR; } // generate

			// get start and end pos as vertical
   		int start_y = (rooms[i - 1].center_y < rooms[i].center_y) ? rooms[i - 1].center_y : rooms[i].center_y;
   		int end_y = (rooms[i].center_y < rooms[i - 1].center_y) ? rooms[i].center_y : rooms[i - 1].center_y;

   		for (int y = start_y; y <= end_y; y++)
   		{ dungeon[rooms[i].center_x][y] = TILE_FLOOR; } // generate
    }
	}

	dungeon[rooms[num_rooms - 1].center_x][rooms[num_rooms - 1].center_y] = TILE_EXIT;

	dungeon[rooms[0].center_x][rooms[0].center_y] = TILE_CHEST;

	draw_border();
}

static inline void draw_dungeon(void)
{
	for(int x = 0; x < DUNGEON_W; x++)
	{
		for(int y = 0; y < DUNGEON_H; y++)
		{
			uint8_t tile_id = dungeon[x][y];

			const uint8_t *sprite = sprite_lookup[tile_id];

			if(sprite != NULL)
			{
				draw_sprite_h(x * DUNGEON_TILE_SIZE, y * DUNGEON_TILE_SIZE, DUNGEON_TILE_SIZE, DUNGEON_TILE_SIZE, sprite);
			}
		}	
	}
}

#endif
