#include "exec/executor.h"
#include "exec/functions.h"
#include <fstream>

using namespace std;

void func_include(string op0s) {
    // 解析文件流
    ifstream ifs;
    ifs.open(op0s);
    if (ifs.good()) {
        parse_stream(ifs);
    } else {
        panic("could not read from file " + op0s);
    }
}