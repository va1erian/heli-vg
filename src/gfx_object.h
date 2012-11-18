#include "main.h"

#ifndef GFXOBJECT_H_INCLUDED
#define GFXOBJECT_H_INCLUDED

#define GFXANIM_ENDLESSLOOP 0
#define GFXANIM_NOLOOP     -1
#define DEFAULT_ANIM_DURATION (10+ (rand() % 500))
/* sprite-ish object with animation support*/
typedef struct _gfx_frminfo {
    short        duration; //frame duration in millisecond
    short        x_offset, y_offset;
} gfx_frminfo;

// this is a read-only structure
typedef struct _gfx_anim {
    unsigned int frame_count;
    int          loop_count; //0 for infinite, -1 or less for no loop
    SDL_Rect     frame_size;
    gfx_frminfo* frm_info;//per frame info
    SDL_Surface* frames;
} gfx_anim;

typedef struct _gfx_object {
    SDL_Rect     bbox;//x and y are the object pos.
                       //also used as the bounding box
    int          hs_x, hs_y; //Hotspot coordinates
    bool         visible;
    unsigned int animation_count;
    float        anim_speed;
    gfx_anim*    animations;
    //Private fields
    SDL_Rect     anim_cliprect;
    unsigned int current_anim;
    unsigned int current_frame;
    int          duration_timer;
    unsigned int loop_counter;

} gfx_spr;

gfx_frminfo* gfxFrameinfoCreate(int duration,
                             int x_offset, int y_offset);

gfx_anim* gfxAnimCreate(gfx_frminfo* frm_info,
                      unsigned int frame_count,
                      unsigned int loop_count,
                      SDL_Surface* frames,
                      SDL_Rect     frame_size);

gfx_spr* gfxSpriteCreate(SDL_Rect  bbox,
                       bool visible,
                       gfx_anim* animations,
                       unsigned int animation_count);


inline void gfxSpriteDraw(gfx_spr* g, int x, int y, SDL_Surface* surf);

void gfxSpriteUpdate(gfx_spr* g, float time);

#endif // GFXOBJECT_H_INCLUDED
