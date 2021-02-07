#include "executionUnit.h"
using namespace std;

ExecutionUnit::ExecutionUnit() {
    arithlogicUnit = ArithlogicUnit::getInstance();
    branchUnit = BranchUnit::getInstance();
    //memopUnit = MemopUnit::getInstance();
    //stackUnit = StackUnit::getInstance();
    //procstatUnit = ProcstatUnit::getInstance();
}

ExecutionUnit *ExecutionUnit::getInstance() {
    if (executionUnit == nullptr) {
        executionUnit = new ExecutionUnit();
    }
    return executionUnit;
}