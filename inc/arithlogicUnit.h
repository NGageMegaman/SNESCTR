#include "defines.h"
#include "procFlagUnit.h"
#include "mem.h"
#include "regfile.h"
using namespace std;

class ArithlogicUnit {
    protected:
        ArithlogicUnit();
        static ArithlogicUnit *arithlogicUnit;
    public:
        static ArithlogicUnit *getInstance();
        void ADC(longw operand, longw address);
        void ASL_A(longw operand, longw address);
        void ASL_mem(longw operand, longw address);
        void CMP(longw operand, longw address);
        void CPX(longw operand, longw address);
        void CPY(longw operand, longw address);
        void DEC_A(longw operand, longw address);
        void DEC_mem(longw operand, longw address);
        void DEX(longw operand, longw address);
        void DEY(longw operand, longw address);
        void EOR(longw operand, longw address);
        void INC_A(longw operand, longw address);
        void INC_mem(longw operand, longw address);
        void INX(longw operand, longw address);
        void INY(longw operand, longw address);
        void LSR_A(longw operand, longw address);
        void LSR_mem(longw operand, longw address);
        void ORA(longw operand, longw address);
        void ROL_A(longw operand, longw address);
        void ROL_mem(longw operand, longw address);
        void ROR_A(longw operand, longw address);
        void ROR_mem(longw operand, longw address);
        void SBC(longw operand, longw address);
        
    private:
        ProcFlagUnit *procFlagUnit;
        Regfile *regfile;
        Mem *mem;
};