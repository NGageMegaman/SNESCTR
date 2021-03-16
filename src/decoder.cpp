#include "decoder.h"
using namespace std;

Decoder::Decoder() {
    regfile = Regfile::getInstance();
    mem = Mem::getInstance();
}

Decoder *Decoder::decoder = nullptr;

Decoder *Decoder::getInstance() {
    if (decoder == nullptr) {
        decoder = new Decoder();
    }
    return decoder;
}

void Decoder::decode(inst_t inst, longw *operand, longw *address) {
    //The decode table is represented by a matrix
    //Generally, using just the column number, we can discern
    //which addressing mode we must use
    uint8_t column = inst & 0x1f;
    switch (column) {
        case 0x00: decodeColumn00(inst, operand, address); break;
        case 0x01: decodeOperandDirectIndexedIndirect(operand, address); break;
        case 0x02: decodeColumn02(inst, operand, address); break;
        case 0x03: decodeOperandStackRelative(operand, address); break;
        case 0x04: decodeColumn04(inst, operand, address); break;
        case 0x05: decodeOperandDirect(operand, address); break;
        case 0x06: decodeOperandDirect(operand, address); break;
        case 0x07: decodeOperandDirectIndirectLong(operand, address); break;
        case 0x08: decodeNoOperand(operand, address); break;
        case 0x09: decodeColumn09(inst, operand, address); break;
        case 0x0a: decodeNoOperand(operand, address); break;
        case 0x0b: decodeNoOperand(operand, address); break;
        case 0x0c: decodeColumn0c(inst, operand, address); break;
        case 0x0d: decodeOperandAbsolute(operand, address); break;
        case 0x0e: decodeOperandAbsolute(operand, address); break;
        case 0x0f: decodeOperandAbsoluteLong(operand, address); break;
        case 0x10: decodeOperandRelative(operand, address); break;
        case 0x11: decodeOperandDirectIndirectIndexed(operand, address); break;
        case 0x12: decodeOperandDirectIndirect(operand, address); break;
        case 0x13: decodeOperandStackRelativeIndirectIndexed(operand, address); break;
        case 0x14: decodeColumn14(inst, operand, address); break;
        case 0x15: decodeOperandDirectIndexedX(operand, address); break;
        case 0x16: decodeColumn16(inst, operand, address); break;
        case 0x17: decodeOperandDirectIndirectLongIndexed(operand, address); break;
        case 0x18: decodeNoOperand(operand, address); break;
        case 0x19: decodeOperandAbsoluteIndexedY(operand, address); break;
        case 0x1a: decodeNoOperand(operand, address); break;
        case 0x1b: decodeNoOperand(operand, address); break;
        case 0x1c: decodeColumn1c(inst, operand, address); break;
        case 0x1d: decodeOperandAbsoluteIndexedX(operand, address); break;
        case 0x1e: decodeColumn1e(inst, operand, address); break;
        case 0x1f: decodeOperandAbsoluteLongIndexed(operand, address); break;
        default:   decodeNoOperand(operand, address);
    }
}

void Decoder::decodeColumn00(inst_t inst, longw *operand, longw *address) {
    if (inst == JSR1) decodeOperandImmediateWord(operand, address);
    else if (inst == BRA) decodeOperandRelative(operand, address);
    else if (inst == BRK) decodeOperandImmediate(operand, address);
    else if (inst != RTI && inst != RTS) {
        if (regfile->isLargeIdx()) decodeOperandImmediateWord(operand, address);
        else decodeOperandImmediate(operand, address);
    }
    else decodeNoOperand(operand, address);
}

void Decoder::decodeColumn02(inst_t inst, longw *operand, longw *address) {
    if (inst == COP || inst == REP || inst == SEP) {
        decodeOperandImmediate(operand, address);
    }
    else if (inst == LDX1) {
        if (regfile->isLargeIdx()) decodeOperandImmediateWord(operand, address);
        else decodeOperandImmediate(operand, address);
    }
    else if (inst == PER || inst == BRL) {
        decodeOperandRelativeLong(operand, address);
    }
    else decodeOperandImmediateLong(operand, address);
}

void Decoder::decodeColumn04(inst_t inst, longw *operand, longw *address) {
    if (inst == MVP) decodeOperandBlockMove(operand, address);
    else decodeOperandDirect(operand, address);
}

void Decoder::decodeColumn09(inst_t inst, longw *operand, longw *address) {
    if (regfile->isLargeA()) decodeOperandImmediateWord(operand, address);
    else decodeOperandImmediate(operand, address);
}

void Decoder::decodeColumn0c(inst_t inst, longw *operand, longw *address) {
    if (inst == JMP3) decodeOperandAbsoluteIndirect(operand, address);
    else decodeOperandAbsolute(operand, address);
}

void Decoder::decodeColumn14(inst_t inst, longw *operand, longw *address) {
    if (inst == TRB1) decodeOperandDirect(operand, address);
    else if (inst == MVN) decodeOperandBlockMove(operand, address);
    else if (inst == PEI) decodeOperandDirectIndirect(operand, address);
    else if (inst == PEA) decodeOperandAbsolute(operand, address);
    else decodeOperandDirectIndexedX(operand, address);
}

void Decoder::decodeColumn16(inst_t inst, longw *operand, longw *address) {
    if (inst == STX3 || inst == LDX4) {
        decodeOperandDirectIndexedY(operand, address);
    }
    else decodeOperandDirectIndexedX(operand, address);
}

void Decoder::decodeColumn1c(inst_t inst, longw *operand, longw *address) {
    if (inst == TRB2 || inst == STZ3) decodeOperandAbsolute(operand, address);
    else if (inst == JMP2) decodeOperandAbsoluteLong(operand, address);
    else if (inst == JMP4 || inst == JSR2) decodeOperandAbsoluteIndexedIndirect(operand, address);
    else if (inst == JMP5) decodeOperandAbsoluteIndirectLong(operand, address);
    else decodeOperandAbsoluteIndexedX(operand, address);
}

void Decoder::decodeColumn1e(inst_t inst, longw *operand, longw *address) {
    if (inst == LDX5) decodeOperandAbsoluteIndexedY(operand, address);
    else decodeOperandAbsoluteIndexedX(operand, address);
}

/////////////////////
// DECODE OPERANDS //
/////////////////////

/** These functions perform 3 tasks: **/
/** 1: Build the correct operand     **/
/** 2: Build the correct address     **/
/** 3: Increment the PC              **/

void Decoder::decodeOperandImmediate(longw *operand, longw *address) {
    //Read a byte_t immediate value
    longw operandAddress = regfile->createFetchAddress(1);
    byte_t op = mem->readByte(operandAddress);

    *address = op;
    *operand = op;
    implicitIncrement(2);
}

void Decoder::decodeOperandImmediateWord(longw *operand, longw *address) {
    //Read a byte_t immediate value
    longw operandAddress = regfile->createFetchAddress(1);
    word op = mem->readWord(operandAddress);

    *address = op;
    *operand = op;
    implicitIncrement(3);
}

void Decoder::decodeOperandImmediateLong(longw *operand, longw *address) {
    //Read a byte_t immediate value
    longw operandAddress = regfile->createFetchAddress(1);
    longw op = mem->readLong(operandAddress);

    *address = op;
    *operand = op;
    implicitIncrement(4);
}


void Decoder::decodeOperandAbsolute(longw *operand, longw *address) {
    //address = DB:word, operand = mem[address]
    longw operandAddress = regfile->createFetchAddress(1);
    word absoluteBaseAddress = mem->readWord(operandAddress);
    longw absoluteAddress = regfile->createAbsoluteAddress(absoluteBaseAddress);
    word op = mem->readWord(absoluteAddress);

    *address = absoluteAddress;
    *operand = op;
    implicitIncrement(3);
}

void Decoder::decodeOperandAbsoluteLong(longw *operand, longw *address) {
    //address = long, operand = mem[address]

    longw operandAddress = regfile->createFetchAddress(1);
    longw absoluteAddress = mem->readLong(operandAddress);
    word op = mem->readWord(absoluteAddress);

    *address = absoluteAddress;
    *operand = op;
    implicitIncrement(4);
}

void Decoder::decodeOperandAbsoluteLongIndexed(longw *operand, longw *address) {
    //address = long + x, operand = mem[address]

    longw operandAddress = regfile->createFetchAddress(1);
    longw absoluteAddress = mem->readLong(operandAddress) + regfile->readX();
    word op = mem->readWord(absoluteAddress);

    *address = absoluteAddress;
    *operand = op;
    implicitIncrement(4);
}

void Decoder::decodeOperandAbsoluteIndexedX(longw *operand, longw *address) {
    //address = DB:word + x, operand = mem[address]

    longw operandAddress = regfile->createFetchAddress(1);
    word absoluteBaseAddress = mem->readWord(operandAddress) + regfile->readX();
    longw absoluteAddress = regfile->createAbsoluteAddress(absoluteBaseAddress);
    word op = mem->readWord(absoluteAddress);

    *address = absoluteAddress;
    *operand = op;
    implicitIncrement(3);
}

void Decoder::decodeOperandAbsoluteIndexedY(longw *operand, longw *address) {
    //address = DB:word + y, operand = mem[address]

    longw operandAddress = regfile->createFetchAddress(1);
    word absoluteBaseAddress = mem->readWord(operandAddress) + regfile->readY();
    longw absoluteAddress = regfile->createAbsoluteAddress(absoluteBaseAddress);
    word op = mem->readWord(absoluteAddress);

    *address = absoluteAddress;
    *operand = op;
    implicitIncrement(3);
}

void Decoder::decodeOperandAbsoluteIndirect(longw *operand, longw *address) {
    //address = ram[00:word], operand = mem[address]
    longw operandAddress = regfile->createFetchAddress(1);
    word indirectAddress = mem->readWord(operandAddress);
    longw absoluteAddress = mem->readWord(indirectAddress);
    word op = mem->readWord(absoluteAddress);

    *address = absoluteAddress;
    *operand = op;
    implicitIncrement(3);
}

void Decoder::decodeOperandAbsoluteIndirectLong(longw *operand, longw *address) {
    //address = ram[00:word], operand = mem[address]
    longw operandAddress = regfile->createFetchAddress(1);
    longw indirectAddress = (regfile->readPB() << 16) + mem->readWord(operandAddress); //POSSIBLE BUG, DOES JML RECEIVE INDIRECT OR ABSOLUTE ADDRESS?
    longw absoluteAddress = mem->readLong(indirectAddress);
    word op = mem->readWord(absoluteAddress);

    *address = absoluteAddress;
    *operand = op;
    implicitIncrement(3);
}

void Decoder::decodeOperandAbsoluteIndexedIndirect(longw *operand, longw *address) {
    //address = mem[00:word + x], operand = mem[address]
    longw operandAddress = regfile->createFetchAddress(1);
    longw indirectAddress = (regfile->readPB() << 16) + mem->readWord(operandAddress) + regfile->readX();
    word absoluteAddress = mem->readWord(indirectAddress);
    word op = mem->readWord(absoluteAddress);

    *address = absoluteAddress;
    *operand = op;
    implicitIncrement(3);
}

void Decoder::decodeOperandDirect(longw *operand, longw *address) {
    //address = 00:DP+byte_t, operand = mem[address]
    longw operandAddress = regfile->createFetchAddress(1);
    word directAddress = mem->readByte(operandAddress) + regfile->readDP();
    word op = mem->readWord(directAddress);

    *address = directAddress;
    *operand = op;
    implicitIncrement(2);
}

void Decoder::decodeOperandDirectIndirect(longw *operand, longw *address) {
    //address = DB:mem[byte_t+DP], operand = mem[address]    
    longw operandAddress = regfile->createFetchAddress(1);
    word indirectAddress = mem->readByte(operandAddress) + regfile->readDP();
    word directBaseAddress = mem->readWord(indirectAddress);
    longw directAddress = regfile->createAbsoluteAddress(directBaseAddress);
    word op = mem->readWord(directAddress);

    *address = directAddress;
    *operand = op;
    implicitIncrement(2);
}

void Decoder::decodeOperandDirectIndirectLong(longw *operand, longw *address) {
    //address_long = mem[byte_t+DP], operand = mem[address_long]    
    longw operandAddress = regfile->createFetchAddress(1);
    word indirectAddress = mem->readByte(operandAddress) + regfile->readDP();
    longw directAddress = mem->readLong(indirectAddress);
    word op = mem->readWord(directAddress);

    *address = directAddress;
    *operand = op;
    implicitIncrement(2);
}

void Decoder::decodeOperandDirectIndexedX(longw *operand, longw *address) {
    //address = 00:DP + byte_t + x, operand = mem[address]
    longw operandAddress = regfile->createFetchAddress(1);
    word directAddress = mem->readByte(operandAddress) + regfile->readX() + regfile->readDP();
    word op = mem->readWord(directAddress);

    *address = directAddress;
    *operand = op;
    implicitIncrement(2);    
}

void Decoder::decodeOperandDirectIndexedY(longw *operand, longw *address) {
    //address = 00:DP + byte_t + y, operand = mem[address]
    longw operandAddress = regfile->createFetchAddress(1);
    word directAddress = mem->readByte(operandAddress) + regfile->readY() + regfile->readDP();
    word op = mem->readWord(directAddress);

    *address = directAddress;
    *operand = op;
    implicitIncrement(2);    
}

void Decoder::decodeOperandDirectIndexedIndirect(longw *operand, longw *address) {
    //address = DB:mem[byte_t+DP+x], operand = mem[address]    
    longw operandAddress = regfile->createFetchAddress(1);
    word indirectAddress = mem->readByte(operandAddress) + regfile->readX() + regfile->readDP();
    word directBaseAddress = mem->readWord(indirectAddress);
    longw directAddress = regfile->createAbsoluteAddress(directBaseAddress);
    word op = mem->readWord(directAddress);

    *address = directAddress;
    *operand = op;
    implicitIncrement(2);
}

void Decoder::decodeOperandDirectIndirectIndexed(longw *operand, longw *address) {
    //address = (DB:mem[DP+byte_t])+y, operand = mem[address]
    longw operandAddress = regfile->createFetchAddress(1);
    word indirectAddress = mem->readByte(operandAddress) + regfile->readDP();
    word directBaseAddress = mem->readWord(indirectAddress);
    longw directAddress = regfile->createAbsoluteAddress(directBaseAddress) + regfile->readY();
    word op = mem->readWord(directAddress);

    *address = directAddress;
    *operand = op;
    implicitIncrement(2);
}

void Decoder::decodeOperandDirectIndirectLongIndexed(longw *operand, longw *address) {
    //address = mem[DP+byte_t]+y, operand = mem[address]
    longw operandAddress = regfile->createFetchAddress(1);
    word indirectAddress = mem->readByte(operandAddress) + regfile->readDP();
    longw directAddress = mem->readLong(indirectAddress) + regfile->readY();
    word op = mem->readWord(directAddress);

    *address = directAddress;
    *operand = op;
    implicitIncrement(2);
}

void Decoder::decodeOperandRelative(longw *operand, longw *address) {
    //address = PC + (signed byte_t) increment, operand = increment
    longw operandAddress = regfile->createFetchAddress(1);
    s_byte increment = mem->readByte(operandAddress);
    implicitIncrement(2);
    s_word incrementedAddress = (s_word) regfile->readPC() + (s_word) increment;

    *address = incrementedAddress;
    *operand = increment;
}

void Decoder::decodeOperandRelativeLong(longw *operand, longw *address) {
    //address = PC + (signed word) increment, operand = increment
    longw operandAddress = regfile->createFetchAddress(1);
    s_word increment = mem->readWord(operandAddress);
    implicitIncrement(3);
    s_word incrementedAddress = (s_word) regfile->readPC() + increment;

    *address = incrementedAddress;
    *operand = increment;
}

void Decoder::decodeOperandStackRelative(longw *operand, longw *address) {
    //address = 00:SP+byte_t, operand = mem[address]
    longw operandAddress = regfile->createFetchAddress(1);
    byte_t increment = mem->readByte(operandAddress);
    word relativeAddress = regfile->readSP() + increment;
    word op = mem->readWord(relativeAddress);

    *address = relativeAddress;
    *operand = op;
    implicitIncrement(2);
}

void Decoder::decodeOperandStackRelativeIndirectIndexed(longw *operand, longw *address) {
    //address = mem[00:regSP + byte_t]
    longw operandAddress = regfile->createFetchAddress(1);
    byte_t increment = mem->readByte(operandAddress);
    word relativeAddress = regfile->readSP() + increment;
    longw indexedAddress = (regfile->readDB() << 16) + mem->readWord(relativeAddress) + regfile->readY();
    word op = mem->readWord(indexedAddress);

    *address = indexedAddress;
    *operand = op;
    implicitIncrement(2);
}

void Decoder::decodeOperandBlockMove(longw *operand, longw *address) {
    //address = 0, operand = (dst << 8) | src

    longw operandAddress = regfile->createFetchAddress(1);
    byte_t dst = mem->readByte(operandAddress);
    operandAddress = regfile->createFetchAddress(2);
    byte_t src = mem->readByte(operandAddress);

    *address = 0;
    *operand = (dst << 8) | src;
    implicitIncrement(3);
}

void Decoder::decodeNoOperand(longw *operand, longw *address) {
    *address = 0;
    *operand = 0;
    implicitIncrement(1);
}

void Decoder::implicitIncrement(int increment) {
    word newPC = regfile->readPC() + increment;
    regfile->writePC(newPC);
}