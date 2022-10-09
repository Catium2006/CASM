#include "exec/functions.h"

#include "var/var.h"
#include "vmem/vmem.h"

void func_push(string op0s) {
    if (get_operand_type(op0s) == VAR) {
        var_node var = parse_var(op0s);
        push(vmem + var.addr, var.size);
    } else {
        panic(op0s + " is not a variable.");
    }
}

void func_pop(string op0s) {
    if (get_operand_type(op0s) == VAR) {
        var_node var = parse_var(op0s);
        pop(vmem + var.addr, var.size);
    } else {
        panic(op0s + " is not a variable.");
    }
}
