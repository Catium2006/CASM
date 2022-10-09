#include "casm.h"
#include <iostream>
using namespace std;
int main() {
    vmem_init();
    // 尝试解析标准输入流
    parse_stream(cin);
    if (is_block("main")) {
        execute_block("main");
    } else {
        warn("main block is never defined. no codes to execute.");
    }
    return 0;
}

