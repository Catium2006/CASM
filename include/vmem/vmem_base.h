#ifndef __VMEM_BASE_H__
#define __VMEM_BASE_H__
using namespace std;

#include "type.h"

// 默认定义128MB
#ifndef VMEM_SIZE
#define VMEM_SIZE 1024 * 1024 * 128
#endif

extern u8 vmem[VMEM_SIZE];

// 栈顶指针, 向下生长
// #define vmem_stack_top esp
extern u32 vmem_stack_top;

// 栈大小
#define vmem_stack_size (VMEM_SIZE - vmem_stack_top)

// 堆顶指针
extern u32 vmem_heap_top;

// 堆大小
#define vmem_heap_size (vmem_heap_top)


#endif