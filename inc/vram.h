#include "defines.h"
#pragma once
using namespace std;

class VRAM {
    protected:
        VRAM();
        static VRAM *vram;
    public:
        static VRAM *getInstance();
        void writeVMAIN(byte_t data);
        void writeVMADDL(byte_t data);
        void writeVMADDH(byte_t data);
        void writeVMDATAL(byte_t data);
        void writeVMDATAH(byte_t data);
        byte_t readVMDATAL();
        byte_t readVMDATAH();
        void write(word data, longw writeAddress);
        word read(longw readAddress);
    private:
        void CPUwrite();
        void CPUread();
        word remapAddress();

        bool incrementAccessHigh;
        byte_t incrementAmount;
        byte_t addressRemapping;
        word address;
        word writeData;
        word readBuffer;
        word memory[VRAM_SIZE];
};