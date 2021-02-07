#include "mem.h"
using namespace std;

Mem::Mem() {
    regfile = Regfile::getInstance();
}

Mem *Mem::getInstance() {
    if (mem == nullptr) {
        mem = new Mem;
    }
    return mem;
}

byte Mem::readByte(longw address) {
    //TBI
    return 0;
}

word Mem::readWord(longw address) {
    byte lowByte  = readByte(address);
    byte highByte = readByte(address+1);
    return (highByte << 8) | lowByte;
}

longw Mem::readLong(longw address) {
    byte lowByte    = readByte(address);
    byte middleByte = readByte(address+1);
    byte highByte   = readByte(address+2);
    return (highByte << 16) | (middleByte << 8) | lowByte;
}

void Mem::writeByte(longw address, byte operand) {
    //TBI
    return;
}

void Mem::writeWord(longw address, word operand) {
    writeByte(address, operand);
    writeByte(address+1, operand >> 8);
}

void Mem::writeLong(longw address, longw operand) {
    writeByte(address, operand);
    writeByte(address+1, operand >> 8);
    writeByte(address+2, operand >> 16);
}

void Mem::pushStack(byte operand) {
    word SP = regfile->readSP();
    writeByte(SP, operand);
    regfile->writeSP(SP-1);
}

byte Mem::pullStack() {
    word SP = regfile->readSP();
    byte result = readByte(SP);
    regfile->writeSP(SP+1);
}