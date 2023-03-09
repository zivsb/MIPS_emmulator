#include <iostream>
#include "cpu.h"

using namespace std;


CPU::CPU(uint32_t* instruction, uint32_t* dynMem, uint32_t* pc) {
    this->instruction = instruction;
    this->dynMem = dynMem;
    this->pc = pc;
    // Setting sp to the top of the dynamic memory     
    regs[29] = 16383;  
}

const void handleInvalid(int instruction){
    cout << "Invalid instruction: " << instruction << endl;
}

int CPU::exec(uint32_t instruction) throw(SuccessfulQuit, Error) {
    uint8_t opcode = (instruction & 0xFC000000) >> 26;
    uint8_t rs = (instruction & 0x03E00000) >> 21;
    uint8_t rt = (instruction & 0x001F0000) >> 16;
    uint8_t rd = (instruction & 0x0000F800) >> 11;
    uint8_t shamt = (instruction & 0x000007C0) >> 6;
    uint8_t func = (instruction & 0x0000003F);
    uint16_t immed = (instruction & 0x0000FFFF);
    uint32_t address = (instruction & 0x03FFFFFF);

    cout << "Executing: " << (instruction)  << endl;
    
    try {

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
            case 0x5:
            // beq
                beq(rs, rt, immed);
                break;
            case 0xf:
                lui(rs, rt, immed);
                break;
            case 0x2:
                j(address);
                break;
            case 0x3:
                jal(address);
                break;
            case 0xA:
                slti(rs, rt, immed);
                break;
            case 0x0:
            // R-Types
                switch (func) {
                    case 0xC:
                        syscall();
                        break;
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
                    case 0x8:
                        jr(rs);
                        break;
                    case 0x2A:
                        slt(rs, rt, rd);
                        break;
                    default:
                        throw (Error(1));
                }
                break;
            default:
                throw (Error(1));
        }
    } catch (Error e) {
        throw e;
    } catch (SuccessfulQuit s) {
        throw s;
    }

    (*pc)++;
    return 0;
}

// I-type instructions
uint32_t CPU::fetch(int pc) {
    return this->instruction[pc];
}

void CPU::lw(uint8_t rs, uint8_t rt, uint16_t immed) {
    regs[rt] = dynMem[immed + regs[rs]];
    // cout << "The value of regs[" << (int) rt << "] is now " << regs[rt] << endl;
}

void CPU::sw(uint8_t rs, uint8_t rt, uint16_t immed) {
    dynMem[immed + regs[rs]] = regs[rt];
    // cout << "dynMem[" << immed + regs[rs] << "] is now: " << dynMem[immed + regs[rs]] << endl;
}

void CPU::addi(uint8_t rs, uint8_t rt, uint16_t immed) {
    cout << "In addi: " << regs[rt] << endl;
    regs[rt] = regs[rs] + immed;
}

void CPU::andi(uint8_t rs, uint8_t rt, uint16_t immed) {
    regs[rt] = regs[rs] & immed;
}

void CPU::ori(uint8_t rs, uint8_t rt, uint16_t immed) {
    regs[rt] = regs[rs] | immed;
}

void CPU::beq(uint8_t rs, uint8_t rt, uint16_t immed) {
    cout << "Running beq" << endl;
    cout << regs[rs] << " " << regs[rt] << endl;
    cout << *pc << endl;
    if(regs[rs] == regs[rt]) {
        *pc = immed;
        cout << "PC has been changed to " << *pc << endl;
    }
}

void CPU::bne(uint8_t rs, uint8_t rt, uint16_t immed) {
    if(regs[rs] != regs[rt]) {
        *pc = immed;
    }
}

void CPU::slti(std::uint8_t rs, std::uint8_t rt, std::uint16_t immed) {
    cout << "In SLTI: " << regs[rs] << " " << immed << " " << (regs[rs] < immed);
    regs[rt] = (regs[rs] < immed);
}

void CPU::slt(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd) {
    regs[rd] = (regs[rs] < regs[rt]);
}

void CPU::lui(uint8_t rs, uint8_t rt, uint16_t immed) {
    // cout << "Loading " << immed << " into " << rt << endl;
    regs[rt] = immed;
    // cout << "regs[" << rt << "] is now: " << regs[rt] << endl;
}

// R-type instructions
void CPU::add(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd) {
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
    regs[rd] = regs[rt] >> shamt;
}

void CPU::j(std::uint32_t address) {
    *(pc) = address;
}

void CPU::jal(std::uint32_t address) {
    regs[31] = *pc;
    *(pc) = address;
}

void CPU::jr(std::uint8_t rs) {
    *(pc) = regs[rs];
}


// theoretically should actually be part of os, not CPU
void CPU::syscall() throw(SuccessfulQuit, Error){
    switch (regs[2]) {
        case 1:
            // print as int
            cout << (int) regs[4] << endl;
            break;
        case 4:
            // a0 used as memory tracker
            // v0 used as register to store the ascii value
            do {
                // If a0 is outside of the memory limit throw memory oob error
                if (regs[4] >= 100) throw (Error(2));
                // load the value at a0 into v0
                lw(4, 2, 0);
                //  print the value of a0
                cout << (char) regs[2];
                // increment a0
                addi(4, 4, 1);
            } while (regs[2] != 0); // print chars until the null character
            break;
        case 5:
            cin >> regs[2];
            break;
        case 10:
            throw (SuccessfulQuit());
    }
}