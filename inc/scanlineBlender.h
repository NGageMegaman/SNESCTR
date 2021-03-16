#include "defines.h"
#include "ppuParams.h"
#include "backgroundParams.h"
#include "scanline.h"
#pragma once
using namespace std;

class ScanlineBlender {
    protected:
        ScanlineBlender();
        static ScanlineBlender *scanlineBlender;
    public:
        static ScanlineBlender *getInstance();
        Scanline blendScanlines(Scanline *layers);
    private:
        Scanline blendMode0(Scanline *layers);
        Scanline blendMode1(Scanline *layers);
        Scanline blendMode2(Scanline *layers);
        Scanline blendMode3(Scanline *layers);
        Scanline blendMode4(Scanline *layers);
        Scanline blendMode5(Scanline *layers);
        Scanline blendMode6(Scanline *layers);
        longw applyBrightness(longw bgr);

        BackgroundParams *backgroundParams;
        PpuParams *ppuParams;
};