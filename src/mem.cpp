#include "mem.h"
using namespace std;

Mem::Mem() {
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