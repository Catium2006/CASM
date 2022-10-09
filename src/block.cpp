#include "exec/block.h"

unordered_map<string, block_node> block_map;

bool is_block(string name) {
    return block_map.count(name) > 0;
}

block_node get_block(string name) {
    block_node nd = block_map[name];
    nd.idx = 0;
    return nd;
}

void new_block(string name, vector<string> codes) {
    block_node nd = { name, codes, 0 };
    // 不检查是否已有对应标识符的代码块, 如果有的话直接覆盖
    block_map[name] = nd;
}