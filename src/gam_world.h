#include "main.h"

#ifndef GAME_WORLD_H
#define GAME_WORLD_H

typedef struct _gam_world{
	unsigned int w , h;
	gfx_tilemap* fg;
	gfx_tilemap* bg;
	linked_list* actor_list;
	linked_list* player_list;
} gam_world;

gam_world* gamWorldCreate(gfx_tilemap* fg, gfx_tilemap* bg);

int gamWorldUpdate(gam_world* world, float dtime);

#endif /*GAME_WORLD_*/
