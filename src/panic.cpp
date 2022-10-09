#include "system/panic.h"
#include "vmem/vmem.h"
using namespace std;

void panic(string msg) {
    cout << endl << "[panic]: " << msg << endl;
#ifdef DUMP_VMEM_AFTER_PANIC
    save_vmem("./vmem.bin");
#endif

#ifndef NO_EXIT_AFTER_PANIC
    exit(-1);
#endif
}

void warn(string msg) {
    cout << endl << "[warn]: " << msg << endl;
}

void error(string msg) {
    cerr << endl << "[error]: " << msg << endl;
#ifndef NO_EXIT_AFTER_ERROR
    exit(-1);
#endif
}