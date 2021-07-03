
#include "defines.h"
#pragma once
using namespace std;

class Muldiv {
    protected:
        Muldiv();
        static Muldiv *muldiv;
    public:
        static Muldiv *getInstance();
        void writeWRMPYA(byte_t data);
        void writeWRMPYB(byte_t data);
        void writeWRDIVL(byte_t data);
        void writeWRDIVH(byte_t data);
        void writeWRDIVB(byte_t data);
        byte_t readRDDIVL();
        byte_t readRDDIVH();
        byte_t readRDMPYL();
        byte_t readRDMPYH();
    private:
        byte_t mulA, mulB;
        word dividend;
        byte_t divisor;
        word quotient;
        word mulResDivRem;
};