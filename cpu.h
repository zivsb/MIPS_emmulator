#ifndef CPU_H
#define CPU_H

#include "exceptions/Error.h"
#include "exceptions/SuccessfulQuit.h"

class CPU {
    private:
        std::uint32_t* instruction;
        std::uint32_t* dynMem;
        std::uint32_t* pc;
        std::uint32_t regs[32] = {0};
        void lw(std::uint8_t rs, std::uint8_t rt, std::uint16_t immed);
        void sw(std::uint8_t rs, std::uint8_t rt, std::uint16_t immed);
        void add(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd);
        void addi(std::uint8_t rs, std::uint8_t rt, std::uint16_t immed);
        // andr because and is already a keyword in C++
        void andr(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd);
        void andi(std::uint8_t rs, std::uint8_t rt, std::uint16_t immed);
        // orr because or is already a keyword
        void orr(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd);
        void ori(std::uint8_t rs, std::uint8_t rt, std::uint16_t immed);
        void nor(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd);
        // sll calls syscall if all parameters are zero
        void sll(std::uint8_t rt, std::uint8_t rd, std::uint8_t shamt);
        void beq(std::uint8_t rs, std::uint8_t rt, std::uint16_t immed);
        void bne(uint8_t rs, uint8_t rt, uint16_t immed);
        void slti(std::uint8_t rs, std::uint8_t rt, std::uint16_t immed);
        void slt(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd);
        void lui(std::uint8_t rs, std::uint8_t rt, std::uint16_t immed);
        void j(std::uint32_t address);
        void jal(std::uint32_t address);
        void jr(std::uint8_t rs);

        // theoretically syscall should actually be part of os, not CPU
        void syscall() throw(SuccessfulQuit, Error);

    public:
        std::uint32_t fetch(int pc);
        int exec(std::uint32_t instruction) throw(SuccessfulQuit, Error);
        CPU(std::uint32_t* instruction, std::uint32_t* dynMem, std::uint32_t* pc);

};

#endif