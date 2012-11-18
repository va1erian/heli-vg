#include "actor.h"

act_obj* ActorCreate(gfx_spr* view,
                    float x, float y,
                    void* fields,
                    ActorThinkProc cb) {
    act_obj* ao = (act_obj*)malloc(sizeof(act_obj));
    ao->view    = view;
    ao->x       = x;
    ao->y       = y;
    ao->xvel    = 0.0f; //in pixels per second
    ao->yvel    = 0.0f; //ditto
    ao->fields  = fields;
    ao->state   = ACT_SPAWNED;
    ao->fthink  = cb;
    return ao;
}

void ActorUpdate(act_obj* ao, float tdelta) {
    ao->fthink(ao, tdelta);
    if(ao->x + (ao->xvel * tdelta) < 0 || (ao->x + (ao->xvel * tdelta) >= 320 - 16))
		ao->xvel = -(ao->xvel);
    if(ao->y + (ao->yvel * tdelta) < 0 || (ao->y + (ao->yvel * tdelta) >= 240 - 16)) {
		ao->yvel = -(ao->yvel) * (0.9);
		ao->xvel = (ao->xvel) * (0.9);
    }
	ao->x += ao->xvel * tdelta;
	ao->y += ao->yvel * tdelta;
    gfxSpriteUpdate(ao->view, tdelta);
}

inline void ActorDraw(act_obj* ao, SDL_Surface* dst) {
    return gfxSpriteDraw(ao->view, ao->x, ao->y, dst);
}

void ActorUpdateList(linked_list* act_list, float tdelta) {
	list_node* i;
	act_obj*   ao;

	for(i = act_list->head; i != act_list->tail->next; i = i->next) {
		ao = (act_obj*)i->data;
		ActorUpdate(ao, tdelta);
	}
}

void ActorDrawList(linked_list* act_list, SDL_Surface* dst) {
	list_node* i;
	act_obj*   ao;
	gfx_spr*   go;
	for(i = act_list->head; i != act_list->tail->next; i = i->next) {
		ao = (act_obj*)i->data;
		go = (gfx_spr*)ao->view;
		ActorDraw(ao, dst);
	}
}

