#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include "exec/executor.h"
#include "exec/parse.h"
#include "system/panic.h"
#include "system/tools.h"
#include "type.h"

void func_mov(string sizes, string op0s, string op1s);

void func_var(string sizes, string op0s, string op1s);

void func_del(string op0s);

void func_add(string sizes, string op0s, string op1s);

void func_sub(string sizes, string op0s, string op1s);

void func_push(string op0s);

void func_pop(string op0s);

void func_addr(string op0s, string op1s);

void func_size(string op0s, string op1s);

void func_mul(string sizes, string op0s, string op1s);

void func_div(string sizes, string op0s, string op1s);

void func_pchar(string op0s);

void func_pint(string op0s);

void func_include(string op0s);

#endif