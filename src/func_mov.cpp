#include "exec/functions.h"
#include "var/var.h"
#include "vmem/vmem.h"
//传入操作数字节数,操作数0,操作数1
void func_mov(string sizes, string op0s, string op1s) {
    if (get_operand_type(sizes) != NUM) {
        panic(sizes + " is not a size.");
        return;
    }
    u32 size = parse_int(sizes);
    if (get_operand_type(op0s) == NUM) {
        panic(op0s + " is a constant.");
        return;
    }
    bool is0m = 0;
    bool is1m = 0;
    bool is0v = 0;
    bool is1v = 0;
    // bool is0n = 0;
    bool is1n = 0;
    if (get_operand_type(op1s) == NUM) {
        is1n = 1;
    }
    if (get_operand_type(op0s) == VAR) {
        is0v = 1;
    }
    if (get_operand_type(op1s) == VAR) {
        is1v = 1;
    }
    if (get_operand_type(op0s) == MR) {
        is0m = 1;
    }
    if (get_operand_type(op1s) == MR) {
        is1m = 1;
    }
    if (is0v && is1n) {
        var_node var0 = parse_var(op0s);
        u32 num = parse_num(op1s);
        size = min(size, var0.size);
        size = min(size, (u32)sizeof(num));
        vmem_copy_in(var0.addr, size, &num);
    } else if (is0v && is1v) {
        var_node var0 = parse_var(op0s);
        var_node var1 = parse_var(op1s);
        size = min(size, min(var0.size, var1.size));
        vmem_copy(var1.addr, size, var0.addr);
    } else if (is0m && is1m) {
        u32 addr0 = parse_mr(op0s);
        u32 addr1 = parse_mr(op1s);
        vmem_copy(addr1, size, addr0);
    } else if (is0m && is1v) {
        u32 addr0 = parse_mr(op0s);
        var_node var1 = parse_var(op1s);
        size = min(size, var1.size);
        vmem_copy(var1.addr, size, addr0);
    } else if (is0v && is1m) {
        u32 addr1 = parse_mr(op1s);
        var_node var0 = parse_var(op0s);
        size = min(size, var0.size);
        vmem_copy(addr1, size, var0.addr);
    } else if (is0m && is1n) {
        u32 addr0 = parse_mr(op0s);
        u32 num = parse_num(op1s);
        size = min(size, (u32)sizeof(num));
        vmem_copy_in(addr0, size, &num);
    } else {
        panic("sntyx error. check your oprand: " + op0s + " " + op1s);
    }
}