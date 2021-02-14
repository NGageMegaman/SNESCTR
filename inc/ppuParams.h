#include "defines.h"
#pragma once
using namespace std;

class PpuParams {
    protected:
        PpuParams();
        static PpuParams *ppuParams;
    public:
        static PpuParams *getInstance();
        void writeINIDISP(byte_t data);
        byte_t getBrightness();
        bool getFBlank();
    private:
        byte_t brightness;
        bool FBlank;
};