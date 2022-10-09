#ifndef __VAR_H__
#define __VAR_H__

#include "system/tools.h"
#include <string>
#include <unordered_map>

struct var_node {
    // string name;
    u32 addr;
    u32 size;
};

// 仅是一张表 不实际存储
extern unordered_map<string, var_node> var_map;

bool is_var(string name);

var_node parse_var(string name);

// 新建变量(在堆里) 成功返回地址 失败返回-1
u32 new_var(string name, u32 size);

void del_var(string name);

#endif