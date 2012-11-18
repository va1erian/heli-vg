#include "main.h"

#ifndef ACTTESTBALL_H_INCLUDED
#define ACTTESTBALL_H_INCLUDED

act_obj* actTestballSpawn(linked_list* act_list, long x, long y);

void TestballThinkProc(act_obj* args, float tdelta);

#endif // ACTTESTBALL_H_INCLUDED
