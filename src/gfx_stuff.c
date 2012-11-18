#include "gfx_stuff.h"

//TODO: png support
SDL_Surface* gfxLoadFile(char* path) {
    SDL_Surface* surf =  SDL_LoadBMP(path);
    SDL_SetColorKey(surf, SDL_SRCCOLORKEY | SDL_RLEACCEL,
                          SDL_MapRGB(surf->format,255,0,255));
    return surf;
}
