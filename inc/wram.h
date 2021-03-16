#include "defines.h"
#pragma once
using namespace std;

class WRAM {
    protected:
        WRAM();
        static WRAM *wram;
    public:
        static WRAM *getInstance();
        byte_t read(longw readAddress);
        void write(byte_t data, longw writeAddress);
        byte_t readWMDATA();
        void writeWMDATA(byte_t data);
        void writeWMADDL(byte_t data);
        void writeWMADDM(byte_t data);
        void writeWMADDH(byte_t data);
        
    private:
        longw address;
        byte_t memory[WRAM_SIZE];
};