#include "vmem/vmem_heap.h"
#include "system/panic.h"
#include "system/tools.h"
using namespace std;

/*
    内存回收方案:
    分别记录2^0~2^16字节的空闲空间地址, 用类似栈的结构维护
    需要对应空间的时候去对应位置查表, 不能满足就堆顶分配
    需要分配连续内存的时候问题可能比较大
    那再大的就连续内存直接干到堆顶吧
*/

u32 vmem_heap_top;

u32 freeblock[16][VMEM_MAX_FREESPACE_BLOCK];
u32 freeblock_p[16];

u32 vmem_alloc_block(u8 k) {
    if (freeblock_p[k]) {
        u32 ret = freeblock[k][freeblock_p[k]];
        freeblock_p[k]--;
        return ret;
    }
    return -1;
}

inline u32 vmem_alloc_heap_top(u32 size) {
    if ((int64)((int64)vmem_heap_top + (int64)size) < (int64)vmem_stack_top) {
        vmem_heap_top += size;
        return vmem_heap_top - size;
    } else {
        // 堆顶和栈顶相交说明内存占满了
        panic("heap memory overflow! vmem_heap_size = " + to_string(vmem_heap_size) + "(+" + to_string(size) + ")");
        return -1;
    }
}

u32 vmem_alloc(u32 size) {
    int k = log2(size);
    if (__builtin_popcount(size) == 1 && k <= 15) {
        u32 f = vmem_alloc_block(k);
        if (f != -1) {
            return f;
        } else {
            return vmem_alloc_heap_top(size);
        }
    } else {
        return vmem_alloc_heap_top(size);
    }
}

void vmem_free_block(u32 addr, u32 size) {
    int k = log2(size);
    if (freeblock_p[k] + 1 < VMEM_MAX_FREESPACE_BLOCK) {
        freeblock_p[k]++;
    }
    freeblock[k][freeblock_p[k]] = addr;
}

void vmem_free(u32 addr, u32 size) {
    while (size) {
        u32 x = lowbit(size);
        size -= x;
        vmem_free_block(addr + size, x);
    }
}
