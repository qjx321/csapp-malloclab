#include<stdio.h>
#include"mymalloc.h"

int main()
{
    heap_init();

    int* pchunk1 = (int*)mymalloc(sizeof(int));

    int* pchunk2 = (int*)mymalloc(sizeof(int));

    char* pchunk3 = (char*)mymalloc(sizeof(char) * 8);

    char* pchunk4 = (char*)mymalloc(sizeof(char) * 17);

    int* pchunk5 = (int*)mymalloc(sizeof(int) * 5);

    printf("patsrt: %p\n", pstart);

    printf("\nchunk1: %p\n", pchunk1);
    printf("chunk2: %p\n", pchunk2);
    printf("chunk3: %p\n", pchunk3);
    printf("chunk4: %p\n", pchunk4);
    printf("chunk4: %p\n", pchunk5);

    printf("\nheap:\n");
    for (int i = 0; i < (ptop_chunk-pstart)/8; i++)
    {
        printf("%p %016lx\n", ((int64_t*)pstart)+i, *(((int64_t*)pstart)+i));
    }

    return 0;
}