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
    pc = 0;
    
    // TODO: After full functionallity implemented reset program count to 0
    // Run the runtime loop until syscall w/ $v0 = 10 is called
    
    try {
        do {
            uint32_t instr = processor->fetch(pc);
            processor->exec(instr);
        } while(true);
        
    } catch (SuccessfulQuit s) {
        cout << "Code Executed successfully and ended with pc = " << pc << endl;
    } catch (Error e) {
        cout << "Unsecusseful Exececution error of type: ";
        switch(e.type) {
            case 0:
                cout << 0 << ". Unknown/specified error" << endl;
                break;
            case 1:
                cout << 1 << ". Invalid instruction. Instruction: " << processor->fetch(pc) << endl;
                break;
            case 2:
                cout << 2 << ". Memory out of bouds exception. Instruction: " << processor->fetch(pc) << endl;
                break;
        }
    }
}