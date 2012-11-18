#include "gam_world.h"

gam_world* gamWorldCreate(gfx_tilemap* fg, gfx_tilemap* bg) {
	gam_world* world = AllocMem(sizeof(gam_world));
	assert(fg);

	world->fg = fg;
	world->bg = bg;
	world->w  = fg->w * fg->tileset->tile_w;
	world->h  = fg->h * fg->tileset->tile_h;
	world->actor_list  = ListCreate();
	world->player_list = ListCreate();
	return world;
}
