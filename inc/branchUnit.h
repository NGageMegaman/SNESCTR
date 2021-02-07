#include "defines.h"
#include "regfile.h"
#include "mem.h"
using namespace std;

class BranchUnit {
    protected:
        BranchUnit();
        static BranchUnit *branchUnit;
    public:
        static BranchUnit *getInstance();
        void BCC(longw operand, longw address);
        void BCS(longw operand, longw address);
        void BEQ(longw operand, longw address);
        void BMI(longw operand, longw address);
        void BNE(longw operand, longw address);
        void BPL(longw operand, longw address);
        void BRA(longw operand, longw address);
        void BRL(longw operand, longw address);
        void BVC(longw operand, longw address);
        void BVS(longw operand, longw address);
        void JMP(longw operand, longw address);
        void JML(longw operand, longw address);
        void JSR(longw operand, longw address);
        void JSL(longw operand, longw address);
        void RTI(longw operand, longw address);
        void RTS(longw operand, longw address);
        void RTL(longw operand, longw address);
    private:
        Regfile *regfile;
        Mem *mem;
};