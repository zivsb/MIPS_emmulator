#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include "cpu.h"

using namespace std;



uint32_t parseUint32(string inpt) {
    uint32_t retVal = 0;
    for (int i = 0; i < inpt.length(); i++) {
        retVal *= 10;
        retVal += (int(inpt[i]) - 0x30) % 10;
    }

    return retVal;
}

int main() {
    uint32_t instructions[100] = {0};
    uint32_t pc = 0;
    CPU* processor = new CPU(instructions, &pc);
    uint32_t registers[32] = {0};

    // Get the instructions from user input and store them into a vector
    string inptInstr;
    do {
        cout << "Enter the instruction as an uint32_t: ";
        cin >> inptInstr;
        instructions[pc] = parseUint32(inptInstr);
        pc++;

    } while(inptInstr != "quit");
    
    pc -= 2;
    for (int i = 0; i <= pc; i++) {
        uint32_t instr = instructions[i];
        cout << "Fetched: " << processor->fetch(i) << endl;
    }

    pc = 0;
}