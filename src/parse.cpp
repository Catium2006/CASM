#include "exec/parse.h"
#include "system/panic.h"
#include "var/var.h"
#include "vmem/vmem.h"

using namespace std;

// 解析一个十进制整数
s64 parse_int(string str) {
    s64 ret = 0;
    s64 start = 0;
    bool f = 0;
    if (str[0] == '-') {
        f = 1;
        start = 1;
    }
    for (int i = start; i < str.size(); i++) {
        char c = str[i];
        ret *= 10;
        ret += c - '0';
    }
    return f ? -ret : ret;
}

// 解析一个十六进制整数
s64 parse_hex(string str) {
    s64 ret = 0;
    // 跳过 "0x"
    for (int i = 2; i < str.size(); i++) {
        char c = str[i];
        ret *= 16;
        if ('0' <= c && c <= '9') {
            ret += c - '0';
        } else if ('a' <= c && c <= 'f') {
            ret += c - 'a' + 10;
        }
    }
    return ret;
}

// 解析一个 数
s64 parse_num(string str) {
    if (is_int(str)) {
        return parse_int(str);
    }
    if (is_hex(str)) {
        return parse_hex(str);
    }
}

// 判断是不是十六进制数
bool is_hex(string str) {
    bool f0 = str.size() >= 3;
    bool f1 = (str[0] == '0' && str[1] == 'x');
    bool f2 = 1;
    for (int i = 2; i < str.size(); i++) {
        char c = str[i];
        if ('0' <= c && c <= '9') {
            continue;
        } else if ('a' <= c && c <= 'f') {
            continue;
        } else {
            f2 = 0;
            break;
        }
    }
    return f0 && f1 && f2;
}

// 判断是不是十进制数
bool is_int(string s) {
    if (s[0] == '-') {
        for (int i = 1; i < s.size(); i++) {
            if (!isdigit(s[i])) {
                return false;
            }
        }
    } else {
        for (int i = 0; i < s.size(); i++) {
            if (!isdigit(s[i])) {
                return false;
            }
        }
    }
    return true;
}

// 判断是不是 数
bool is_num(string s) {
    return is_int(s) || is_hex(s);
}

//[0x114514] [114514] [VAR] [REG]
bool is_mr(string str) {
    if (str.size() >= 3) {
        if (str[0] == '[' && str[str.size() - 1] == ']') {
            string s = str.substr(1, str.size() - 2);
            return is_num(s) || is_var(s);
        }
    }
    return false;
}

// 解析符合要求的内存[地址]
u32 parse_mr(string str) {
    string s = str.substr(1, str.size() - 2);
    u32 ret = 0;
    if (is_int(s)) {
        ret = parse_int(s);
    } else if (is_hex(s)) {
        ret = parse_hex(s);
    } else if (is_var(s)) {
        var_node var = parse_var(s);
        u32 val = 0;
        if (var.size > 4) {
            panic("too large variable for memory reference");
        }
        vmem_copy_out(var.addr, var.size, &val);
        ret = val;
    } else {
        panic("no such symbol: " + s);
    }
    if (ret >= VMEM_SIZE) {
        panic("invalid memory reference " + to_string(ret));
    }
    return ret;
}