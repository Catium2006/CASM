#include "exec/functions.h"
#include "var/var.h"
#include "vmem/vmem.h"

void func_pchar(string op0s) {
    if (is_var(op0s)) {
        var_node var0 = parse_var(op0s);
        char ch = 0;
        vmem_copy_out(var0.addr, 1, &ch);
        cout << ch;
    } else if (is_mr(op0s)) {
        u32 addr = parse_mr(op0s);
        char ch = 0;
        vmem_copy_out(addr, 1, &ch);
        cout << ch;
    } else if (is_num(op0s)) {
        char ch = parse_num(op0s);
        cout << ch;
    } else {
        panic("illegal oprand " + op0s);
    }
}

void func_pint(string op0s) {
    if (is_var(op0s)) {
        var_node var0 = parse_var(op0s);
        u32 size = min(4u, var0.size);
        if (size == 4 || size == 3) {
            s32 x = 0;
            vmem_copy_out(var0.addr, size, &x);
            cout << x;
        }
        if (size == 2) {
            s16 x = 0;
            vmem_copy_out(var0.addr, size, &x);
            cout << x;
        }
        if (size == 1) {
            s8 x = 0;
            vmem_copy_out(var0.addr, size, &x);
            cout << 0 + x;
        }
    } else if (is_num(op0s)) {
        int x = parse_num(op0s);
        cout << x;
    } else {
        panic("illegal oprand " + op0s);
    }
}
