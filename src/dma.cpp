#include "dma.h"
#include "mem.h"
using namespace std;

DMA::DMA() {
    for (int i = 0; i<8; ++i) {
        transferBA[i] = 0;
        addressIncrement[i] = 0;
        fixedTransfer[i] = 0;
        transferMode[i] = 0;
        addressA[i] = 0;
        addressB[i] = 0;
        size[i] = 0;
    }
}

DMA *DMA::dma = nullptr;

DMA *DMA::getInstance(Mem *memInstance) {
    if (dma == nullptr) {
        dma = new DMA();
    }
    dma->mem = memInstance;
    return dma;
}

void DMA::writeMDMA(byte_t data) {
    for (int i = 0; i<8; ++i) {
        bool channelEnable = (data >> i) & 1;
        if (channelEnable) {
            dmaEnable(i);
        }
    }
}

void DMA::writeDMAPx(byte_t data, byte_t channel) {
    transferBA[channel]       = (data >> 7) & 1;
    addressIncrement[channel] = (data >> 4) & 1;
    fixedTransfer[channel]    = (data >> 3) & 1;
    transferMode[channel]     = data & 0x07;
}

void DMA::writeBBADx(byte_t data, byte_t channel) {
    //$00:2100 ~ $00:21ff
    addressB[channel] = 0x002100 | data;
}

void DMA::writeA1TxL(byte_t data, byte_t channel) {
    addressA[channel] = (addressA[channel] & 0xffff00) | data;
}

void DMA::writeA1TxH(byte_t data, byte_t channel) {
    addressA[channel] = (addressA[channel] & 0xff00ff) | (data << 8);
}

void DMA::writeA1Bx(byte_t data, byte_t channel) {
    addressA[channel] = (addressA[channel] & 0x00ffff) | (data << 16);
}

void DMA::writeDASxL(byte_t data, byte_t channel) {
    size[channel] = (size[channel] & 0xff00) | data;
}

void DMA::writeDASxH(byte_t data, byte_t channel) {
    size[channel] = (size[channel] & 0x00ff) | (data << 8);
}

byte_t DMA::readDMAPx(byte_t channel) {
    byte_t result;
    result = transferBA[channel]       << 7 |
             addressIncrement[channel] << 4 |
             fixedTransfer[channel]    << 3 |
             transferMode[channel];
    return result;
}

byte_t DMA::readBBADx(byte_t channel) {
    return addressB[channel];
}

byte_t DMA::readA1TxL(byte_t channel) {
    return (addressA[channel] & 0x0000ff);
}

byte_t DMA::readA1TxH(byte_t channel) {
    return ((addressA[channel] & 0x00ff00) >> 8);
}

byte_t DMA::readA1Bx(byte_t channel) {
    return ((addressA[channel] & 0xff0000) >> 16);
}

byte_t DMA::readDASxL(byte_t channel) {
    return (size[channel] & 0x00ff);
}

byte_t DMA::readDASxH(byte_t channel) {
    return ((size[channel] & 0xff00) >> 8);
}

void DMA::dmaEnable(byte_t channel) {
    longw A, B;
    word bytesLeft = size[channel];
    word bytes = 0;
    bool direction = transferBA[channel];
    do {
        A = addressA[channel];
        B = addressB[channel];
        switch (transferMode[channel]) {
            case 0b001: case 0b101:
                // B0 -> r0, B1 -> r1
                B += (bytes % 2);
                break;
            case 0b011: case 0b111:
                // B0 -> r0, B1 -> r0, B2 -> r1, B3 -> r1
                B += ((bytes % 4 ) / 2);
                break;
            case 0b100:
                // B0 -> r0, B1 -> r1, B2 -> r2, B3 -> r3
                B += (bytes % 4);
                break;
        }
        transfer(A, B, direction);
        if (!fixedTransfer[channel]) {
            if (!addressIncrement[channel]) addressA[channel]++;
            else addressA[channel]--;
        }
        bytesLeft--;
        bytes++;
    } while (bytesLeft != 0);
    size[channel] = 0;
}

void DMA::transfer(longw A, longw B, bool BtoA) {
    if (BtoA) {
        mem->writeByte(A, mem->readByte(B));
    }
    else {
        mem->writeByte(B, mem->readByte(A));
        //cout << std::hex << "DMA: " << A << " " << B << " " << (int) mem->readByte(A) << endl;
    }
}