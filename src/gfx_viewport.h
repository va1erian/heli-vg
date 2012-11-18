#include "main.h"

#ifndef GFX_VP_H
#define GFX_VP_H


typedef struct _gfx_viewport {
	SDL_Surface* tmbuf;
	SDL_Surface* actorbuf;
	SDL_Rect     metrics;
	SDL_Rect     cliprect;
	gam_world* 	 world;
} gfx_viewport;

gfx_viewport* gfxViewportCreate(unsigned int w, unsigned int h, gam_world* world);
int 		  gfxViewportScroll(gfx_viewport* vp, int x, int y);
void 		  gfxViewportUpdate(gfx_viewport* vp);
void		  gfxViewportDraw(gfx_viewport* vp, SDL_Surface* dst, int x, int y);

#endif /*GFX_VP_H*/
