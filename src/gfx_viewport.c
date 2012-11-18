#include "gfx_viewport.h"

gfx_viewport* gfxViewportCreate(unsigned int w, unsigned int h, gam_world* world) {
	Uint32 rmask, gmask, bmask;
	gfx_viewport* vp = AllocMem(sizeof(gfx_viewport));

	SDL_Rect cliprect = {16,16,w,h};
	vp->metrics.x = 0;
	vp->metrics.y = 0;
	vp->metrics.w = w;
	vp->metrics.h = h;

	/*Taken from SDL documentation*/
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
	#endif
	vp->tmbuf    = SDL_CreateRGBSurface( SDL_HWSURFACE, vp->metrics.w + 32,
										vp->metrics.h + 32, 24, rmask, gmask, bmask, 0);

	vp->actorbuf = SDL_CreateRGBSurface( SDL_HWSURFACE, vp->metrics.w + 32,
										vp->metrics.h + 32, 24, rmask, gmask, bmask, 0);
	if(!vp->tmbuf || !vp->actorbuf)
		Crash("Failed to allocate viewports.");
	else
		LogWrite(LOGLEVEL_NORMAL, "Viewports allocated : %d*%d",vp->metrics.w, vp->metrics.h);
	SDL_SetClipRect(vp->tmbuf, &cliprect);
	SDL_SetClipRect(vp->actorbuf, &cliprect);

	vp->world = world;
	return vp;
}

void gfxViewportUpdate(gfx_viewport* vp) {
	SDL_Rect srcrect = vp->metrics;
	SDL_FillRect(vp->tmbuf, NULL, 0);
	gfxTilemapClipDraw(vp->world->fg, vp->tmbuf, srcrect,
						-(vp->metrics.x % vp->world->fg->tileset->tile_w),
						-(vp->metrics.y % vp->world->fg->tileset->tile_h));
}

void gfxViewportDraw(gfx_viewport* vp, SDL_Surface* dst, int x, int y) {
	SDL_Rect dstrect = {x, y, 0, 0 };
	SDL_BlitSurface(vp->tmbuf,&vp->tmbuf->clip_rect, dst, &dstrect);
}
