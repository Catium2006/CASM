#ifndef __PANIC_H__
#define __PANIC_H__

#include <stdlib.h>
#include <iostream>

using namespace std;

void panic(string msg);

void warn(string msg);

void error(string msg);


#endif