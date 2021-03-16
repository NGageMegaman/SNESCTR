#include "wram.h"
using namespace std;

WRAM::WRAM() {
    for (int i = 0; i<WRAM_SIZE; ++i) {
        memory[i] = 0;
    }
    address = 0;
}

WRAM *WRAM::wram = nullptr;

WRAM *WRAM::getInstance() {
    if (wram == nullptr) {
        wram = new WRAM;
    }
    return wram;
}

byte_t WRAM::read(longw readAddress) {
    longw addr = readAddress - 0x7e0000;
    return memory[addr];
}

void WRAM::write(byte_t data, longw writeAddress) {
    longw addr = writeAddress - 0x7e0000;
    memory[addr] = data;
}

byte_t WRAM::readWMDATA() {
    byte_t data = memory[address];
    address = (address + 1) % 0x020000;
    return data;
}

void WRAM::writeWMDATA(byte_t data) {
    memory[address] = data;
    address = (address + 1) % 0x020000;
}

void WRAM::writeWMADDL(byte_t data) {
    address = (address & 0xffff00) | data;
}

void WRAM::writeWMADDM(byte_t data) {
    address = (address & 0xff00ff) | (data << 8);
}

void WRAM::writeWMADDH(byte_t data) {
    address = (address & 0x00ffff) | ((data & 1) << 16);
}