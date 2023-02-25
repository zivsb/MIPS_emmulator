#ifndef cpu_h
#define cpu_h

class CPU {
    private:
        std::uint32_t* instruction;
        std::uint32_t* staticMem;
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
        void sll(std::uint8_t rt, std::uint8_t rd, std::uint8_t shamt);
        void beq(std::uint8_t rs, std::uint8_t rt, std::uint16_t immed);
        void lui(std::uint8_t rs, std::uint8_t rt, std::uint16_t immed);
        void j(std::uint32_t address);

        // theoretically syscall should actually be part of os, not CPU
        void syscall();

    public:
        std::uint32_t fetch(int pc);
        int exec(std::uint32_t instruction);
        CPU(std::uint32_t* instruction, std::uint32_t* staticMem, std::uint32_t* pc);

};

#endif