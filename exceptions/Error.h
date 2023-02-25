#ifndef ERROR_H
#define ERROR_H

class Error {
    public:
        // type 0 for unknown/unspecified
        // type 1 for invalid instruction
        // type 2 for memory out of bounds error
        int type;
        Error(int type = 0) {
            this->type = type;
        }
};

#endif