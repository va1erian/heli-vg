#include "gfx_tilemap.h"
#include "test.map"
gfx_tileset* gfxTilesetCreate(SDL_Surface* surf,
                            unsigned short tile_w,
                            unsigned short tile_h) {
    gfx_tileset* t = (gfx_tileset*)malloc(sizeof(gfx_tileset));
    t->tile_w      = tile_w;
    t->tile_h      = tile_h;
    t->w           = div(surf->w, tile_w).quot;
    t->h           = div(surf->h, tile_h).quot;
    t->tileset_gfx = surf;
    return t;
}

/*inline void gfxtileset_drawtile(gfx_tileset* tileset,
                                unsigned int tile_index,
                                int x, int y,
                                SDL_Surface* dest) {
    div_t pos = div(tile_index, tileset->w);
    SDL_Rect srcrect = {pos.rem * tileset->tile_w,
                        pos.quot * tileset->tile_h,
                        tileset->tile_w,
                        tileset->tile_h};

    SDL_Rect dstrect = {x, y, 0, 0};
    SDL_BlitSurface(tileset->tileset_gfx,
                    &srcrect,
                    dest,
                    &dstrect);
}
*/

void gfxPuts(char* string, gfx_tileset* t,
              int x, int y, SDL_Surface* dest) {
    SDL_Rect srcrect = {0, 0, t->tile_w, t->tile_h};
    SDL_Rect dstrect = {x, y, 0, 0};
    int i;
    div_t d;
    for(i = 0; i < strlen(string); i++) {
        d = div((string[i])- GFX_ASCII_OFFSET, t->w);
        srcrect.x = d.rem  * t->tile_w;
        srcrect.y = d.quot * t->tile_h;
        SDL_BlitSurface(t->tileset_gfx,
                        &srcrect,
                        dest,
                        &dstrect);
        dstrect.x += t->tile_w;
    }
}


void gfxPrintFormatted(gfx_tileset* t, int x, int y,
                SDL_Surface* dest, char* format, ...) {
    va_list args;
    char string[64];
    va_start(args, format);
    vsnprintf(string,64, format, args); //64 Should be sufficient
    gfxPuts(string, t, x, y, dest);
}

inline int gfxTextWidth(char* string, gfx_tileset* t) {
    return strlen(string) * t->tile_w;
}

gfx_tilemap* gfxTilemapCreateFromFile(char* path, int w,
                             int h) {
    FILE* f = fopen(path, "rb");
    gfx_tile* tiles = malloc(sizeof(gfx_tile) * h * w);
    gfx_tilemap* tilemap = malloc(sizeof(gfx_tilemap));
    assert(tilemap);
    int i;
    short int* buffer = malloc(sizeof(short int));
    for(i = 0; !feof(f); i++) {
        fread(buffer, sizeof(short int), 1, f); //TODO:Fix this Hack-ey shit
        tiles[i].index = ((*buffer>>5)-1);
    }
    fclose(f);
    tilemap->w = w;
    tilemap->h = h;
    tilemap->clip_rect = 0;
    tilemap->tiles = tiles;
    return tilemap;
}

void gfxTilemapTestDraw(gfx_tilemap* tm, SDL_Surface* dst, int xoff, int yoff) {
	SDL_Rect dstrect = {xoff,yoff,0,0};
	SDL_Rect srcrect = {0, 0, tm->tileset->tile_w, tm->tileset->tile_h};
	div_t srcpos;
	int x, y;
	short t;
	for(y = 0; y < 20; y++) {
		for(x = 0; x < 25; x++) {
			t = derp_map[x+y*25];
			srcpos = div(t-1, tm->tileset->w);
			srcrect.x = srcpos.rem  * tm->tileset->tile_w;
			srcrect.y = srcpos.quot * tm->tileset->tile_h;
			dstrect.x = (x * tm->tileset->tile_w) + xoff;
			dstrect.y = (y * tm->tileset->tile_h) + yoff;
			SDL_BlitSurface(tm->tileset->tileset_gfx,
                    &srcrect,
                    dst,
                    &dstrect);
		}
	}

}

/* FIXME: This function actually draw 2 more additional tile strip than asked
for the scrolling routines. It's obviously ugly as hell */
void gfxTilemapClipDraw(gfx_tilemap* tm, SDL_Surface* dst, SDL_Rect clip, int xoff, int yoff) {
	SDL_Rect srcrect = {0, 0, tm->tileset->tile_w, tm->tileset->tile_h};
	SDL_Rect tilerect = {div(clip.x,tm->tileset->tile_w).quot * tm->tileset->tile_w,
						 div(clip.y,tm->tileset->tile_h).quot * tm->tileset->tile_h,
						 /*This is rather odd; but we need the w and h dist. from
						 the origin because the iterators are starting from 0 */
						 clip.w + 2 * tm->tileset->tile_w + clip.x - (clip.w  % tm->tileset->tile_w),
						 clip.h + 2 * tm->tileset->tile_h + clip.y - (clip.h  % tm->tileset->tile_h)};
	SDL_Rect dstrect = {0,0,0,0};
	int x, y;
	div_t srcpos;
	for(y = 0; y < (tilerect.h / tm->tileset->tile_h);y++) {
		for(x = 0; x < (tilerect.w / tm->tileset->tile_w); x++) {
			srcpos = div(derp_map[x+y*25] -1, tm->tileset->w);
			srcrect.x = srcpos.rem  * tm->tileset->tile_w;
			srcrect.y = srcpos.quot * tm->tileset->tile_h;
			dstrect.x = (x * tm->tileset->tile_w) + xoff - tilerect.x;
			dstrect.y = (y * tm->tileset->tile_h) + yoff - tilerect.y;
			SDL_BlitSurface(tm->tileset->tileset_gfx,
                    &srcrect,
                    dst,
                    &dstrect);
		}
	}
}

void gfxTilemapDrawVStrip(gfx_tilemap* tm, SDL_Surface* dst, int stripx, int xoff,int yoff) {
	SDL_Rect srcrect = {0, 0, tm->tileset->tile_w, tm->tileset->tile_h};
	SDL_Rect dstrect = {xoff,0,0,0};
	div_t srcpos;
	int y;
	for(y = 0; y < tm->h; y++) {
		srcpos = div(derp_map[stripx + y*25] - 1, tm->tileset->w);
		srcrect.x = srcpos.rem * tm->tileset->tile_w;
		srcrect.y = srcpos.quot * tm->tileset->tile_h;
		dstrect.x = xoff; /* Doesn't work whithout this line: WHY ? */
		dstrect.y = (y * tm->tileset->tile_h) + yoff;
		SDL_BlitSurface(tm->tileset->tileset_gfx,
                    &srcrect,
                    dst,
                    &dstrect);

	}
}
short gfxTilemapTileTypeAtXY(gfx_tilemap* tm, int x, int y) {
	unsigned int tilex = (x - (x % tm->tileset->tile_w)) / tm->tileset->tile_w
				,tiley = (y - (y % tm->tileset->tile_h)) / tm->tileset->tile_h;
	return tm->tiles[tilex + tiley * tm->w].index;
}

/* Based on the explanation provided by this fine gentleman from
http://stackoverflow.com/questions/306316/determine-if
-two-rectangles-overlap-each-other							   */
inline bool gfxRectOverlap(SDL_Rect* r1, SDL_Rect* r2) {
	return((r1->x < (r2->w + r2->x))
		&& ((r1->w + r1->x) > r2->x)
		&& (r1->y < (r2->y + r2->h))
		&& ((r1->y + r1->h) > r2->y));
}
