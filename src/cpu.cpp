#include "cpu.h"
using namespace std;

CPU::CPU() {
    mem = Mem::getInstance();
    regfile = Regfile::getInstance();
    decoder = Decoder::getInstance();
    
    uint16_t resetAddress = mem->readWord(RESET_VECTOR);
    regfile->writePC(resetAddress);
}

CPU *CPU::getInstance() {
    if (cpu == nullptr) {
        cpu = new CPU;
    }
    return cpu;
}

void CPU::executeInstruction() {
    //Step 1: Fetch the instruction
    inst_t inst = fetch();
    //Step 2: Decode the operand and address
    uint32_t operand, address;
    decoder->decode(inst, &operand, &address);
    //Step 3: Execute the instruction
    executionUnit->execute(inst, operand, address);
}

inst_t CPU::fetch() {
    longw fetch_address = regfile->createFetchAddress();
    return (inst_t) mem->readByte(fetch_address);
}