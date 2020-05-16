#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t size;
    size_t capacity;
    int* buffer_ptr;
} ArrayList;

void arraylist_init(ArrayList* al);

void arraylist_del(ArrayList* al);

/* Getters */
size_t arraylist_size(const ArrayList* al);

size_t arraylist_capacity(const ArrayList* al);

/* States */
bool arraylist_is_empty(const ArrayList* al);

bool arraylist_is_full(const ArrayList* al);

int arraylist_get(const ArrayList* al, size_t pos);

void arraylist_set(ArrayList* al, size_t pos, int val);

void arraylist_push_back(ArrayList* al, int val);

int arraylist_pop(ArrayList* al);

void arraylist_sort(ArrayList* al, bool ascend);

void arraylist_print(const ArrayList* al);

void arraylist_clear(ArrayList* al);

void arraylist_resize(ArrayList* al, size_t count);

void arraylist_reverse(ArrayList* al);

void arraylist_insert(ArrayList* al, size_t pos, int val);

void arraylist_erase(ArrayList* al, size_t pos);

ArrayList* arraylist_concat(ArrayList* dest, ArrayList* src);

ArrayList* arraylist_shrink_to_fit(ArrayList* al);

void arraylist_remove(ArrayList* al, int val);

int arraylist_lsearch(ArrayList* al, int val);

int arraylist_bsearch(ArrayList* al, int val);

bool arraylist_equals(const ArrayList* al1, const ArrayList* al2);

#endif /* ARRAY_LIST_H */