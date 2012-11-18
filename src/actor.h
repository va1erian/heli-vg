#include "main.h"

#ifndef ACTCOMMON_H_INCLUDED
#define ACTCOMMON_H_INCLUDED

typedef enum _std_state {
    ACT_SPAWNED   = 255,
    ACT_DESTROYED = 254,
} std_state;
//FIXME: Ugly hack
typedef struct _act_obj __act_obj;
typedef void (*ActorThinkProc)(__act_obj* args, float tdelta);
typedef int act_state;

typedef struct _act_obj {
    gfx_spr*      view;
    float         x, y;
    float         xvel, yvel;
    act_state     state;
    void*         fields;
    ActorThinkProc fthink;
} act_obj;


act_obj* ActorCreate(gfx_spr* view,
                    float x, float y,
                    void* fields,
                    ActorThinkProc cb);
void ActorUpdateList        (linked_list* act_list, float tdelta);
void ActorDrawList          (linked_list* act_list, SDL_Surface* dst);
void ActorUpdate     (act_obj* ao, float tdelta);
inline void ActorDraw       (act_obj* ao, SDL_Surface* dst);

#endif // ACTCOMMON_H_INCLUDED
