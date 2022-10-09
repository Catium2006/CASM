#include "vmem/vmem.h"
#include "system/panic.h"
#include <cstring>
#include <fstream>
#include <string>
using namespace std;

u8 vmem[VMEM_SIZE];

void vmem_init() {
    vmem_stack_top = VMEM_SIZE;
#ifdef VMEM_INIT_CLEAR
    memset(vmem, VMEM_INIT_CLEAR, sizeof(vmem));
#endif
}

void vmem_copy(u32 addr_from, u32 size, u32 addr_to) {
    for (u32 i = 0; i < size; i++) {
        // 或许可以改用memcpy?
        vmem[addr_to + i] = vmem[addr_from + i];
    }
}

void vmem_copy_in(u32 addr, u32 size, void* buf) {
    for (u32 i = 0; i < size; i++) {
        // 或许可以改用memcpy?
        vmem[addr + i] = ((u8*)buf)[i];
    }
}

void vmem_fill(u32 addr, u32 size, u8 byte) {
    for (u32 i = 0; i < size; i++) {
        // 填充,改用memset或许速度更快
        // vmem[addr + i] = byte;
        memset(vmem + i, byte, size);
    }
}

void vmem_copy_out(u32 addr, u32 size, void* buf) {
    for (u32 i = 0; i < size; i++) {
        ((u8*)buf)[i] = vmem[addr + i];
    }
}

void save_vmem(string filename) {
    ofstream ofs;
    // binary模式打开文件
    ofs.open(filename, ios::out | ios::binary);
    if (ofs.good()) {
        ofs.write((const char*)vmem, sizeof(vmem));
        ofs.flush();
    } else {
        error("could not write vmem to file " + filename);
    }
    ofs.close();
}

void load_vmem(string filename) {
    ifstream ifs;
    ifs.open(filename, ios::in | ios::binary);
    if (ifs.good()) {
        ifs.read((char*)vmem, sizeof(vmem));
    } else {
        error("could not load vmem from file " + filename);
    }
    ifs.close();
}