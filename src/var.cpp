#include "var/var.h"
#include "vmem/vmem_heap.h"

unordered_map<string, var_node> var_map;

bool is_var(string name) {
    return var_map.count(name) != 0;
}

var_node parse_var(string name) {
    return var_map[name];
}

u32 new_var(string name, u32 size) {
    if (var_map.count(name) != 0) {
        return -1;
    }
    u32 addr = vmem_alloc(size);
    if (addr == -1) {
        return -1;
    } else {
        var_map[name] = { addr, size };
        return addr;
    }
}

void del_var(string name) {
    if (var_map.count(name) != 0) {
        var_node nd = var_map[name];
        vmem_free(nd.addr, nd.size);
        var_map.erase(name);
    }
}