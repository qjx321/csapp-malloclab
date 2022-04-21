#include<stdio.h>
#include"../mymalloc.h"

int main(void)
{
    heap_init();

    char* a = (char*)mymalloc(0xf); //0x20
    char* b = (char*)mymalloc(0x11); //0x30
    char* c = (char*)mymalloc(0x21); //0x40

    printf("a: %p\n", a);
    printf("b: %p\n", b);
    printf("c: %p\n", c);

    myfree(a);
    myfree(b);
    myfree(c);

    char* d = (char*)mymalloc(0x12); //0x30
    char* e = (char*)mymalloc(0x22); //0x40
    char* f = (char*)mymalloc(0x32); //0x50

    printf("d: %p\n", d);
    printf("e: %p\n", e);
    printf("f: %p\n", f);


    printf("\nheap:\n");
    for (int i = 0; i < (ptop_chunk-pstart)/8; i++)
    {
        printf("%p %016lx\n", ((int64_t*)pstart)+i, *(((int64_t*)pstart)+i));
    }

    return 0;
}