#include "arithlogicUnit.h"
using namespace std;

ArithlogicUnit::ArithlogicUnit() {
    procFlagUnit = ProcFlagUnit::getInstance();
    regfile = Regfile::getInstance();
    mem = Mem::getInstance();
}

ArithlogicUnit *ArithlogicUnit::arithlogicUnit = nullptr;

ArithlogicUnit *ArithlogicUnit::getInstance() {
    if (arithlogicUnit == nullptr) {
        arithlogicUnit = new ArithlogicUnit();
    }
    return arithlogicUnit;
}

void ArithlogicUnit::ADC(longw operand, longw address) {
    //Add with carry
    bool signResult, signA, signOperand;
    bool isCarry = false;

    word result_part = regfile->readA() + operand;
    if (!regfile->isLargeA()) result_part &= 0x00ff;
    if (result_part < regfile->readA()) isCarry = true;

    word result = result_part + regfile->readP(PFlags_t::CARRY_FLAG);
    if (!regfile->isLargeA()) result &= 0x00ff;
    if (result < regfile->readA()) isCarry = true;

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->overflowFlagADC(operand, result);
    procFlagUnit->negativeFlagA(result);
    regfile->writeA(result);
    regfile->writeP(PFlags_t::CARRY_FLAG, isCarry);
}

void ArithlogicUnit::AND(longw operand, longw address) {
    //AND
    word result = regfile->readA() & operand;
    regfile->writeA(result);

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
}

void ArithlogicUnit::ASL_A(longw operand, longw address) {
    //Arithmetic Shift Left (Accum)
    longw result = regfile->readA() << 1;
    regfile->writeA(result);

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->carryFlagA(result);
    procFlagUnit->negativeFlagA(result);
}

void ArithlogicUnit::ASL_mem(longw operand, longw address) {
    //Arithmetic Shift Left (memory)
    longw result = operand << 1;
    if (regfile->isLargeA()) mem->writeWord(address, result);
    else mem->writeByte(address, result);

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->carryFlagA(result);
    procFlagUnit->negativeFlagA(result);
}

void ArithlogicUnit::CMP(longw operand, longw address) {
    //Compare A register
    word comp = regfile->readA() - operand;

    procFlagUnit->zeroFlagA(comp);
    procFlagUnit->carryFlagCMP(regfile->readA(), operand, regfile->isLargeA());
    procFlagUnit->negativeFlagA(comp);
}

void ArithlogicUnit::CPX(longw operand, longw address) {
    //Compare X register
    word comp = regfile->readX() - operand;

    procFlagUnit->zeroFlagX(comp);
    procFlagUnit->carryFlagCMP(regfile->readX(), operand, regfile->isLargeIdx());
    procFlagUnit->negativeFlagX(comp);
}

void ArithlogicUnit::CPY(longw operand, longw address) {
    //Compare Y register
    word comp = regfile->readY() - operand;

    procFlagUnit->zeroFlagX(comp);
    procFlagUnit->carryFlagCMP(regfile->readY(), operand, regfile->isLargeIdx());
    procFlagUnit->negativeFlagX(comp);
}

void ArithlogicUnit::DEC_A(longw operand, longw address) {
    //Decrement A
    word result = regfile->readA()-1;
    regfile->writeA(result);

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
}

void ArithlogicUnit::DEC_mem(longw operand, longw address) {
    //Decrement memory
    word result = operand-1;
    if (regfile->isLargeA()) mem->writeWord(address, result);
    else mem->writeByte(address, result);

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
}

void ArithlogicUnit::DEX(longw operand, longw address) {
    //Decrement X
    word result = regfile->readX()-1;
    regfile->writeX(result);

    procFlagUnit->zeroFlagX(result);
    procFlagUnit->negativeFlagX(result);
}

void ArithlogicUnit::DEY(longw operand, longw address) {
    //Decrement Y
    word result = regfile->readY()-1;
    regfile->writeY(result);

    procFlagUnit->zeroFlagX(result);
    procFlagUnit->negativeFlagX(result);
}

void ArithlogicUnit::EOR(longw operand, longw address) {
    //XOR
    word result = regfile->readA() ^ operand;
    regfile->writeA(result);

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
}

void ArithlogicUnit::INC_A(longw operand, longw address) {
    //Increment A
    word result = regfile->readA()+1;
    regfile->writeA(result);

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
}

void ArithlogicUnit::INC_mem(longw operand, longw address) {
    //Increment memory
    word result = operand+1;
    if (regfile->isLargeA()) mem->writeWord(address, result);
    else mem->writeByte(address, result);

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
}

void ArithlogicUnit::INX(longw operand, longw address) {
    //Increment X
    word result = regfile->readX()+1;
    regfile->writeX(result);

    procFlagUnit->zeroFlagX(result);
    procFlagUnit->negativeFlagX(result);
}

void ArithlogicUnit::INY(longw operand, longw address) {
    //Increment Y
    word result = regfile->readY()+1;
    regfile->writeY(result);

    procFlagUnit->zeroFlagX(result);
    procFlagUnit->negativeFlagX(result);
}

void ArithlogicUnit::LSR_A(longw operand, longw address) {
    //Logical shift right A
    word result;
    if (regfile->isLargeA()) result = (regfile->readA() >> 1) & 0x7fff;
    else result = (regfile->readA() >> 1) & 0x007f;

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
    regfile->writeP(PFlags_t::CARRY_FLAG, regfile->readA() & 1);
    regfile->writeA(result);
}

void ArithlogicUnit::LSR_mem(longw operand, longw address) {
    //Logical shift right memory
    word result;
    if (regfile->isLargeA()) {
        result = (operand >> 1) & 0x7fff;
        mem->writeWord(address, operand);
    }
    else {
        result = (operand >> 1) & 0x007f;
        mem->writeByte(address, operand);
    }

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
    regfile->writeP(PFlags_t::CARRY_FLAG, operand & 1);
}

void ArithlogicUnit::ORA(longw operand, longw address) {
    //OR
    word result = regfile->readA() | operand;
    regfile->writeA(result);

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
}

void ArithlogicUnit::ROL_A(longw operand, longw address) {
    //Rotate Left A
    longw result = (regfile->readA() << 1) | regfile->readP(PFlags_t::CARRY_FLAG);
    regfile->writeA(result);

    procFlagUnit->carryFlagA(result);
    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
}

void ArithlogicUnit::ROL_mem(longw operand, longw address) {
    //Rotate Left memory
    longw result = (operand << 1) | regfile->readP(PFlags_t::CARRY_FLAG);
    if (regfile->isLargeA()) mem->writeWord(address, result);
    else mem->writeByte(address, result);

    procFlagUnit->carryFlagA(result);
    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
}

void ArithlogicUnit::ROR_A(longw operand, longw address) {
    //Rotate Right A
    word result;

    if (regfile->isLargeA()) {
       result = ((regfile->readA() >> 1) & 0x7fff) | (regfile->readP(PFlags_t::CARRY_FLAG) << 15); 
    }
    else {
       result = ((regfile->readA() >> 1) & 0x007f) | (regfile->readP(PFlags_t::CARRY_FLAG) << 7); 
    }

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
    regfile->writeP(PFlags_t::CARRY_FLAG, regfile->readA() & 1);

    regfile->writeA(result);
}

void ArithlogicUnit::ROR_mem(longw operand, longw address) {
    //Rotate Right memory
    word result;

    if (regfile->isLargeA()) {
       result = ((operand >> 1) & 0x7fff) | (regfile->readP(PFlags_t::CARRY_FLAG) << 15); 
       mem->writeWord(address, result);
    }
    else {
       result = ((regfile->readA() >> 1) & 0x007f) | (regfile->readP(PFlags_t::CARRY_FLAG) << 7); 
       mem->writeByte(address, result);
    }

    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(result);
    regfile->writeP(PFlags_t::CARRY_FLAG, operand & 1);
}

void ArithlogicUnit::SBC(longw operand, longw address) {
    //Subtract with carry
    //This is equivalent to ADC with ~operand

    longw noperand = ~operand;
    ADC(noperand, address);
}