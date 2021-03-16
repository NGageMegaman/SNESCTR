#include "cgram.h"
using namespace std;

CGRAM::CGRAM() {
    accessHigh = false;
    address = 0;
    writeData = 0;
}

CGRAM *CGRAM::cgram = nullptr;

CGRAM *CGRAM::getInstance() {
    if (cgram == nullptr) {
        cgram = new CGRAM();
    }
    return cgram;
}

void CGRAM::writeCGADD(byte_t data) {
    address = data;
}

void CGRAM::writeCGDATA(byte_t data) {
    if (accessHigh) {
        writeData = (data << 8) | (writeData & 0x00ff);
        memory[address] = writeData;
        address++;
        accessHigh = false;
    }
    else {
        writeData = (writeData & 0xff00) | data;
        accessHigh = true;
    }
}

byte_t CGRAM::readCGDATA() {
    byte_t readData;
    if (accessHigh) {
        accessHigh = false;
        readData = memory[address] & 0x00ff;
        address++;
    }
    else {
        accessHigh = true;
        readData = (memory[address] >> 8) & 0x00ff;
    }
    return readData;
}

word CGRAM::read(longw readAddress) {
    return memory[readAddress];
}