#include "regfile.h"
using namespace std;


Regfile::Regfile() {
    SP = SP_INIT_VALUE;
    initP();
    X = Y = A = PB = DB = DP = 0;
}

Regfile *Regfile::getInstance() {
    if (regfile == nullptr) {
        regfile = new Regfile;
    }
    return regfile;
}

void Regfile::initP() {
    P.C = P.Z = P.V = P.N = P.D = P.E = 0;
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
    if (isLargeA()) return (A & 0x00ff);
    else return A;
}

word Regfile::readX() {
    return X;
}

word Regfile::readY() {
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

word Regfile::readDP() {
    return DP;
}

word Regfile::readSP() {
    return SP;
}

word Regfile::readPC() {
    return PC;
}

byte Regfile::readPB() {
    return PB;
}

byte Regfile::readDB() {
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

void Regfile::writeX(word data) {
    if (isLargeIdx()) X = data;
    else X = data & 0x00ff;
}

void Regfile::writeY(word data) {
    if (isLargeIdx()) Y = data;
    else Y = data & 0x00ff;
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

void Regfile::writePB(byte data) {
    PB = data;
}

void Regfile::writeDB(byte data) {
    DB = data;
}