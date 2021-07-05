#include "procStatUnit.h"
using namespace std;

ProcStatUnit::ProcStatUnit() {
    regfile = Regfile::getInstance();
    mem = Mem::getInstance();
    procFlagUnit = ProcFlagUnit::getInstance();
}

ProcStatUnit *ProcStatUnit::procStatUnit = nullptr;

ProcStatUnit *ProcStatUnit::getInstance() {
    if (procStatUnit == nullptr) {
        procStatUnit = new ProcStatUnit();
    }
    return procStatUnit;
}

void ProcStatUnit::BIT(longw operand, longw address) {
    //Bit Test
    word result = regfile->readA() & operand;
    procFlagUnit->zeroFlagA(result);
    procFlagUnit->negativeFlagA(operand);
    if (regfile->isLargeA()) {
        regfile->writeP(PFlags_t::OVERFLOW_FLAG, (operand >> 14) & 1);
    }
    else regfile->writeP(PFlags_t::OVERFLOW_FLAG, (operand >> 6) & 1);
}

void ProcStatUnit::BIT_imm(longw operand, longw address) {
    //Bit Test with immediate
    word result = regfile->readA() & operand;
    procFlagUnit->zeroFlagA(result);
}

void ProcStatUnit::BRK(longw operand, longw address) {
    //Force interrupt
    byte_t PC_l = regfile->readPC();
    byte_t PC_h = regfile->readPC() >> 8;
    byte_t procStat = regfile->readPAll();

    if (!regfile->readP(PFlags_t::EMULATION_FLAG)) {
        mem->pushStack(regfile->readPB());
    }
    mem->pushStack(PC_h);
    mem->pushStack(PC_l);
    mem->pushStack(procStat);
    if (!regfile->readP(PFlags_t::EMULATION_FLAG)) {
        mem->pushStack(regfile->readPB());
        regfile->writePC(mem->readWord(BRK_VECTOR));
    }
    else {
        regfile->writePC(mem->readWord(BRK_IRQ_VECTOR_E));
        regfile->writeP(PFlags_t::BREAKPOINT_FLAG, true);
    }
    regfile->writePB(0);
    regfile->writeP(PFlags_t::DECIMAL_FLAG, false);
    regfile->writeP(PFlags_t::INTERRUPT_FLAG, true);
}

void ProcStatUnit::COP(longw operand, longw address) {
    //Coprocessor enable
    byte_t PC_l = regfile->readPC();
    byte_t PC_h = regfile->readPC() >> 8;
    byte_t procStat = regfile->readPAll();

    mem->pushStack(PC_h);
    mem->pushStack(PC_l);
    mem->pushStack(procStat);
    if (!regfile->readP(PFlags_t::EMULATION_FLAG)) {
        mem->pushStack(regfile->readPB());
        regfile->writePC(mem->readWord(COP_VECTOR));
    }
    else {
        regfile->writePC(mem->readWord(COP_VECTOR_E));
    }
    regfile->writePB(0);
    regfile->writeP(PFlags_t::DECIMAL_FLAG, false);
    regfile->writeP(PFlags_t::INTERRUPT_FLAG, true);
}

void ProcStatUnit::CLC(longw operand, longw address) {
    //Clear Carry flag
    regfile->writeP(PFlags_t::CARRY_FLAG, false);
}

void ProcStatUnit::CLD(longw operand, longw address) {
    //Clear Decimal flag
    regfile->writeP(PFlags_t::DECIMAL_FLAG, false);
}

void ProcStatUnit::CLI(longw operand, longw address) {
    //Clear Interrupt disable flag
    regfile->writeP(PFlags_t::INTERRUPT_FLAG, false);
}

void ProcStatUnit::CLV(longw operand, longw address) {
    //Clear Overflow flag
    regfile->writeP(PFlags_t::OVERFLOW_FLAG, false);
}

void ProcStatUnit::REP(longw operand, longw address) {
    //Reset status bits
    byte_t noperand = ~operand;
    byte_t procStat = regfile->readPAll();
    byte_t result = procStat & noperand;
    regfile->writePAll(result);
    if (regfile->readP(PFlags_t::EMULATION_FLAG)) {
        regfile->writeP(PFlags_t::INDEX_FLAG, true);
        regfile->writeP(PFlags_t::ACCUMULATOR_FLAG, true);
    }
}

void ProcStatUnit::SEC(longw operand, longw address) {
    //Set Carry flag
    regfile->writeP(PFlags_t::CARRY_FLAG, true);
}

void ProcStatUnit::SED(longw operand, longw address) {
    //Set Decimal flag
    regfile->writeP(PFlags_t::DECIMAL_FLAG, true);
}

void ProcStatUnit::SEI(longw operand, longw address) {
    //Set Interrupt disable flag
    regfile->writeP(PFlags_t::INTERRUPT_FLAG, true);
}

void ProcStatUnit::SEP(longw operand, longw address) {
    //Set Processor status bits
    byte_t procStat = regfile->readPAll();
    byte_t result = procStat | operand;
    regfile->writePAll(result);
}

void ProcStatUnit::STP(longw operand, longw address) {
    //Stop the Processor
    while (1);
}

void ProcStatUnit::TAX(longw operand, longw address) {
    //Transfer A to X
    regfile->writeX(regfile->readALarge());
    procFlagUnit->zeroFlagX(regfile->readX());
    procFlagUnit->negativeFlagX(regfile->readX());
}

void ProcStatUnit::TAY(longw operand, longw address) {
    //Transfer A to Y
    regfile->writeY(regfile->readALarge());
    procFlagUnit->zeroFlagX(regfile->readY());
    procFlagUnit->negativeFlagX(regfile->readY());
}

void ProcStatUnit::TCD(longw operand, longw address) {
    //Transfer A to DP
    regfile->writeDP(regfile->readALarge());
    procFlagUnit->zeroFlag(regfile->readDP());
    procFlagUnit->negativeFlagLarge(regfile->readDP());
}

void ProcStatUnit::TCS(longw operand, longw address) {
    //Transfer A to SP
    regfile->writeSP(regfile->readALarge());
    if (regfile->readP(PFlags_t::EMULATION_FLAG)) {
        //If emulation mode, high byte = 01, only 8 bits transfer
        regfile->writeSP(0x0100 | (regfile->readSP() & 0x00ff));
    }
}

void ProcStatUnit::TDC(longw operand, longw address) {
    //Transfer DP to A
    regfile->writeALarge(regfile->readDP());
    //POSSIBLE BUG? MAYBE THIS DEPENDS ON ACCUM FLAG
    procFlagUnit->zeroFlag(regfile->readALarge());
    procFlagUnit->negativeFlagLarge(regfile->readALarge());
}

void ProcStatUnit::TSC(longw operand, longw address) {
    //Transfer SP to A
    regfile->writeALarge(regfile->readSP());
    //POSSIBLE BUG? MAYBE THIS DEPENDS ON ACCUM FLAG
    procFlagUnit->zeroFlag(regfile->readALarge());
    procFlagUnit->negativeFlagLarge(regfile->readALarge());
}

void ProcStatUnit::TSX(longw operand, longw address) {
    //Transfer SP to X
    regfile->writeX(regfile->readSP());
    procFlagUnit->zeroFlagX(regfile->readX());
    procFlagUnit->negativeFlagX(regfile->readX());
}

void ProcStatUnit::TXA(longw operand, longw address) {
    //Transfer X to A
    regfile->writeA(regfile->readX());
    procFlagUnit->zeroFlagA(regfile->readA());
    procFlagUnit->negativeFlagA(regfile->readA());
}

void ProcStatUnit::TXS(longw operand, longw address) {
    //Transfer X to SP
    regfile->writeSP(regfile->readXLarge());
    if (regfile->readP(PFlags_t::EMULATION_FLAG)) {
        //If emulation mode, high byte = 01, only 8 bits transfer
        regfile->writeSP(0x0100 | (regfile->readSP() & 0x00ff));
    }
}

void ProcStatUnit::TXY(longw operand, longw address) {
    //Transfer X to Y
    regfile->writeY(regfile->readX());
    procFlagUnit->zeroFlagX(regfile->readY());
    procFlagUnit->negativeFlagX(regfile->readY());
}

void ProcStatUnit::TYA(longw operand, longw address) {
    //Transfer Y to A
    regfile->writeA(regfile->readY());
    procFlagUnit->zeroFlagA(regfile->readA());
    procFlagUnit->negativeFlagA(regfile->readA());
}

void ProcStatUnit::TYX(longw operand, longw address) {
    //Transfer Y to X
    regfile->writeX(regfile->readY());
    procFlagUnit->zeroFlagX(regfile->readX());
    procFlagUnit->negativeFlagX(regfile->readX());
}

void ProcStatUnit::WAI(longw operand, longw address) {
    //Wait for interrupt
    //TBI, WE MUST WAIT FOR RDY PIN
    return;
}

void ProcStatUnit::WDM(longw operand, longw address) {
    //RESERVED, DOES NOTHING
    return;
}

void ProcStatUnit::XBA(longw operand, longw address) {
    //Exchange the B and A accumulators
    word BA = regfile->readALarge();
    word AB = ((BA << 8) & 0xff00) | (BA >> 8);
    regfile->writeALarge(AB);
    procFlagUnit->zeroFlag(AB & 0x00ff);
    procFlagUnit->negativeFlag(AB & 0x00ff);
}

void ProcStatUnit::XCE(longw operand, longw address) {
    //Exchange carry and emulation bits

    bool newC = regfile->readP(PFlags_t::EMULATION_FLAG);
    bool newE = regfile->readP(PFlags_t::CARRY_FLAG);
    regfile->writeP(PFlags_t::CARRY_FLAG, newC);
    regfile->writeP(PFlags_t::EMULATION_FLAG, newE);
    if (newE) {
        regfile->writeP(PFlags_t::ACCUMULATOR_FLAG, true);
        regfile->writeP(PFlags_t::INDEX_FLAG, true);
    }
}

void ProcStatUnit::NMI() {
    //Non-Maskable interrupt
    byte_t PC_l = regfile->readPC();
    byte_t PC_h = regfile->readPC() >> 8;
    byte_t procStat = regfile->readPAll();
    //cout << "NMI: PCprev = " << std::hex << (int) PC_h << std::hex << (int) PC_l << endl;
    //cout << "GAMEMODE = " << std::hex << (int) mem->readByte(0x7e0100) << endl;

    if (!regfile->readP(PFlags_t::EMULATION_FLAG)) {
        mem->pushStack(regfile->readPB());
    }
    mem->pushStack(PC_h);
    mem->pushStack(PC_l);
    mem->pushStack(procStat);
    if (!regfile->readP(PFlags_t::EMULATION_FLAG)) {
        regfile->writePC(mem->readWord(NMI_VECTOR));
    }
    else {
        regfile->writePC(mem->readWord(NMI_VECTOR_E));
    }

}

void ProcStatUnit::NOP(longw operand, longw address) {
    //No Operation
    return;
}