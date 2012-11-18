#include "main.h"

#ifndef GFXTILEMAP_H_INCLUDED
#define GFXTILEMAP_H_INCLUDED
#define GFX_ASCII_OFFSET 32

typedef struct _gfx_tile {
    unsigned short type;
    unsigned short index;
} gfx_tile;

typedef struct _gfx_tileset {
    unsigned short tile_w;
    unsigned short tile_h;
    unsigned int w; /*in tile dimensions*/
    unsigned int h;
    SDL_Surface* tileset_gfx;
} gfx_tileset;

typedef struct _gfx_tilemap {
    gfx_tile*    tiles;
    unsigned int w; /*In tile size */
    unsigned int h;
    unsigned int pw; /*in pixels*/
    unsigned int ph;
    SDL_Rect*    clip_rect;
    gfx_tileset* tileset;
} gfx_tilemap;

gfx_tileset* gfxTilesetCreate(SDL_Surface* surf,
                            unsigned short tile_w,
                            unsigned short tile_h);

/*inline void gfxtileset_drawtile(gfx_tileset* tileset,
                                unsigned int tile_index,
                                int x, int y,
                                SDL_Surface* dest);
*/

void gfxPuts(char* string, gfx_tileset* t, int x, int y, SDL_Surface* dest);

void gfxPrintFormatted(gfx_tileset* t, int x, int y,
				SDL_Surface* dest, char* format, ...);

gfx_tilemap* gfxTilemapCreateFromFile(char* path, int w,
                             int h);

void gfxTilemapTestDraw(gfx_tilemap* tm,SDL_Surface* dst, int xoff, int yoff);
void gfxTilemapClipDraw(gfx_tilemap* tm, SDL_Surface* dst, SDL_Rect clip, int x, int y);

void gfxTilemapDrawVStrip(gfx_tilemap* tm,SDL_Surface* dst, int stripx, int xoff,int yoff);

short gfxTilemapTileTypeAtXY(gfx_tilemap* tm, int x, int y);

inline bool gfxRectOverlap(SDL_Rect* r1, SDL_Rect* r2);

inline int gfxTextWidth(char* string, gfx_tileset* t);
#endif // GFXTILEMAP_H_INCLUDED
