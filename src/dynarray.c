#include "dynarray.h"

dyn_array* dyn_array_new(unsigned int initial_capacity) {
    dyn_array* the_array;

    the_array = (dyn_array*)malloc(sizeof(dyn_array));
    assert(the_array);
    if(initial_capacity == 0) the_array->capacity = DEFAULT_SIZE;
        else the_array->capacity = initial_capacity;
    the_array->count = 0;
    the_array->data = calloc(the_array->capacity, sizeof(void*));
    assert(the_array->data);

    return the_array;
}

void dyn_array_push(dyn_array* the_array, const void* data) {
    if((the_array->count) >= the_array->capacity) {
        the_array->data = realloc(the_array->data,
                                  sizeof(void*) * (the_array->capacity + SIZE_INCR));
        assert(the_array->data);
        the_array->capacity += SIZE_INCR;
    }
    the_array->data[the_array->count] = (void*)data;
    the_array->count++;
}

void* dyn_array_pop(dyn_array* the_array) {
    void* the_data = the_array->data[the_array->count - 1];
    the_array->data[the_array->count - 1] = NULL;
    the_array->count--;
    return the_data;
}

void  dyn_array_insert(dyn_array* the_array, const void* data,unsigned int where) {
    if(where >= the_array->count) return dyn_array_push(the_array, data);
    if((the_array->count) >= the_array->capacity) {
        the_array->data = realloc(the_array->data,
                                  sizeof(void*) * (the_array->capacity + SIZE_INCR));
        assert(the_array->data);
        the_array->capacity += SIZE_INCR;
    }
    assert(memmove(the_array->data + (where + 1),
                   the_array->data + (where),
                   sizeof(void*) * (the_array->count - where)));
    the_array->data[where] = (void*)data;
    the_array->count++;
}


