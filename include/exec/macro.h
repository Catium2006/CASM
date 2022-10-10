#ifndef __MACRO_H__
#define __MACRO_H__

#include <system/panic.h>
#include <string>
#include <unordered_map>

using namespace std;

extern unordered_map<string, string> definition_map;

void func_define(string op0s, string op1s);

void func_undef(string op0s);

bool is_defined(string op0s);

string get_definition(string op0s);


#endif