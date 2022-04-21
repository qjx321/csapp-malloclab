#include<stdio.h>
#include"../mymalloc.h"

int main()
{

    heap_init();
    int* a = (int*)mymalloc(sizeof(int));
    int* b = (int*)mymalloc(sizeof(int));
    int* c = (int*)mymalloc(sizeof(int));

    *a = 1;
    *b = 2;
    *c = 3; 

    myfree(a);
    myfree(b);
    myfree(c);

    printf("bin: %p\n", bin);

    printf("\nheap:\n");
    for (int i = 0; i < (ptop_chunk-pstart)/8; i++)
    {
        printf("%p %016lx\n", ((int64_t*)pstart)+i, *(((int64_t*)pstart)+i));
    }

    printf("\nbin:\n");

    intptr_t* pItem = bin;
    intptr_t fd = *(intptr_t*)pchunk2pdata(pItem);
    while(fd != 0)
    {
        printf("%p -> ", pItem);
        pItem = (intptr_t*)(fd);
        fd = *(intptr_t*)pchunk2pdata(pItem);
    }
    printf("%p\n", pItem);

    return 0;
}