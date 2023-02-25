#include <iostream>
#include "cpu.h"

using namespace std;


CPU::CPU(uint32_t* instruction, uint32_t* staticMem, uint32_t* pc) {
            this->instruction = instruction;
            this->staticMem = staticMem;
            this->pc = pc;        
}


int CPU::exec(uint32_t instruction) {
    uint8_t opcode = (instruction & 0xFC000000) >> 26;
    uint8_t rs = (instruction & 0x03E00000) >> 21;
    uint8_t rt = (instruction & 0x001F0000) >> 16;
    uint8_t rd = (instruction & 0x0000F800) >> 11;
    uint16_t immed = (instruction & 0x0000FFFF);
    uint32_t address = (instruction & 0x03FFFFFF);

    switch (opcode) {
        case 0x23:
        // lw
            lw(rs, rt, immed);
            break;
        case 0x2b:
        // sw
            sw(rs, rt, immed);
            break;
        case 0x8:
        // addi
            addi(rs, rt, immed);
            break;
        case 0xc:
        // andi
            andi(rs, rt, immed);
            break;
        case 0xd:
        // ori
            ori(rs, rt, immed);
            break;
        case 0x4:
        // beq
            beq(rs, rt, immed);
            break;
        case 0xf:
            lui(rs, rt, immed);
            break;
        case 0x2:
        // j
            // j(address);
            break;
        case 0x0:
        // R-Types
            break;
        
        
    }

    cout << "Executed: " << (instruction)  << endl;
    return 0;
}

// I-type instructions
uint32_t CPU::fetch(int pc) {
    return this->instruction[pc];
}

void CPU::lw(uint8_t rs, uint8_t rt, uint16_t immed) {
    regs[rt] = staticMem[immed + rs];
}

void CPU::sw(uint8_t rs, uint8_t rt, uint16_t immed) {
    staticMem[immed + rs] = regs[rt];
}

void CPU::addi(uint8_t rs, uint8_t rt, uint16_t immed) {
    regs[rt] = regs[rs] + immed;
}

void CPU::andi(uint8_t rs, uint8_t rt, uint16_t immed) {
    regs[rt] = regs[rs] & immed;
}

void CPU::ori(uint8_t rs, uint8_t rt, uint16_t immed) {
    regs[rt] = regs[rs] | immed;
}

void CPU::beq(uint8_t rs, uint8_t rt, uint16_t immed) {
    if(regs[rs] == regs[rt]) {
        *pc = immed;
    }
}

void CPU::lui(uint8_t rs, uint8_t rt, uint16_t immed) {
    // cout << "Loading " << immed << " into " << rt << endl;
    regs[rt] = immed;
    // cout << "regs[" << rt << "] is now: " << regs[rt] << endl;
}