#include "defines.h"
#pragma once
using namespace std;

class CGRAM {
    protected:
        CGRAM();
        static CGRAM *cgram;
    public:
        static CGRAM *getInstance();
        void writeCGADD(byte_t data);
        void writeCGDATA(byte_t data);
        byte_t readCGDATA();
        word read(longw address);
    private:
        longw address;
        bool accessHigh;
        word writeData;
        word memory[CGRAM_SIZE];
};