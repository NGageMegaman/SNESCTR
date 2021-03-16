#include "vram.h"
using namespace std;

VRAM::VRAM() {
    for (int i = 0; i<VRAM_SIZE; ++i) {
        memory[i] = 0;
    }
    incrementAccessHigh = 0;
    incrementAmount = 1;
    addressRemapping = 0;
    address = 0;
    writeData = 0;
}

VRAM *VRAM::vram = nullptr;

VRAM *VRAM::getInstance() {
    if (vram == nullptr) {
        vram = new VRAM();
    }
    return vram;
}

void VRAM::writeVMAIN(byte_t data) {
    byte_t inc = data & 0x03;
    addressRemapping = (data >> 2) & 0x03;
    incrementAccessHigh = (data >> 7) & 1;
    switch (inc) {
        case 0: incrementAmount = 1; break;
        case 1: incrementAmount = 32; break;
        default: incrementAmount = 128;
    }
}

void VRAM::writeVMADDL(byte_t data) {
    address = (address & 0xff00) | data;
}

void VRAM::writeVMADDH(byte_t data) {
    address = (data << 8) | (address & 0x00ff);
}

void VRAM::writeVMDATAL(byte_t data) {
    writeData = (writeData & 0xff00) | data;
    if (incrementAccessHigh == 0) CPUwrite();
}

void VRAM::writeVMDATAH(byte_t data) {
    writeData = (data << 8) | (writeData & 0x00ff);
    if (incrementAccessHigh == 1) CPUwrite();
}

byte_t VRAM::readVMDATAL() {
    byte_t readData = readBuffer & 0x00ff;
    if (incrementAccessHigh == 0) CPUread();
    return readData;
}

byte_t VRAM::readVMDATAH() {
    byte_t readData = readBuffer >> 8;
    if (incrementAccessHigh == 1) CPUread();
    return readData;
}

void VRAM::write(word data, longw writeAddress) {
    memory[writeAddress] = data;
}

void VRAM::CPUwrite() {
    word remappedAddress = remapAddress();
    memory[remappedAddress] = writeData;
    readBuffer = writeData;
    address += incrementAmount;
}

word VRAM::read(longw readAddress) {
    return memory[readAddress];
}

void VRAM::CPUread() {
    word remappedAddress = remapAddress();
    readBuffer = memory[remappedAddress];
    address += incrementAmount;
}

word VRAM::remapAddress() {
    word remappedAddress;
    word a, b, c;
    switch (addressRemapping) {
        case 0: remappedAddress = address; break;
        case 1:
            a = (address >> 8) & 0x00ff;
            b = (address >> 5) & 0x0007;
            c = address & 0x001f;
            remappedAddress = (a << 8) | (c << 3) | b;
            break;
        case 2:
            a = (address >> 9) & 0x007f;
            b = (address >> 6) & 0x0007;
            c = address & 0x003f;
            remappedAddress = (a << 9) | (c << 3) | b;
            break;
        default:
            a = (address >> 10) & 0x003f;
            b = (address >> 7) & 0x0007;
            c = address & 0x007f;
            remappedAddress = (a << 10) | (c << 3) | b;
    }
    return remappedAddress;
}