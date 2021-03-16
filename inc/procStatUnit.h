#include "defines.h"
#include "regfile.h"
#include "mem.h"
#include "procFlagUnit.h"
#pragma once
using namespace std;

class ProcStatUnit {
    protected:
        ProcStatUnit();
        static ProcStatUnit *procStatUnit;
    public:
        static ProcStatUnit *getInstance();
        void BIT(longw operand, longw address);
        void BIT_imm(longw operand, longw address);
        void BRK(longw operand, longw address);
        void COP(longw operand, longw address);
        void CLC(longw operand, longw address);
        void CLD(longw operand, longw address);
        void CLI(longw operand, longw address);
        void CLV(longw operand, longw address);
        void REP(longw operand, longw address);
        void SEC(longw operand, longw address);
        void SED(longw operand, longw address);
        void SEI(longw operand, longw address);
        void SEP(longw operand, longw address);
        void STP(longw operand, longw address);
        void TAX(longw operand, longw address);
        void TAY(longw operand, longw address);
        void TCD(longw operand, longw address);
        void TCS(longw operand, longw address);
        void TDC(longw operand, longw address);
        void TSC(longw operand, longw address);
        void TSX(longw operand, longw address);
        void TXA(longw operand, longw address);
        void TXS(longw operand, longw address);
        void TXY(longw operand, longw address);
        void TYA(longw operand, longw address);
        void TYX(longw operand, longw address);
        void WAI(longw operand, longw address);
        void WDM(longw operand, longw address);
        void XBA(longw operand, longw address);
        void XCE(longw operand, longw address);
        void NOP(longw operand, longw address);
        void NMI();
    private:
        Regfile *regfile;
        Mem *mem;
        ProcFlagUnit *procFlagUnit;
};