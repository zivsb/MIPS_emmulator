#include <iostream>
#include "cpu.h"

using namespace std;


CPU::CPU(uint32_t* instruction, uint32_t* staticMem, uint32_t* pc) {
            this->instruction = instruction;
            this->staticMem = staticMem;
            this->pc = pc;        
}

void handleInvalid(int instruction){
    cout << "Invalid instruction: " << instruction << endl;
}

int CPU::exec(uint32_t instruction) {
    uint8_t opcode = (instruction & 0xFC000000) >> 26;
    uint8_t rs = (instruction & 0x03E00000) >> 21;
    uint8_t rt = (instruction & 0x001F0000) >> 16;
    uint8_t rd = (instruction & 0x0000F800) >> 11;
    uint8_t shamt = (instruction & 0x000007C0) >> 6;
    uint8_t func = (instruction & 0x0000003F);
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
            switch (func) {
                case 0x20:
                    add(rs, rt, rd);
                    break;
                case 0x24:
                    andr(rs, rt, rd);
                    break;
                case 0x25:
                    orr(rs, rt, rd);
                    break;
                case 0x27:
                    nor(rs, rt, rd);
                    break;
                case 0x00:
                    sll(rt, rd, shamt);
                    break;
                default:
                    handleInvalid(instruction);
            }
            break;
        default:
            handleInvalid(instruction);
        
        
    }

    cout << "Executed: " << (instruction)  << endl;
    return 0;
}

// I-type instructions
uint32_t CPU::fetch(int pc) {
    return this->instruction[pc];
}

void CPU::lw(uint8_t rs, uint8_t rt, uint16_t immed) {
    regs[rt] = staticMem[immed + regs[rs]];
    // cout << "The value of regs[" << (int) rt << "] is now " << regs[rt] << endl;
}

void CPU::sw(uint8_t rs, uint8_t rt, uint16_t immed) {
    staticMem[immed + regs[rs]] = regs[rt];
    // cout << "staticMem[" << immed + regs[rs] << "] is now: " << staticMem[immed + regs[rs]] << endl;
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

// R-type instructions
void CPU::add(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd) {
    // Adding syscall to functionallity if all are zero
    regs[rd] = regs[rs] + regs[rt];
}

void CPU::andr(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd) {
    regs[rd] = regs[rs] & regs[rt];
}

void CPU::orr(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd) {
    regs[rd] = regs[rs] | regs[rt];
}

void CPU::nor(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd) {
    regs[rd] = (regs[rs] ^ 0xFFFFFFFF) & (regs[rt] ^ 0xFFFFFFFF);
}

void CPU::sll(std::uint8_t rt, std::uint8_t rd, std::uint8_t shamt) {
    if (shamt == 0 && rt == 0 && rd == 0) return syscall();
    regs[rd] = regs[rt] >> shamt;
}

// theoretically should actually be part of os, not CPU
void CPU::syscall() {
    switch (regs[2]) {
        case 1:
            // print as int
            cout << (int) regs[4] << endl;
            break;
        case 4:
            // a0 used as memory tracker
            // v0 used as register to store the ascii value
            do {
                // load the value at a0 into v0
                lw(4, 2, 0);
                //  print the value of a0
                cout << (char) regs[2];
                // increment a0
                addi(4, 4, 1);
            } while (regs[2] != 0); // print chars until the null character
    }
}