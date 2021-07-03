#include "cpu.h"
using namespace std;

CPU::CPU() {
    mem = Mem::getInstance();
    regfile = Regfile::getInstance();
    decoder = Decoder::getInstance();
    executionUnit = ExecutionUnit::getInstance();
    
    word resetAddress = mem->readWord(RST_VECTOR);
    regfile->writePC(resetAddress);
}

CPU *CPU::cpu = nullptr;

CPU *CPU::getInstance() {
    if (cpu == nullptr) {
        cpu = new CPU();
    }
    return cpu;
}

bool debug = false;
bool lmao = false;

void CPU::executeInstruction() {
    longw PCprev = (regfile->readPB() << 16) | regfile->readPC();
    //Step 1: Fetch the instruction
    inst_t inst = fetch();
    //Step 2: Decode the operand and address
    uint32_t operand, address;
    decoder->decode(inst, &operand, &address);
    //Step 3: Execute the instruction
    executionUnit->execute(inst, operand, address);

    //Debug
    
    //if (((regfile->readPB() << 16) | regfile->readPC()) == 0x9e85) debug = true;
    //else debug = false;
    //if (address == 0x65) debug = true;
    if (regfile->readPC() < 0x8000 || debug) {
        //cout << "Mem[0x7e0109] = " << std::hex << (int) mem->readLong(0x7e0109) << endl;
        //cout << "DP = " << std::hex << (int) regfile->readDP() << endl;
        cout << "PCprev: " << std::hex << (int) PCprev << endl;
        cout << "PC: " << std::hex << (int) regfile->readPB() << (int) regfile->readPC() << " A: " << (int) regfile->readA() << " X: " << (int) regfile->readX() << " Y: " << (int) regfile->readY() << " DB: " << (int) regfile->readDB() << " inst = " << (int) inst << endl;
        cout << "PStat: " << std::hex << (int) regfile->readPAll() << endl;
        cout << "SP: " << std::hex << (int) regfile->readSP() << endl;
    }
}

inst_t CPU::fetch() {
    longw fetch_address = regfile->createFetchAddress(0);
    return (inst_t) mem->readByte(fetch_address);
}

void CPU::NMI() {
    executionUnit->NMI();
}