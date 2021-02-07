#include "defines.h"
using namespace std;

struct ProcessorStatus {
    bool C, Z, V, N, D, E, M, X, I;
};

class Regfile {
    //Singleton
    protected:
        Regfile();
        static Regfile *regfile;
    public:
        static Regfile *getInstance();
        bool isLargeA();
        bool isLargeIdx();

        word readA();
        word readX();
        word readY();
        bool readP(PFlags_t PFlag);
        byte readPAll();
        word readDP();
        word readSP();
        word readPC();
        byte readPB();
        byte readDB();
        longw createFetchAddress(int offset);
        longw createAbsoluteAddress(word baseAddress);
        
        void writeA(word data);
        void writeX(word data);
        void writeY(word data);
        void writeP(PFlags_t PFlag, bool value);
        void writePAll(byte data);
        void writeDP(word data);
        void writeSP(word data);
        void writePC(word data);
        void writePB(byte data);
        void writeDB(byte data);

    private:
        void initP();
        word X, Y, A, DP, SP, PC;
        byte PB, DB;
        ProcessorStatus P;
};