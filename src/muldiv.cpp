#include "muldiv.h"
using namespace std;

Muldiv::Muldiv() {
    mulA = 0xff;
    mulB = 0;
    dividend = 0xffff;
    divisor = 0;
    mulResDivRem = 0;
    quotient = 0;
}

Muldiv *Muldiv::muldiv = nullptr;

Muldiv *Muldiv::getInstance() {
    if (muldiv == nullptr) {
        muldiv = new Muldiv();
    }
    return muldiv;
}

void Muldiv::writeWRMPYA(byte_t data) {
    mulA = data;
}

void Muldiv::writeWRMPYB(byte_t data) {
    mulB = data;
    mulResDivRem = mulA * mulB;
}

void Muldiv::writeWRDIVL(byte_t data) {
    dividend = (dividend & 0xff00) | data;
}

void Muldiv::writeWRDIVH(byte_t data) {
    dividend = (dividend & 0x00ff) | (data << 8);
}

void Muldiv::writeWRDIVB(byte_t data) {
    divisor = data;
    if (divisor == 0) {
        quotient = 0xffff;
        mulResDivRem = dividend;
    }
    else {
        quotient = dividend/divisor;
        mulResDivRem = dividend%divisor;
    }
}

byte_t Muldiv::readRDDIVL() {
    return (quotient & 0x00ff);
}

byte_t Muldiv::readRDDIVH() {
    return ((quotient & 0xff00) >> 8);
}

byte_t Muldiv::readRDMPYL() {
    return (mulResDivRem & 0x00ff);
}

byte_t Muldiv::readRDMPYH() {
    return ((mulResDivRem & 0xff00) >> 8);
}