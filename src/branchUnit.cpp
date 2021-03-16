#include "branchUnit.h"
using namespace std;

BranchUnit::BranchUnit() {
    regfile = Regfile::getInstance();
    mem = Mem::getInstance();
}

BranchUnit *BranchUnit::branchUnit = nullptr;

BranchUnit *BranchUnit::getInstance() {
    if (branchUnit == nullptr) {
        branchUnit = new BranchUnit();
    }
    return branchUnit;
}

void BranchUnit::BCC(longw operand, longw address) {
    //Branch Carry Clear
    if (!regfile->readP(PFlags_t::CARRY_FLAG)) {
        regfile->writePC(address);
    }
}

void BranchUnit::BCS(longw operand, longw address) {
    //Branch Carry Set
    if (regfile->readP(PFlags_t::CARRY_FLAG)) {
        regfile->writePC(address);
    }
}

void BranchUnit::BEQ(longw operand, longw address) {
    //Branch Equal
    if (regfile->readP(PFlags_t::ZERO_FLAG)) {
        regfile->writePC(address);
    }
}

void BranchUnit::BMI(longw operand, longw address) {
    //Branch Minus
    if (regfile->readP(PFlags_t::NEGATIVE_FLAG)) {
        regfile->writePC(address);
    }
}

void BranchUnit::BNE(longw operand, longw address) {
    //Branch Not Equal
    if (!regfile->readP(PFlags_t::ZERO_FLAG)) {
        regfile->writePC(address);
    }
}

void BranchUnit::BPL(longw operand, longw address) {
    //Branch Positive
    if (!regfile->readP(PFlags_t::NEGATIVE_FLAG)) {
        regfile->writePC(address);
    }
}

void BranchUnit::BRA(longw operand, longw address) {
    //Branch Always
    regfile->writePC(address);
}

void BranchUnit::BRL(longw operand, longw address) {
    //Branch Always Long
    //The address is already computed
    regfile->writePC(address);
}

void BranchUnit::BVC(longw operand, longw address) {
    //Branch Overflow Clear
    if (!regfile->readP(PFlags_t::OVERFLOW_FLAG)) {
        regfile->writePC(address);
    }
}

void BranchUnit::BVS(longw operand, longw address) {
    //Branch Overflow Set 
    if (regfile->readP(PFlags_t::OVERFLOW_FLAG)) {
        regfile->writePC(address);
    }
}

void BranchUnit::JMP(longw operand, longw address) {
    //Jump
    regfile->writePC(address);
}

void BranchUnit::JML(longw operand, longw address) {
    //Jump Long
    regfile->writePC(address);
    regfile->writePB(address >> 16);
}

void BranchUnit::JSR(longw operand, longw address) {
    //Jump to Subroutine
    word returnAddress = regfile->readPC() - 1; //Last byte of the instruction
    mem->pushStack(returnAddress >> 8); //high
    mem->pushStack(returnAddress); //low
    regfile->writePC(address);
}

void BranchUnit::JSL(longw operand, longw address) {
    //Jump to Subroutine Long
    word returnAddress = regfile->readPC() - 1; //Last byte of the instruction
    mem->pushStack(regfile->readPB());
    mem->pushStack(returnAddress >> 8); //high
    mem->pushStack(returnAddress); //low

    regfile->writePC(address);
    regfile->writePB(address >> 16);
}

void BranchUnit::RTI(longw operand, longw address) {
    //Return from Interrupt
    byte_t procStat = mem->pullStack();
    regfile->writePAll(procStat);
    byte_t PC_l = mem->pullStack();
    byte_t PC_h = mem->pullStack();
    regfile->writePC((PC_h << 8) | PC_l);

    if (regfile->readP(PFlags_t::EMULATION_FLAG)) {
        regfile->writeP(PFlags_t::INDEX_FLAG, true);
        regfile->writeP(PFlags_t::ACCUMULATOR_FLAG, true);
    }
    else regfile->writePB(mem->pullStack());
}

void BranchUnit::RTS(longw operand, longw address) {
    //Return from subroutine
    byte_t PC_l = mem->pullStack();
    byte_t PC_h = mem->pullStack();
    regfile->writePC(((PC_h << 8) | PC_l) + 1); //Last byte of instr + 1
}

void BranchUnit::RTL(longw operand, longw address) {
    //Return from subroutine Long
    byte_t PC_l = mem->pullStack();
    byte_t PC_h = mem->pullStack();
    regfile->writePC(((PC_h << 8) | PC_l) + 1); //Last byte_t of instr + 1
    regfile->writePB(mem->pullStack());
}
