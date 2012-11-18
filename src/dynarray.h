//Variable length array of untyped pointer
//Public Domain
//2010 - Hadrien Bellahcene
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#ifndef VALARRAY_H_INCLUDED
#define VALARRAY_H_INCLUDED

#define DEFAULT_SIZE 8
#define SIZE_INCR    8

typedef struct _dyn_array {
    void** data;    //pointer to an array of pointer
    int    count;   //object count
    int    capacity;//array capacity
} dyn_array;

dyn_array* dyn_array_new(unsigned int initial_size);
void dyn_array_push(dyn_array* the_array, const void* data);
void* dyn_array_pop(dyn_array* the_array);
void dyn_array_insert(dyn_array* the_array, const void* data,unsigned int where);
void dyn_array_clear (int (*dtor)(void*));

#endif // VALARRAY_H_INCLUDED
