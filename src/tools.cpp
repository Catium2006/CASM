#include "system/tools.h"
using namespace std;

int qpow(int base, u32 k) {
    int ret = 1;
    while (k) {
        if (k | 1) {
            ret = ret * base;
        }
        base = base * base;
        k >>= 1;
    }
    return ret;
}

u32 pow2(u32 k) {
    return 1 << k;
}

u32 log2(u32 k) {
    u32 ret = -1;
    while (k) {
        k >>= 1;
        ret++;
    }
    return ret;
}

u32 lowbit(u32 x) {
    return x & -x;
}

