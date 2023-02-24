#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CPU {
    private:
        void lw();
        void sw();
        void add(uint8_t rs, uint8_t rt, uint8_t rd);
        void addi(uint8_t rs, uint8_t rt, int16_t immed);
        // andr because and is already a keyword in C++
        void andr(uint8_t rs, uint8_t rt, uint8_t rd);
        void andi(uint8_t rs, uint8_t rt, int16_t immed);
        // orr because or is already a keyword
        void orr(uint8_t rs, uint8_t rt, uint8_t rd);
        void ori(uint8_t rs, uint8_t rt, int16_t immed);
        void nor(uint8_t rs, uint8_t rt, uint8_t rd);
        void sll(uint8_t rt, uint8_t rd, uint8_t shamt);
        void beq(uint8_t rs, uint8_t rt, int16_t immed);
        void j(uint32_t address);

    public:
        int fetch(int pc);
        int exec(int instruction);

};



uint32_t parseUint32(string inpt) {
    uint32_t retVal = 0;
    for (int i = 0; i < inpt.length(); i++) {
        retVal *= 10;
        retVal += (int(inpt[i]) - 0x33) % 10;
    }

    return retVal;
}

int main() {
    uint32_t pc = 0;
    uint32_t registers[32] = {0};

    // Get the instructions from user input and store them into a vector
    vector<uint32_t> instructions;
    string inptInstr = "0";
    do {
        cout << "Enter the instruction as an uint32_t: ";
        cin >> inptInstr;
        instructions.push_back(parseUint32(inptInstr));

    } while(inptInstr != "quit");

    for (uint32_t instr : instructions) {
        cout << instr << endl;
    }
}