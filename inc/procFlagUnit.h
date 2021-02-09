#include "defines.h"
#include "regfile.h"
#pragma once
using namespace std;

class ProcFlagUnit {
    protected:
        ProcFlagUnit();
        static ProcFlagUnit *procFlagUnit;
    public:
        static ProcFlagUnit *getInstance();
        void zeroFlag(longw data);
        void zeroFlagA(longw data);
        void zeroFlagX(longw data);
        void negativeFlag(longw data);
        void negativeFlagLarge(longw data);
        void negativeFlagA(longw data);
        void negativeFlagX(longw data);
        void carryFlagA(longw data);
        void carryFlagX(longw data);
        void carryFlagCMP(longw reg, longw data, bool large);
        void overflowFlagADC(longw operand, longw result);
    private:
        Regfile *regfile;
};