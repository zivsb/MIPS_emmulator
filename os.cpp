#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "cpu.h"

using namespace std;



uint32_t parseUint32(string inpt) {
    uint32_t retVal = 0;
    int base = 10;
    bool isDec = true;

    if (int(inpt[1]) == 0x78) {
        isDec = false;
        base = 16;
    } else if (int(inpt[1]) == 0x62) {
        isDec = false;
        base = 2;
    }

    for (int i = isDec ? 0 : 2; i < inpt.length(); i++) {
        retVal *= base;
        retVal += (int(inpt[i]) - 0x30 < 10) ? (int(inpt[i]) - 0x30) : ((int(inpt[i]) - 0x41) + 10);
        // cout << inpt[i] << " converted to: " << ((int(inpt[i]) - 0x30 < 10) ? (int(inpt[i]) - 0x30) : ((int(inpt[i]) - 0x41) + 10)) << "\n";
    }

    return retVal;
}

int main(int argc, char* argv[]) {
    uint32_t instructions[100] = {0};
    // TODO implement Big Endian addressing
    uint32_t dynMem[16384] = {0};
    uint32_t pc = 0;
    CPU* processor = new CPU(instructions, dynMem, &pc);

    // Get the instructions from user input and store them into a vector
    string inptInstr;
    if (argc < 2) {
        // Get the input from a cin loop
        cerr << "No input file provided, resorting to manual instruction entry." << endl;
        do {
            cout << "Enter the instruction " << pc <<": ";
            cin >> inptInstr;
            instructions[pc] = parseUint32(inptInstr);
            pc++;

        } while(inptInstr != "quit");
    } else {
        // Get the input from the input text file
        ifstream file(argv[1]);
        if (!file.is_open()) {
            cerr << "Error: could not open file " << argv[1] << endl;
            return 1;
        }

        string line;
        getline(file, line);
        do {
            instructions[pc] = parseUint32(line);
            pc++;
        } while(getline(file, line));
        file.close();
    }
    pc = 0;
    
    // Run loop with exit codes handling
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