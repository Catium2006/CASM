#ifndef __PARSE_H__
#define __PARSE_H__

#include <string>
#include <type.h>

using namespace std;

s64 parse_int(string str);

s64 parse_hex(string str);

s64 parse_num(string str);

bool is_num(string s);

bool is_hex(string str);

bool is_int(string s);

// memory reference
bool is_mr(string s);


u32 parse_mr(string str);

#endif