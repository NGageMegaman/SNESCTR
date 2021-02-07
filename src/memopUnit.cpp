#include "memopUnit.h"
using namespace std;

MemopUnit::MemopUnit() {

}

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
    byte srcBank = operand;
    byte dstBank = operand >> 8; 

    while (len != 0xffffffff) {
        byte data = mem->readByte((srcBank << 16) | srcAddress);
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
    byte srcBank = operand;
    byte dstBank = operand >> 8; 

    while (len != 0xffffffff) {
        byte data = mem->readByte((srcBank << 16) | srcAddress);
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