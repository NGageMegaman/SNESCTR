#include "defines.h"
#include "arithlogicUnit.h"
#include "branchUnit.h"
#include "memopUnit.h"
#include "procStatUnit.h"
#pragma once
using namespace std;

class ExecutionUnit {
    protected:
        ExecutionUnit();
        static ExecutionUnit *executionUnit;
    public:
        static ExecutionUnit *getInstance();
        void execute(inst_t inst, longw operand, longw address);
        void NMI();
    private:
        Regfile *regfile;
        ArithlogicUnit *arithlogicUnit;
        BranchUnit *branchUnit;
        MemopUnit *memopUnit;
        ProcStatUnit *procStatUnit;
};