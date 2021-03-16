#include "regfile.h"
using namespace std;


Regfile::Regfile() {
    SP = SP_INIT_VALUE;
    initP();
    X = Y = A = PB = DB = DP = 0;
}

Regfile *Regfile::regfile = nullptr;

Regfile *Regfile::getInstance() {
    if (regfile == nullptr) {
        regfile = new Regfile;
    }
    return regfile;
}

void Regfile::initPC(word value) {
    PC = value;
}

void Regfile::initP() {
    P.C = P.Z = P.V = P.N = P.D = P.E = P.B = 0;
    P.M = P.X = P.I = 1;
}

bool Regfile::isLargeA() {
    //If P.M == 0, A = 16 bits
    return (!P.M);
}

bool Regfile::isLargeIdx() {
    //If P.X == 0, X and Y = 16 bits
    return (!P.X);
}

////////////////////
// READ OPERATION //
////////////////////

word Regfile::readA() {
    if (isLargeA()) return A;
    else return A & 0x00ff;
}

word Regfile::readALarge() {
    return A;
}

word Regfile::readX() {
    if (isLargeIdx()) return X;
    else return X & 0x00ff;
}

word Regfile::readXLarge() {
    return X;
}

word Regfile::readY() {
    if (isLargeIdx()) return Y;
    else return Y & 0x00ff;
}

word Regfile::readYLarge() {
    return Y;
}

bool Regfile::readP(PFlags_t PFlag) {
    switch (PFlag) {
        case CARRY_FLAG:       return P.C; break;
        case ZERO_FLAG:        return P.Z; break;
        case OVERFLOW_FLAG:    return P.V; break;
        case NEGATIVE_FLAG:    return P.N; break;
        case DECIMAL_FLAG:     return P.D; break;
        case EMULATION_FLAG:   return P.E; break;
        case ACCUMULATOR_FLAG: return P.M; break;
        case INDEX_FLAG:       return P.X; break;
        case INTERRUPT_FLAG:    return P.I; break;
        default: return 0;
    }
}

byte_t Regfile::readPAll() {
    byte_t procStat;
    procStat =  
                ((P.N) << 7) |
	            ((P.V) << 6) |
	            ((P.M) << 5) |
	            ((P.X) << 4) |
	            ((P.D) << 3) |
	            ((P.I) << 2) |
	            ((P.Z) << 1) |
	            (P.C);
    return procStat;
}

word Regfile::readDP() {
    return DP;
}

word Regfile::readSP() {
    return SP;
}

word Regfile::readPC() {
    return PC;
}

byte_t Regfile::readPB() {
    return PB;
}

byte_t Regfile::readDB() {
    return DB;
}

longw Regfile::createFetchAddress(int offset) {
    //Creates a fetch address adding an offset
    word base = PC + offset;
    return ((PB << 16) | base);
}

longw Regfile::createAbsoluteAddress(word baseAddress) {
    //Creates an address usinb DB and a base address
    return ((DB << 16) | baseAddress);
}

//////////////////////
// WRITE OPERATIONS //
//////////////////////

void Regfile::writeA(word data) {
    if (isLargeA()) A = data;
    else A = (A & 0xff00) | (data & 0x00ff);
}

void Regfile::writeALarge(word data) {
    A = data;
}

void Regfile::writeX(word data) {
    if (isLargeIdx()) X = data;
    else X = data & 0x00ff;
}

void Regfile::writeY(word data) {
    if (isLargeIdx()) Y = data;
    else Y = data & 0x00ff;
}

void Regfile::writeP(PFlags_t PFlag, bool value) {
    switch (PFlag) {
        case CARRY_FLAG:       P.C = value; break;
        case ZERO_FLAG:        P.Z = value; break;
        case OVERFLOW_FLAG:    P.V = value; break;
        case NEGATIVE_FLAG:    P.N = value; break;
        case DECIMAL_FLAG:     P.D = value; break;
        case EMULATION_FLAG:   P.E = value; break;
        case ACCUMULATOR_FLAG: P.M = value; break;
        case INDEX_FLAG:       P.X = value; break;
        case INTERRUPT_FLAG:   P.I = value; break;
        default: return;
    }
}

void Regfile::writePAll(byte_t data) {
    P.N = (data >> 7) & 1;
    P.V = (data >> 6) & 1;
    P.M = (data >> 5) & 1;
    P.X = (data >> 4) & 1;
    P.D = (data >> 3) & 1;
    P.I = (data >> 2) & 1;
    P.Z = (data >> 1) & 1;
    P.C = data & 1;
}

void Regfile::writeDP(word data) {
    DP = data;
}

void Regfile::writeSP(word data) {
    SP = data;
}

void Regfile::writePC(word data) {
    PC = data;
}

void Regfile::writePB(byte_t data) {
    PB = data;
}

void Regfile::writeDB(byte_t data) {
    DB = data;
}