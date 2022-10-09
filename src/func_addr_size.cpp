#include "exec/functions.h"
#include "var/var.h"
#include "vmem/vmem.h"

void func_addr(string op0s, string op1s) {
    if (is_var(op0s)) {
        if (is_var(op1s)) {
            var_node var0 = parse_var(op0s);
            var_node var1 = parse_var(op1s);
            u32 size = min(4u, var0.size);
            vmem_copy_in(var0.addr, size, &var1.addr);
        } else {
            panic(op1s + " is not a variable");
        }
    } else {
        panic(op0s + " is not a variable");
    }
}

void func_size(string op0s, string op1s) {
    if (is_var(op0s)) {
        if (is_var(op1s)) {
            var_node var0 = parse_var(op0s);
            var_node var1 = parse_var(op1s);
            u32 size = min(4u, var0.size);
            vmem_copy_in(var0.addr, size, &var1.size);
        } else {
            panic(op1s + " is not a variable");
        }
    } else {
        panic(op0s + " is not a variable");
    }
}