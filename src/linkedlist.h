//A doubly-linked list
//Public domain
//2010, Hadrien Bellahcene

#include <stdlib.h>
#include <stdio.h>
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#define LNKL_SUCCESS    0
#define LNKL_MALLOCFAIL 1
#define LNKL_EMPTYLIST  2

typedef struct _list_node {
    struct _list_node* prev;
    void* data;
    struct _list_node* next;
} list_node;

typedef struct _linked_list {
    list_node* head;
    list_node* tail;
    int count;
} linked_list;

linked_list* ListCreate(void);
list_node*   ListPushFront(linked_list* list, const void* data);
list_node*   ListPushBack (linked_list* list, const void* data);
list_node*   ListInsert  (linked_list* list, const void* data, list_node* prev_node);
//this function will return the first node found containing the given pointer
list_node*   ListLookup  (linked_list* list, const void* data_ptr);
void* ListPopBack (linked_list* list);
void* ListPopFront(linked_list* list);
int   ListClear   (linked_list* list, int (*dtor)(void*));

void  ListPrintStrings(const linked_list* list);
void  ListPrintStringsReverse(const linked_list* list);

int   DummyDestructor(void* data);

#endif // LINKEDLIST_H_INCLUDED
