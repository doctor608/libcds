#include "arraylist.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#define GROW_FACTOR 2
#define INIT_CAPACITY 4
#define NOT_FOUND -1

#define ASSERT_MEMORY_ALLOCATED(PTR) \
    assert((PTR) && "Memory allocation error");

#define ASSERT_INDEX_IS_VALID(AL, POS) \
    assert((POS) < (AL)->size && "Index out of bounds error")

#define ASSERT_NOT_EMPTY(AL) \
    assert(!arraylist_is_empty((AL)) && "ArrayList is empty");

static void arraylist_grow_buffer_by(ArrayList* al, size_t count);
static void arraylist_shrink_buffer_by(ArrayList* al, size_t count);

static void swap(int* a, int* b);

/* Constructor */
void arraylist_init(ArrayList* al)
{
    al->size = 0;
    al->capacity = INIT_CAPACITY;
    al->buffer_ptr = malloc(sizeof(int) * al->capacity);
    ASSERT_MEMORY_ALLOCATED(al->buffer_ptr);
}

/* Destructor */
void arraylist_del(ArrayList* al)
{
    free(al->buffer_ptr);
}

/* Getters */
size_t arraylist_size(const ArrayList* al) { return al->size; }

size_t arraylist_capacity(const ArrayList* al) { return al->capacity; }

/* States */
bool arraylist_is_empty(const ArrayList* al) { return al->size == 0; }

bool arraylist_is_full(const ArrayList* al) { return al->size == al->capacity; }

/* Index operator */
int arraylist_get(const ArrayList* al, size_t pos)
{
    return al->buffer_ptr[pos];
}

void arraylist_set(ArrayList* al, size_t pos, int val)
{
    al->buffer_ptr[pos] = val;
}

/* Methods */
void arraylist_push_back(ArrayList* al, int val)
{
    if (arraylist_is_full(al))
        arraylist_resize(al, al->capacity * GROW_FACTOR);
    
    al->buffer_ptr[al->size++] = val;
}

int arraylist_pop(ArrayList* al)
{
    ASSERT_NOT_EMPTY(al);
    return al->buffer_ptr[al->size--];
}

void arraylist_sort(ArrayList* al, bool ascend)
{
    if (al->size == 0 || al->size == 1) return;

    if (ascend) {
        for (size_t i = 0; i < al->size; ++i) {
            int min_index = i;
            for (size_t j = i + 1; j < al->size; ++j) {
                if (al->buffer_ptr[j] < al->buffer_ptr[min_index])
                    min_index = j;
            }
            swap(al->buffer_ptr + i, al->buffer_ptr + min_index);
        }
    } else {
        for (size_t i = 0; i < al->size; ++i) {
            int max_index = i;
            for (size_t j = i + 1; j < al->size; ++j) {
                if (al->buffer_ptr[j] > al->buffer_ptr[max_index])
                    max_index = j;
            }
            swap(al->buffer_ptr + i, al->buffer_ptr + max_index);
        }
    }
}

void arraylist_print(const ArrayList* al)
{
    if (arraylist_is_empty(al)) {
        puts("[]");
        return;
    }

    printf("[");
    for (size_t i = 0; i < al->size; ++i) {
        printf("%d", arraylist_get(al, i));
        if (i + 1 < al->size) printf(", ");
    }
    printf("]\n");
}

void arraylist_reverse(ArrayList* al)
{
    for (size_t i = 0; i < al->size / 2; ++i) {
        swap(al->buffer_ptr + i, al->buffer_ptr + al->size - i - 1);
    }
}

void arraylist_clear(ArrayList* al)
{
    if (arraylist_is_empty(al)) return;
    
    if (arraylist_size(al) <= INIT_CAPACITY) {
        al->size = 0;
        return;
    }

    al->size = 0;
    al->capacity = INIT_CAPACITY;
    al->buffer_ptr = (int*)realloc(al->buffer_ptr, sizeof(int) * INIT_CAPACITY);
    ASSERT_MEMORY_ALLOCATED(al->buffer_ptr);
}

void arraylist_resize(ArrayList* al, size_t count)
{
    if (al->capacity < count) {
        arraylist_grow_buffer_by(al, count - al->capacity);
    } else {
        arraylist_shrink_buffer_by(al, al->capacity - count);
    }
}

void arraylist_insert(ArrayList* al, size_t pos, int val)
{
    ASSERT_INDEX_IS_VALID(al, pos);

    if (arraylist_is_full(al))
        arraylist_resize(al, al->capacity * GROW_FACTOR);

    for (size_t i = al->size - 1; i >= pos; --i) {
        arraylist_set(al, i + 1, arraylist_get(al, i));
    } 

    arraylist_set(al, pos, val);
    ++al->size;
}

int arraylist_lsearch(ArrayList* al, int val)
{
    for (size_t i = 0; i < al->size; ++i) {
        if (arraylist_get(al, i) == val) {
            return i;
        }
    }
    return NOT_FOUND;
}

void arraylist_erase(ArrayList* al, size_t pos)
{
    ASSERT_INDEX_IS_VALID(al, pos);

    for(size_t i = pos; i < al->size - 1; ++i) {
        arraylist_set(al, i, arraylist_get(al, i + 1));
    }

    --al->size;
}
    
static void arraylist_grow_buffer_by(ArrayList* al, size_t count)
{
    al->capacity += count;
    al->buffer_ptr = (int*)realloc(al->buffer_ptr, al->capacity * sizeof(int));
    ASSERT_MEMORY_ALLOCATED(al->buffer_ptr);
}

static void arraylist_shrink_buffer_by(ArrayList* al, size_t count)
{
    al->capacity = al->capacity - count;
    al->size = (al->size > al->capacity) ? al->capacity : al->size;

    al->buffer_ptr = (int*)realloc(al->buffer_ptr, sizeof(int) * al->capacity);
    ASSERT_MEMORY_ALLOCATED(al->buffer_ptr);
}

static void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

ArrayList* arraylist_concat(ArrayList* dest, ArrayList* src)
{
    for (size_t i = 0; i < src->size; ++i)
        arraylist_push_back(dest, arraylist_get(src, i));
}

void arraylist_remove(ArrayList* al, int val)
{
    int pos = arraylist_lsearch(al, val);
    if (pos != NOT_FOUND)
        arraylist_erase(al, pos);
}

ArrayList* arraylist_shrink_to_fit(ArrayList* al)
{
    arraylist_resize(al, al->size);
    return al;
}