#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct block_node {
    string name;
    vector<string> codes;
    int idx = 0;
    string next_code() {
        string ret = codes[idx];
        idx++;
        // 注意 如果代码块没有显式的结束或返回语句 则将会持续循环
        if (idx >= codes.size()) {
            idx = 0;
        }
        return ret;
    }
    block_node& operator>>(string& str) {
        str = this->next_code();
        return *this;
    }
};

extern unordered_map<string, block_node> block_map;

bool is_block(string name);

block_node get_block(string name);

void new_block(string name, vector<string> codes);

#endif