#ifndef __MYMALLOC__
#define __MYMALLOC__

#include<stdint.h>

#define MAX_MEM_SIZE 1000

//模拟的内存
uint8_t MEMORY[MAX_MEM_SIZE] = {0}; 

//指向heap的起始位置和结束位置+1
uint8_t *pstart, *pend;

//指向top_chunk的指针（即指向chunk的末尾）
uint8_t* ptop_chunk;

//chunk的数量
unsigned chunk_num = 0;

// typedef struct CHUNK
// {
//     intptr_t pchunk; //保存该chunk在内存中的起始地址，也就是pchunk
//     struct CHUNK* fd; //指向下一个CHUNK结构体
//     struct CHUNK* bk; //指向上一个CHUNK结构体
// }chunk_t, *pchunk_t;

//bin头指针
intptr_t* bin;

void* pdata2pchunk(void* pdata)
{
    return (void*)((uint8_t*)pdata-16);
}

void* pchunk2pdata(void* pchunk)
{
    return (void*)((uint8_t*)pchunk+16);
}

//P标志位
typedef enum p {free, inuse} P;

/*
 * 将size和P打包
 */
int64_t pack(int64_t size,  P statu)
{
    return size | statu;
}


/*
 * 初始化heap区域 
 */
void heap_init()
{
    pstart =  MEMORY;
    pend   = &MEMORY[4096];
    ptop_chunk = pstart;
}

/*
 * 模拟sbrk函数的行为
 */
void* mysbrk(int increment)
{
    void* pret = pend;
    pend += increment;
    return pret;
}


void* mymalloc(int64_t size)
{
    //不合法的size
    if (size <= 0)
    {
        return NULL;
    }
    //计算chunk的size
    int64_t chunk_size = (size + 16) + (size % 16 ? 16-(size%16) : 0);

    //在heap中布置chunk结构
    *((int64_t*)(ptop_chunk) + 1) = pack(chunk_size, inuse);

    //如果是第一个chunk
    if (chunk_num == 0)
    {
        *(int64_t*)ptop_chunk = 0;
    }
    chunk_num++;

    void* ret = (void*)(ptop_chunk + 16);
    ptop_chunk += chunk_size;
    return ret;
}

void myfree(void* pdata)
{
    //获取指向chunk头部的指针
    void* pchunk = pdata2pchunk(pdata);
    //将P标志位置为free
    *((int64_t*)pdata-1) &= ~0x1;
    
    if(bin == NULL) //如果bin中没有chunk
    {
        bin = (intptr_t*)pchunk;
        *(intptr_t*)pdata = 0;
    }
    else //bin中有chunk
    {
        *(intptr_t*)pdata = (intptr_t)bin; //将前一个bin保存到这一个chunk的fd字段
        bin = (intptr_t*)pchunk; //将这一个chunk的指针放入bin中
    } 
}

#endif