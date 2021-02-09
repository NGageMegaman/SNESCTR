#include "memopUnit.h"
using namespace std;

MemopUnit::MemopUnit() {
    regfile = Regfile::getInstance();
    mem = Mem::getInstance();
    procFlagUnit = ProcFlagUnit::getInstance();
}

MemopUnit *MemopUnit::memopUnit = nullptr;

MemopUnit *MemopUnit::getInstance() {
    if (memopUnit == nullptr) {
        memopUnit = new MemopUnit();
    }
    return memopUnit;
}

void MemopUnit::LDA(longw operand, longw address) {
    //Load Accumulator
    regfile->writeA(operand);
    
    procFlagUnit->zeroFlagA(operand);
    procFlagUnit->negativeFlagA(operand);
}

void MemopUnit::LDX(longw operand, longw address) {
    //Load X
    regfile->writeX(operand);
    
    procFlagUnit->zeroFlagX(operand);
    procFlagUnit->negativeFlagX(operand);
}

void MemopUnit::LDY(longw operand, longw address) {
    //Load Y
    regfile->writeY(operand);
    
    procFlagUnit->zeroFlagX(operand);
    procFlagUnit->negativeFlagX(operand);
}

void MemopUnit::MVN(longw operand, longw address) {
    //Move block Negative
    longw len = regfile->readA();
    word srcAddress = regfile->readX();
    word dstAddress = regfile->readY();
    byte_t srcBank = operand;
    byte_t dstBank = operand >> 8; 

    while (len != 0xffffffff) {
        byte_t data = mem->readByte((srcBank << 16) | srcAddress);
        mem->writeByte((dstBank << 16) | dstAddress, data);
        srcAddress++;
        dstAddress++;
        len--;
    }
    regfile->writeDB(dstBank);
    regfile->writeA(len);
    regfile->writeX(srcAddress);
    regfile->writeY(dstAddress);
}

void MemopUnit::MVP(longw operand, longw address) {
    //Move block Positive
    longw len = regfile->readA();
    word srcAddress = regfile->readX();
    word dstAddress = regfile->readY();
    byte_t srcBank = operand;
    byte_t dstBank = operand >> 8; 

    while (len != 0xffffffff) {
        byte_t data = mem->readByte((srcBank << 16) | srcAddress);
        mem->writeByte((dstBank << 16) | dstAddress, data);
        srcAddress--;
        dstAddress--;
        len--;
    }
    regfile->writeDB(dstBank);
    regfile->writeA(len);
    regfile->writeX(srcAddress);
    regfile->writeY(dstAddress);
}

void MemopUnit::PEA(longw operand, longw address) {
    //Push Effective Absolute address
    mem->pushStack(address >> 8);
    mem->pushStack(address);
}

void MemopUnit::PEI(longw operand, longw address) {
    //Push Effective Indirect address
    mem->pushStack(address >> 8);
    mem->pushStack(address);
}

void MemopUnit::PER(longw operand, longw address) {
    //Push Effective PC Relative address
    mem->pushStack(address >> 8);
    mem->pushStack(address);
}

void MemopUnit::PHA(longw operand, longw address) {
    //Push Accumulator
    if (regfile->isLargeA()) mem->pushStack(regfile->readA() >> 8);
    mem->pushStack(regfile->readA());
}

void MemopUnit::PHB(longw operand, longw address) {
    //Push Databank
    mem->pushStack(regfile->readDB());
}

void MemopUnit::PHD(longw operand, longw address) {
    //Push Direct page register
    mem->pushStack(regfile->readDP() >> 8);
    mem->pushStack(regfile->readDP());
}

void MemopUnit::PHK(longw operand, longw address) {
    //Push Program bank
    mem->pushStack(regfile->readPB());
}

void MemopUnit::PHP(longw operand, longw address) {
    //Push Processor status
    mem->pushStack(regfile->readPAll());
}

void MemopUnit::PHX(longw operand, longw address) {
    //Push X
    if (regfile->isLargeIdx()) mem->pushStack(regfile->readX() >> 8);
    mem->pushStack(regfile->readX());
}

void MemopUnit::PHY(longw operand, longw address) {
    //Push Y
    if (regfile->isLargeIdx()) mem->pushStack(regfile->readY() >> 8);
    mem->pushStack(regfile->readY());
}

void MemopUnit::PLA(longw operand, longw address) {
    //Pull A
    word result = mem->pullStack();
    if (regfile->isLargeA()) {
        result = (mem->pullStack() << 8) | result;
    }
    regfile->writeA(result);
    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
}

void MemopUnit::PLB(longw operand, longw address) {
    //Pull Databank
    word result = mem->pullStack();
    regfile->writeDB(result);
    procFlagUnit->zeroFlag(result);
    procFlagUnit->negativeFlag(result);
}

void MemopUnit::PLD(longw operand, longw address) {
    //Pull direct page register
    byte_t DP_l = mem->pullStack();
    byte_t DP_h = mem->pullStack();
    word DP = ((DP_h << 8) | DP_l);
    regfile->writeDP(DP);

    procFlagUnit->zeroFlag(DP);
    procFlagUnit->negativeFlagLarge(DP);
}

void MemopUnit::PLP(longw operand, longw address) {
    //Pull Processor status
    byte_t procStat = mem->pullStack();
    regfile->writePAll(procStat);
    if (regfile->readP(PFlags_t::EMULATION_FLAG)) {
        regfile->writeP(PFlags_t::INDEX_FLAG, true);
        regfile->writeP(PFlags_t::ACCUMULATOR_FLAG, true);
    }
}

void MemopUnit::PLX(longw operand, longw address) {
    //Pull X
    word result = mem->pullStack();
    if (regfile->isLargeIdx()) {
        result = (mem->pullStack() << 8) | result;
    }
    regfile->writeX(result);
    procFlagUnit->zeroFlagX(result);
    procFlagUnit->negativeFlagX(result);
}

void MemopUnit::PLY(longw operand, longw address) {
    //Pull Y
    word result = mem->pullStack();
    if (regfile->isLargeIdx()) {
        result = (mem->pullStack() << 8) | result;
    }
    regfile->writeY(result);
    procFlagUnit->zeroFlagX(result);
    procFlagUnit->negativeFlagX(result);
}

void MemopUnit::STA(longw operand, longw address) {
    //Store A
    if (regfile->isLargeA()) mem->writeWord(address, regfile->readA());
    else mem->writeByte(address, regfile->readA());
}

void MemopUnit::STX(longw operand, longw address) {
    //Store X
    if (regfile->isLargeIdx()) mem->writeWord(address, regfile->readX());
    else mem->writeByte(address, regfile->readX());
}

void MemopUnit::STY(longw operand, longw address) {
    //Store Y
    if (regfile->isLargeIdx()) mem->writeWord(address, regfile->readY());
    else mem->writeByte(address, regfile->readY());
}

void MemopUnit::STZ(longw operand, longw address) {
    //Store Zero
    if (regfile->isLargeA()) mem->writeWord(address, 0);
    else mem->writeByte(address, 0);
}

void MemopUnit::TRB(longw operand, longw address) {
    //Test and Reset memory Bits against A
    word nA = ~regfile->readA();
    word result = operand & nA;
    if (regfile->isLargeA()) mem->writeByte(address, result);
    else mem->writeWord(address, result);
    procFlagUnit->zeroFlagA(operand & regfile->readA());
}

void MemopUnit::TSB(longw operand, longw address) {
    //Test and Set memory Bits against A
    word result = operand & regfile->readA();
    if (regfile->isLargeA()) mem->writeByte(address, result);
    else mem->writeWord(address, result);
    procFlagUnit->zeroFlagA(operand & regfile->readA());
}