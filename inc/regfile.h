#include "defines.h"
#pragma once
using namespace std;

class Regfile {
    //Singleton
    protected:
        Regfile();
        static Regfile *regfile;
    public:
        static Regfile *getInstance();
        void initPC(word value);
        bool isLargeA();
        bool isLargeIdx();

        word readA();
        word readALarge();
        word readX();
        word readXLarge();
        word readY();
        word readYLarge();
        bool readP(PFlags_t PFlag);
        byte_t readPAll();
        word readDP();
        word readSP();
        word readPC();
        byte_t readPB();
        byte_t readDB();
        longw createFetchAddress(int offset);
        longw createAbsoluteAddress(word baseAddress);
        
        void writeA(word data);
        void writeALarge(word data);
        void writeX(word data);
        void writeY(word data);
        void writeP(PFlags_t PFlag, bool value);
        void writePAll(byte_t data);
        void writeDP(word data);
        void writeSP(word data);
        void writePC(word data);
        void writePB(byte_t data);
        void writeDB(byte_t data);

    private:
        void initP();
        word X, Y, A, DP, SP, PC;
        byte_t PB, DB;
        ProcessorStatus P;
};