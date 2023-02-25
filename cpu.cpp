#include <iostream>
#include "cpu.h"

using namespace std;

int CPU::exec(int instruction) {
    cout << "Executing: " << instruction << endl;
    return 0;
}

int CPU::fetch(int pc) {
    return this->instruction0[pc];
}