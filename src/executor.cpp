#include "exec/executor.h"
#include "exec/functions.h"
#include "exec/parse.h"
#include "system/panic.h"
#include "system/tools.h"
#include "var/var.h"
#include "vmem/vmem.h"

using namespace std;

operand_type get_operand_type(string str) {
    if (is_num(str)) {
        return NUM;
    }
    if (is_var(str)) {
        return VAR;
    }
    if (is_mr(str)) {
        return MR;
    }
    if (is_block(str)) {
        return BLCK;
    }
    return NUL;
}

// 逐行解释块内代码
void execute_block(string name) {
#ifdef ECHO_BLOCK_NAME
    cout << name << endl;
#endif
    block_node block = get_block(name);
    while (1) {
        string op;
        block >> op;
        if (op == "ret") {
            return;
        } else if (op == "exit") {
            exit(0);
        } else if (op == "call") {
            string name;
            block >> name;
            if (is_block(name)) {
                execute_block(name);
            } else {
                panic("no such block named " + name + ".");
            }
        } else if (op == "rez") {
            string op0s;
            block >> op0s;
            if (get_operand_type(op0s) == VAR) {
                var_node var0 = parse_var(op0s);
                u32 num0 = 0;
                u32 size = min(var0.size, (u32)sizeof(num0));
                vmem_copy_out(var0.addr, size, &num0);
                // cout << num0 << endl;
                if (num0 == 0) {
                    return;
                }
            } else {
                panic(op0s + " is not a variable");
            }
        } else if (op == "mov") {
            string sizes, op0s, op1s;
            block >> sizes >> op0s >> op1s;
            func_mov(sizes, op0s, op1s);
        } else if (op == "var") {
            string sizes, op0s, op1s;
            block >> sizes >> op0s >> op1s;
            func_var(sizes, op0s, op1s);
        } else if (op == "del") {
            string op0s;
            block >> op0s;
            func_del(op0s);
        } else if (op == "add") {
            string sizes, op0s, op1s;
            block >> sizes >> op0s >> op1s;
            func_add(sizes, op0s, op1s);
        } else if (op == "sub") {
            string sizes, op0s, op1s;
            block >> sizes >> op0s >> op1s;
            func_sub(sizes, op0s, op1s);
        } else if (op == "push") {
            string op0s;
            block >> op0s;
            func_push(op0s);
        } else if (op == "pop") {
            string op0s;
            block >> op0s;
            func_pop(op0s);
        } else if (op == "addr") {
            string op0s, op1s;
            block >> op0s >> op1s;
            func_addr(op0s, op1s);
        } else if (op == "size") {
            string op0s, op1s;
            block >> op0s >> op1s;
            func_size(op0s, op1s);
        } else if (op == "mul") {
            string sizes, op0s, op1s;
            block >> sizes >> op0s >> op1s;
            func_mul(sizes, op0s, op1s);
        } else if (op == "div") {
            string sizes, op0s, op1s;
            block >> sizes >> op0s >> op1s;
            func_div(sizes, op0s, op1s);
        } else if (op == "pchar") {
            string op0s;
            block >> op0s;
            func_pchar(op0s);
        } else if (op == "pint") {
            string op0s;
            block >> op0s;
            func_pint(op0s);
        } else {
            panic("sntyx error near " + op);
        }
    }
}

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
