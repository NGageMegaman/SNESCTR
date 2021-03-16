#include "procFlagUnit.h"
using namespace std;

ProcFlagUnit::ProcFlagUnit() {
    regfile = Regfile::getInstance();
}

ProcFlagUnit *ProcFlagUnit::procFlagUnit = nullptr;

ProcFlagUnit *ProcFlagUnit::getInstance() {
    if (procFlagUnit == nullptr) {
        procFlagUnit = new ProcFlagUnit;
    }
    return procFlagUnit;
}

void ProcFlagUnit::zeroFlag(longw data) {
    PFlags_t flag = PFlags_t::ZERO_FLAG;
    if (data == 0) regfile->writeP(flag, true);
    else regfile->writeP(flag, false);
}

void ProcFlagUnit::zeroFlagA(longw data) {
    PFlags_t flag = PFlags_t::ZERO_FLAG;
    if (regfile->isLargeA()) {
        if ((word) data == 0) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
    else {
        if ((byte_t) data == 0) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
}

void ProcFlagUnit::zeroFlagX(longw data) {
    PFlags_t flag = PFlags_t::ZERO_FLAG;
    if (regfile->isLargeIdx()) {
        if ((word) data == 0) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
    else {
        if ((byte_t) data == 0) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
}

void ProcFlagUnit::negativeFlag(longw data) {
    PFlags_t flag = PFlags_t::NEGATIVE_FLAG;
    if ((data >> 7) & 1 == 1) regfile->writeP(flag, true);
    else regfile->writeP(flag, false);
}

void ProcFlagUnit::negativeFlagLarge(longw data) {
    PFlags_t flag = PFlags_t::NEGATIVE_FLAG;
    if ((data >> 15) & 1 == 1) regfile->writeP(flag, true);
    else regfile->writeP(flag, false);
}

void ProcFlagUnit::negativeFlagA(longw data) {
    PFlags_t flag = PFlags_t::NEGATIVE_FLAG;
    if (regfile->isLargeA()) {
        if ((data >> 15) & 1 == 1) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
    else {
        if ((data >> 7) & 1 == 1) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
}

void ProcFlagUnit::negativeFlagX(longw data) {
    PFlags_t flag = PFlags_t::NEGATIVE_FLAG;
    if (regfile->isLargeIdx()) {
        if ((data >> 15) & 1 == 1) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
    else {
        if ((data >> 7) & 1 == 1) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
}

void ProcFlagUnit::carryFlagA(longw data) {
    PFlags_t flag = PFlags_t::CARRY_FLAG;
    if (regfile->isLargeA()) {
        if ((data >> 16) & 1 == 1) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
    else {
        if ((data >> 8) & 1 == 1) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
}

void ProcFlagUnit::carryFlagX(longw data) {
    PFlags_t flag = PFlags_t::CARRY_FLAG;
    if (regfile->isLargeIdx()) {
        if ((data >> 16) & 1 == 1) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
    else {
        if ((data >> 8) & 1 == 1) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
}

void ProcFlagUnit::carryFlagCMP(longw reg, longw data, bool large) {
    PFlags_t flag = PFlags_t::CARRY_FLAG;
    if (large) {
        if (reg >= (word) data) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
    else {
        if (reg >= (byte_t) data) regfile->writeP(flag, true);
        else regfile->writeP(flag, false);
    }
}

void ProcFlagUnit::overflowFlagADC(longw operand, longw result) {
    PFlags_t flag = PFlags_t::OVERFLOW_FLAG;
    bool signResult, signA, signOperand;
    byte_t shiftAmount;
    if (regfile->isLargeA()) shiftAmount = 15;
    else shiftAmount = 7;
    signResult  = (result           >> shiftAmount) & 1;
    signA       = (regfile->readA() >> shiftAmount) & 1;
    signOperand = (operand          >> shiftAmount) & 1;
    if ((signA == signOperand) && (signResult != signA)) {
        regfile->writeP(flag, true);
    }
    else regfile->writeP(flag, false);
}