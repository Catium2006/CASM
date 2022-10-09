#include "exec/executor.h"
#include "exec/functions.h"
#include "exec/parse.h"
#include "var/var.h"
#include "vmem/vmem.h"
using namespace std;

void func_var(string sizes, string op0s, string op1s) {
    u32 size = 0;
    if (!is_int(sizes)) {
        panic(sizes + " is not a size.");
    }
    size = parse_int(sizes);
    //参数零不能是已有的变量,立即数,而且不能由内存地址初始化
    if (get_operand_type(op0s) == NUL) {
        if (get_operand_type(op1s) == NUM) {
            // 变量由立即数初始化
            u32 val = 0;
            if (is_int(op1s)) {
                val = parse_int(op1s);
            }
            if (is_hex(op1s)) {
                val = parse_hex(op1s);
            }
            void* p = &val;
            u32 addr = new_var(op0s, size);
            if (addr != -1) {
                if (size <= 4) {
                    vmem_copy_in(addr, size, p);
                } else {
                    u8 c = *(u8*)p;
                    vmem_fill(addr, size, c);
                }
            } else {
                panic("could not create variable " + op0s + ", vmem_alloc() failed");
            }
        } else if (get_operand_type(op1s) == VAR) {
            // 变量由变量初始化
            var_node var = parse_var(op1s);
            void* p = vmem + var.addr;
            u32 addr = new_var(op0s, size);
            if (addr != -1) {
                vmem_fill(addr, size, 0);
                size = min(size, var.size);
                vmem_copy_in(addr, size, p);
            } else {
                panic("could not create variable " + op0s + ", vmem_alloc() failed");
            }
        } else {
            // 不合法的声明
            panic("illegal variable value: " + op1s);
        }
    } else {
        panic(op0s + " can not be a variable here, it has been already used.");
    }
}

void func_del(string op0s) {
    if (is_var(op0s)) {
        del_var(op0s);
    } else {
        warn(op0s + " is not a variable.");
    }
}