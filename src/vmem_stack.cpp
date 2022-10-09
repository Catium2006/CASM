#include "vmem/vmem_stack.h"
#include "system/panic.h"
using namespace std;

u32 vmem_stack_top;

void push(void* p, u32 size) {
    if ((s64)((s64)vmem_stack_top - (s64)size) < (s64)(vmem_heap_top)) {
        panic("stack memory overflow! vmem_stack_size = " + to_string(vmem_stack_size) + "(+" + to_string(size) + ")");
    }
    //栈顶向下生长
    vmem_stack_top -= size;
    for (int i = 0; i < size; i++) {
        vmem[vmem_stack_top + i] = *(u8*)(p + i);
    }
}

void pop(void* p, u32 size) {
    if ((s64)((s64)vmem_stack_top + size) > (s64)(VMEM_SIZE)) {
        //空栈就不能pop了
        // warn("no enough content in stack.")
        return;
    }
    for (int i = 0; i < size; i++) {
        *(u8*)(p + i) = vmem[vmem_stack_top + i];
    }
    vmem_stack_top += size;
}
