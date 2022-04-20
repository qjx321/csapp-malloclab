#include<stdio.h>
#include"../mymalloc.h"

int main()
{
    heap_init();
    printf("origin heap:\n");
    printf("pstart: %p\npend: %p\nheap_size: %ld\n", pstart, pend, pend-pstart);
    
    printf("\nadd 10 bytes:\n");
    mysbrk(10);
    printf("pstart: %p\npend: %p\nheap_size: %ld\n", pstart, pend, pend-pstart);

    printf("\nsub 5 bytes\n");
    mysbrk(-5);
    printf("pstart: %p\npend: %p\nheap_size: %ld\n", pstart, pend, pend-pstart);

    return 0;
}