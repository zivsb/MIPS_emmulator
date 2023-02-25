#ifndef cpu_h
#define cpu_h

class CPU {
    private:
        std::uint32_t* instruction0;
        std::uint32_t* pc;
        void lw();
        void sw();
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
        void j(std::uint32_t address);

    public:
        int fetch(int pc);
        int exec(int instruction);
        CPU(std::uint32_t* instruction0, std::uint32_t* pc) {
            this->instruction0 = instruction0;
            this->pc = pc;
        }

};

#endif