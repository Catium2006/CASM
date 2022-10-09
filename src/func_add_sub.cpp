#include "exec/functions.h"
#include "var/var.h"
#include "vmem/vmem.h"
// 参数0只能是变量 参数1只能是变量或立即数
void func_add(string sizes, string op0s, string op1s) {
    if (get_operand_type(sizes) != NUM) {
        panic(sizes + " is not a size.");
        return;
    }
    u32 size = parse_int(sizes);
    if (get_operand_type(op0s) == NUM) {
        panic(op0s + " is a constant.");
        return;
    }
    bool is0v = 0;
    bool is1v = 0;
    // bool is0n = 0;
    bool is1n = 0;
    if (get_operand_type(op0s) == VAR) {
        is0v = 1;
    }
    if (get_operand_type(op1s) == NUM) {
        is1n = 1;
    }
    if (get_operand_type(op1s) == VAR) {
        is1v = 1;
    }
    if (is0v && is1n) {
        var_node var0 = parse_var(op0s);
        u32 num0 = 0;
        size = min(size, var0.size);
        size = min(size, (u32)sizeof(num0));
        vmem_copy_out(var0.addr, size, &num0);
        u32 num1 = parse_num(op1s);
        num0 += num1;
        vmem_copy_in(var0.addr, size, &num0);
    } else if (is0v && is1v) {
        var_node var0 = parse_var(op0s);
        var_node var1 = parse_var(op1s);
        u32 num0 = 0;
        u32 num1 = 0;
        size = min(size, var0.size);
        size = min(size, (u32)sizeof(num0));
        vmem_copy_out(var0.addr, size, &num0);
        vmem_copy_out(var1.addr, size, &num1);
        num0 += num1;
        vmem_copy_in(var0.addr, size, &num0);
    } else {
        panic("sntyx error. check your oprand: " + op0s + " " + op1s);
    }
}

//传入操作数字节数,操作数0,操作数1
void func_sub(string sizes, string op0s, string op1s) {
    if (get_operand_type(sizes) != NUM) {
        panic(sizes + " is not a size.");
        return;
    }
    u32 size = parse_int(sizes);
    if (get_operand_type(op0s) == NUM) {
        panic(op0s + " is a constant.");
        return;
    }
    bool is0v = 0;
    bool is1v = 0;
    // bool is0n = 0;
    bool is1n = 0;
    if (get_operand_type(op0s) == VAR) {
        is0v = 1;
    }
    if (get_operand_type(op1s) == NUM) {
        is1n = 1;
    }
    if (get_operand_type(op1s) == VAR) {
        is1v = 1;
    }
    if (is0v && is1n) {
        var_node var0 = parse_var(op0s);
        u32 num0 = 0;
        size = min(size, var0.size);
        size = min(size, (u32)sizeof(num0));
        vmem_copy_out(var0.addr, size, &num0);
        u32 num1 = parse_num(op1s);
        num0 -= num1;
        vmem_copy_in(var0.addr, size, &num0);
    } else if (is0v && is1v) {
        var_node var0 = parse_var(op0s);
        var_node var1 = parse_var(op1s);
        u32 num0 = 0;
        u32 num1 = 0;
        size = min(size, var0.size);
        size = min(size, (u32)sizeof(num0));
        vmem_copy_out(var0.addr, size, &num0);
        vmem_copy_out(var1.addr, size, &num1);
        num0 -= num1;
        vmem_copy_in(var0.addr, size, &num0);
    } else {
        panic("sntyx error. check your oprand: " + op0s + " " + op1s);
    }
}