#include "gfx_object.h"

gfx_frminfo* gfxFrameinfoCreate(int duration,
                            int x_offset, int y_offset) {
    gfx_frminfo* info   = malloc(sizeof(gfx_frminfo));
    assert(info);
    info->duration      = duration;
    info->x_offset      = x_offset;
    info->y_offset      = y_offset;
    return info;
}

gfx_anim* gfxAnimCreate(gfx_frminfo* frm_info,
                      unsigned int frame_count,
                      unsigned int loop_count,
                      SDL_Surface* frames,
                      SDL_Rect     frame_size) {
    gfx_anim* a   = malloc(sizeof(gfx_anim));
    assert(a);
    a->frames     = frames;
    a->frame_count= frame_count;
    a->loop_count = loop_count;
    if(frm_info == NULL) {
        gfx_frminfo* frm  = gfxFrameinfoCreate(DEFAULT_ANIM_DURATION,
                                    0, 0);
        gfx_frminfo* frms = calloc(a->frame_count,sizeof(gfx_frminfo));
        int i;
        for(i = 0; i < a->frame_count;i++)
            frms[i] = *frm;
        a->frm_info = frms;
    } else
        a->frm_info   = frm_info;
    a->frame_size = frame_size;
    return a;
}

gfx_spr* gfxSpriteCreate(SDL_Rect  bbox,
                       bool visible,
                       gfx_anim* animations,
                       unsigned int animation_count) {
    gfx_spr* g       = malloc(sizeof(gfx_spr));
    assert(g);
    g->bbox             = bbox;
    g->visible          = visible;
    g->animations       = animations;
    g->animation_count  = animation_count;
    g->anim_speed       = 1.0f;
    g->current_anim     = 0;
    g->anim_cliprect    = g->animations[g->current_anim].frame_size;
    g->current_frame    = 0;
    g->duration_timer   = 0;
    g->loop_counter     = 0;
    g->hs_x             = 0;
    g->hs_y             = 0;
    return g;
}

inline void gfxSpriteDraw(gfx_spr* g, int x, int y, SDL_Surface* surf) {
    SDL_Rect dstrect = {x, y, 0, 0};
    SDL_BlitSurface(g->animations[g->current_anim].frames,
                    &(g->anim_cliprect),
                    surf,
                    &dstrect);
}

void gfxSpriteUpdate(gfx_spr* g, float tdelta) {
    float real_speed;

    if(g->anim_speed != 0) {
     g->duration_timer += (tdelta * 1000.0f);
     real_speed = (g->animations[g->current_anim].frm_info
                          [g->current_frame].duration * g->anim_speed);
        if( g->duration_timer >= (int)real_speed){
            g->current_frame++;
            g->duration_timer = 0;
            if(g->current_frame >= g->animations[g->current_anim].frame_count)
                g->current_frame = 0;
            g->anim_cliprect.x = (g->animations[g->current_anim].frame_size.w) *
                                      g->current_frame;
        }
    }
}


/*void gfxobj_arrayupdate(dyn_array* array, unsigned int time) {
    int i;
    for(i = 0; i < array->count; i++) {
        gfxObjectUpdate(array->data[i], time);
    }
}
*/
