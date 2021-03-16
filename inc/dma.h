#include "defines.h"
#include "mem.h"
#pragma once
using namespace std;

class DMA {
    protected:
        DMA();
        static DMA *dma;
    public:
        static DMA *getInstance(Mem *memInstance);
        void writeMDMA(byte_t data);
        void writeDMAPx(byte_t data, byte_t channel);
        void writeBBADx(byte_t data, byte_t channel);
        void writeA1TxL(byte_t data, byte_t channel);
        void writeA1TxH(byte_t data, byte_t channel);
        void writeA1Bx(byte_t data, byte_t channel);
        void writeDASxL(byte_t data, byte_t channel);
        void writeDASxH(byte_t data, byte_t channel);
        byte_t readDMAPx(byte_t channel);
        byte_t readBBADx(byte_t channel);
        byte_t readA1TxL(byte_t channel);
        byte_t readA1TxH(byte_t channel);
        byte_t readA1Bx(byte_t channel);
        byte_t readDASxL(byte_t channel);
        byte_t readDASxH(byte_t channel);
    private:
        void dmaEnable(byte_t channel);
        void transfer(longw A, longw B, bool BtoA);
        Mem *mem;

        bool transferBA[8];
        bool addressIncrement[8];
        bool fixedTransfer[8];
        byte_t transferMode[8];
        longw addressA[8];
        longw addressB[8];
        word size[8];
};