#include "mem.h"
using namespace std;

Mem::Mem() {
    regfile = Regfile::getInstance();
    romMapper = RomMapper::getInstance();
    initMem();
}

Mem *Mem::mem = nullptr;

Mem *Mem::getInstance() {
    if (mem == nullptr) {
        mem = new Mem;
    }
    return mem;
}

void Mem::initMem() {
    byte_t *rom = romMapper->mapRom("smw.sfc");
    for (int i = 0; i<0xffffff; ++i) {
        writeByte(i, rom[i]);
    }    
    regfile->initPC(readWord(RST_VECTOR));
}

byte_t Mem::readByte(longw address) {
    return memory[address];
}

word Mem::readWord(longw address) {
    byte_t lowByte  = readByte(address);
    byte_t highByte = readByte(address+1);
    return (highByte << 8) | lowByte;
}

longw Mem::readLong(longw address) {
    byte_t lowByte    = readByte(address);
    byte_t middleByte = readByte(address+1);
    byte_t highByte   = readByte(address+2);
    return (highByte << 16) | (middleByte << 8) | lowByte;
}

void Mem::writeByte(longw address, byte_t operand) {
    memory[address] = operand;
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

void Mem::pushStack(byte_t operand) {
    word SP = regfile->readSP();
    writeByte(SP, operand);
    regfile->writeSP(SP-1);
}

byte_t Mem::pullStack() {
    word SP = regfile->readSP();
    byte_t result = readByte(SP);
    regfile->writeSP(SP+1);
    return result;
}