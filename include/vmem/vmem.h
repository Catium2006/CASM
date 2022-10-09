#ifndef __VMEM_H__
#define __VMEM_H__
using namespace std;

#include "vmem/vmem_heap.h"
#include "vmem/vmem_stack.h"
#include <string>
/**
 * @brief 初始化堆栈
 *
 */
void vmem_init();

void vmem_copy(u32 addr_from, u32 size, u32 addr_to);

void vmem_copy_in(u32 addr, u32 size, void* buf);

void vmem_copy_out(u32 addr, u32 size, void* buf);

void vmem_fill(u32 addr, u32 size, u8 byte);

void save_vmem(string filename);

void load_vmem(string filename);
#endif
