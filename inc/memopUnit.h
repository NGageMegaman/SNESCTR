#include "defines.h"
#include "regfile.h"
#include "mem.h"
#include "procFlagUnit.h"
using namespace std;

class MemopUnit {
    protected:
        MemopUnit();
        static MemopUnit *memopUnit;
    public:
        static MemopUnit *getInstance();
        void LDA(longw operand, longw address);
        void LDX(longw operand, longw address);
        void LDY(longw operand, longw address);
        void MVN(longw operand, longw address);
        void MVP(longw operand, longw address);
        void PEA(longw operand, longw address);
        void PEI(longw operand, longw address);
        void PER(longw operand, longw address);
        void PHA(longw operand, longw address);
        void PHB(longw operand, longw address);
        void PHD(longw operand, longw address);
        void PHK(longw operand, longw address);
        void PHP(longw operand, longw address);
        void PHX(longw operand, longw address);
        void PHY(longw operand, longw address);
        void PLA(longw operand, longw address);
        void PLB(longw operand, longw address);
        void PLD(longw operand, longw address);
        void PLP(longw operand, longw address);
        void PLX(longw operand, longw address);
        void PLY(longw operand, longw address);
        void STA(longw operand, longw address);
        void STX(longw operand, longw address);
        void STY(longw operand, longw address);
        void STZ(longw operand, longw address);
        void TRB(longw operand, longw address);
        void TSB(longw operand, longw address);
    private:
        Regfile *regfile;
        Mem *mem;
        ProcFlagUnit *procFlagUnit;
}