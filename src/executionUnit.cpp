#include "executionUnit.h"
using namespace std;

ExecutionUnit::ExecutionUnit() {
    arithlogicUnit = AirthLogicUnit::getInstance();
    branchUnit = BranchUnit::getInstance();
    memopUnit = MemopUnit::getInstance();
    stackUnit = StackUnit::getInstance();
    porcstatUnit = ProcstatUnit::getInstance();
}