#ifndef __VMEM_HEAP_H__
#define __VMEM_HEAP_H__
using namespace std;

#include "type.h"
#include "vmem/vmem_base.h"

// 每种空间最多回收这么多块的空闲内存
// 默认 1M 块
#ifndef VMEM_MAX_FREESPACE_BLOCK
#define VMEM_MAX_FREESPACE_BLOCK 1024 * 1024
#endif

/**
 * @brief 分配堆内存, 成功返回地址, 失败返回 -1
 *
 * @param size
 * @return u32 address
 */
u32 vmem_alloc(u32 size);

/**
 * @brief 释放堆内存
 *
 * @param addr
 * @param size
 */
void vmem_free(u32 addr, u32 size);

#endif