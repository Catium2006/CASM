#include "exec/executor.h"
#include "exec/parse.h"
#include "system/panic.h"
#include "system/tools.h"
#include "exec/functions.h"

bool parse_stream(istream& istr) {
    if (istr.bad()) {
        return false;
    }
    while (1) {
        string str;
        if (!(istr >> str)) {
            break;
        }
        if (str[0] == '#') {
            getline(istr, str);
            continue;
        }
        if (str == "block") {
            string name;
            if (!(istr >> name)) {
                panic("some block have no name.");
                return false;
            }
            vector<string> codes;
            while (1) {
                if (!(istr >> str)) {
                    panic("block reaches the end of file but no endblock found.");
                    return false;
                }
                if (str[0] == '#') {
                    getline(istr, str);
                    continue;
                }
                // endblock为结束标志
                if (str == "endblock") {
                    break;
                }
                codes.push_back(str);
            }
            new_block(name, codes);
        }
        if (str == "include") {
            string op0s;
            if (!(istr >> op0s)) {
                panic("filename is undefined.");
            }
            func_include(op0s);
        }
    }

    // cout << "stream ends." << endl;
    return true;
}
