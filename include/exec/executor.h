#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__
using namespace std;

#include "exec/block.h"
#include <fstream>
#include <iostream>

enum operand_type { NUL, NUM, VAR, MR, BLCK };

operand_type get_operand_type(string str);

void execute_block(string name);

bool parse_stream(istream& istr);

#endif