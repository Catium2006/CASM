#include "casm.h"
#include <iostream>
using namespace std;
int main() {
    vmem_init();
    parse_stream(cin);
    if (is_block("main")) {
        execute_block("main");
    } else {
        warn("main block is not defined. no codes to execute.");
        return false;
    }
    return 0;
}

