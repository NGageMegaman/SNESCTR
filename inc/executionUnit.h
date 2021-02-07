#include "defines.h"
#include "arithlogicUnit.h"
#include "branchUnit.h"
using namespace std;

class ExecutionUnit {
    protected:
        ExecutionUnit();
        static ExecutionUnit *executionUnit;
    public:
        static ExecutionUnit *getInstance();
    private:
        ArithlogicUnit *arithlogicUnit;
        BranchUnit *branchUnit;
}