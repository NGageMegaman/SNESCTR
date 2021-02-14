#include "ppuParams.h"
using namespace std;

PpuParams::PpuParams() {

}

PpuParams *PpuParams::ppuParams = nullptr;

PpuParams *PpuParams::getInstance() {
    if (ppuParams == nullptr) {
        ppuParams = new PpuParams();
    }
    return ppuParams;
}

void PpuParams::writeINIDISP(byte_t data) {
    brightness = data & 0x0f;
    FBlank = (data >> 7) & 1;
}

byte_t PpuParams::getBrightness() {
    return brightness;
}

bool PpuParams::getFBlank() {
    return FBlank;
}