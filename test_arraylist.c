#include "arraylist.h"

#define NOT_FOUND -1

#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    ArrayList numbers;
    arraylist_init(&numbers);

    for (int i = 0; i < 100000; ++i) {
        arraylist_push_back(&numbers, i);
    }

    int num = arraylist_bsearch(&numbers, 255);

    if (num == NOT_FOUND)
        printf("no\n");
    else
        printf("yes\n");
    
    
    
    arraylist_del(&numbers);

    return 0;
}