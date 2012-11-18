#include "linkedlist.h"

linked_list* ListCreate(void) {
    linked_list* the_list;

    the_list = (linked_list*)malloc(sizeof(linked_list));
    the_list->head = NULL;
    the_list->tail = NULL;
    the_list->count = 0;
    return the_list;
}

list_node* ListPushFront(linked_list* list, const void* data) {
    list_node* the_node;

    the_node = (list_node*)malloc(sizeof(list_node));
    the_node->next = NULL;
    the_node->prev = NULL;
    the_node->data = (void*)data;
    if( list->count == 0) {
        list->head  = the_node;
        list->tail  = the_node;
        list->count = 1;
    } else {
        list->head->prev = the_node;
        the_node->next = list->head;
        list->head = the_node;
        list->count++;
    }
    return the_node;
}

list_node* ListPushBack(linked_list* list, const void* data) {
    list_node* the_node;

    the_node = (list_node*)malloc(sizeof(list_node));
    the_node->next = NULL;
    the_node->prev = NULL;
    the_node->data = (void*)data;
    if( list->count == 0) {
        list->head = the_node;
        list->tail = the_node;
        list->count = 1;
    } else {
        list->tail->next = the_node;
        the_node->prev = list->tail;
        list->tail = the_node;
        list->count++;
    }
    return the_node;
}

list_node* ListInsert(linked_list* list, const void* data, list_node* prev_node) {
    list_node* new_node;

    if(prev_node == list->tail) return ListPushBack(list, data);

	new_node = (list_node*)malloc(sizeof(list_node));
	new_node->next = prev_node->next;
	new_node->next->prev = new_node;
	prev_node->next = new_node;
	new_node->prev  = prev_node;
    new_node->data = (void*)data;
    list->count++;
    return new_node;
}

void* ListPopFront(linked_list* list) {
    void* node_data;
    list_node* new_head;

    switch(list->count) {
        case 0: //empty list
            return NULL;
        case 1: // 1-node list
            node_data   = list->head->data;
            free((void*)list->head);
            list->head  = NULL;
            list->tail  = NULL;
            list->count = 0;
            return node_data;
        default:
            node_data = list->head->data;
            new_head  = list->head->next;
            free(list->head);
            list->head  = new_head;
            list->head->prev = NULL;
            list->count--;
            //return if there is only one node left
            if(list->head->next == NULL) return node_data;
            //update the prev pointer of the node next to the head
            list->head->next->prev = list->head;
            return node_data;
    }
}

void* ListPopBack(linked_list* list) {
    void* node_data;
    list_node* new_tail;

    switch(list->count) {
        case 0:
            return NULL;
        case 1:
            return ListPopFront(list); //how elegant
        default:
            node_data = list->tail->data;
            new_tail  = list->tail->prev;
            free(list->tail);
            list->tail  = new_tail;
            list->tail->next = NULL;
            list->count--;
            //same as above
            if(list->tail->prev == NULL) return node_data;
            //ditto
            list->tail->prev->next = list->tail;
            return node_data;
    }
}

int ListClear(linked_list* list, int (*dtor)(void*)) {
    while( list->count != 0) {
        dtor(list->head->data);
        ListPopFront(list);
    }
    return LNKL_SUCCESS;
}

void ListPrintStrings(const linked_list* list) {
    list_node* i;
    printf("%d item(s)\n", list->count);
    if(list->count == 0) return;
    printf("head: %s\ntail:%s\n", (char*)list->head->data, (char*)list->tail->data);
    for(i = list->head; i != list->tail->next; i = i->next)
        printf("%s\n", (char*)i->data);
}

void ListPrintStringsReverse(const linked_list* list) {
    list_node* i;
    printf("%d item(s)\n", list->count);
    if(list->count == 0) return;
    printf("head: %s\ntail:%s\n", (char*)list->head->data, (char*)list->tail->data);
    for(i = list->tail; i != list->head->prev; i = i->prev)
        printf("%s\n", (char*)i->data);
}

int DummyDestructor(void* data) {
	free(data);
    printf("%s deleted", (char*)data);
    return LNKL_SUCCESS;
}
