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
    uint32_t staticMem[16384] = {0};
    uint32_t pc = 0;
    CPU* processor = new CPU(instructions, staticMem, &pc);
    uint32_t registers[32] = {0};

    // Get the instructions from user input and store them into a vector
    string inptInstr;
    do {
        cout << "Enter the instruction as an uint32_t: ";
        cin >> inptInstr;
        instructions[pc] = parseUint32(inptInstr);
        pc++;

    } while(inptInstr != "quit");
    
    // TODO: After full functionallity implemented reset program count to 0
    // Run the runtime loop until syscall w/ $v0 = 10 is called
    pc -= 2;
    for (int i = 0; i <= pc; i++) {
        uint32_t instr = instructions[i];
        processor->exec(processor->fetch(i));
    }

    pc = 0;
}