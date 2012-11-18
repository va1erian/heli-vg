#include "act_testball.h"
#include <math.h>
act_obj* actTestballSpawn(linked_list* act_list, long x, long y) {
    SDL_Rect bbox  = {0,0,16,16};
    SDL_Rect arect = {0,0,16,16};
    gfx_anim* anim = gfxAnimCreate(NULL, 4, 0,
                                 gfxLoadFile("derp.bmp"),
                                 arect);
    gfx_spr* obj   = gfxSpriteCreate(bbox, true,
                                 anim, 1);

    act_obj* aobj  = ActorCreate(obj, (float)x, (float)y, NULL, TestballThinkProc);
    aobj->xvel = rand() % 300;
    aobj->yvel = -(rand() % 300);
    if((rand() % 100) > 50)
		aobj->xvel = -aobj->xvel;
    ListPushFront(act_list, aobj);
    return aobj;
}

void TestballThinkProc(act_obj* args, float tdelta) {
	args->yvel = (args->yvel) + (1200 * tdelta);
    return;
}
