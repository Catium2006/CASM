#include "exec/macro.h"

using namespace std;

unordered_map<string, string> definition_map;

void func_define(string op0s, string op1s) {
    definition_map[op0s] = op1s;
}

void func_undef(string op0s) {
    definition_map.erase(op0s);
}

bool is_defined(string op0s) {
    return definition_map.count(op0s) > 0;
}

string get_definition(string op0s) {
    return definition_map[op0s];
}