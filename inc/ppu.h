#include "defines.h"
#include "scanlineRenderer.h"
#include "scanlineBlender.h"
#include "app.h"
#pragma once
using namespace std;

class PPU {
    protected:
        PPU();
        static PPU *ppu;
    public:
        static PPU *getInstance();
        Scanline HBlank(int line);
    private:
        Scanline layers[5];
        ScanlineRenderer *scanlineRenderer;
        ScanlineBlender *scanlineBlender;
        App *app;
};