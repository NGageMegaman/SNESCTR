#include "defines.h"
#include "regfile.h"
#include "romMapper.h"
#pragma once
using namespace std;

class Mem {
    protected:
        Mem();
        static Mem *mem;
    public:
        static Mem *getInstance();
        void initMem();
        byte_t  readByte(longw address);
        word  readWord(longw address);
        longw readLong(longw address);
        void writeByte(longw address, byte_t operand);
        void writeWord(longw address, word operand);
        void writeLong(longw address, longw operand);
        void pushStack(byte_t operand);
        byte_t pullStack();
    private:
        Regfile *regfile;
        RomMapper *romMapper;
        byte_t memory[0xffffff];
};