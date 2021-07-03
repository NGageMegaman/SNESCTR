#include "ppu.h"
using namespace std;

PPU::PPU() {
    oam = OAM::getInstance();
    scanlineRenderer = ScanlineRenderer::getInstance();
    scanlineBlender = ScanlineBlender::getInstance();
    app = App::getInstance();
    for (int i = 0; i<5; ++i) {
        layers[i] = *(new Scanline());
    }
}

PPU *PPU::ppu = nullptr;

PPU *PPU::getInstance() {
    if (ppu == nullptr) {
        ppu = new PPU();
    }
    return ppu;
}

Scanline PPU::HBlank(int line) {
    for (int i = 1; i<5; ++i) {
        layers[i-1] = scanlineRenderer->getScanline(line, i, layers[i-1]);
    }
    layers[4] = scanlineRenderer->getOBJScanline(line);
    Scanline scanline = scanlineBlender->blendScanlines(layers);
    //Scanline scanline = scanlineRenderer->getScanline(line, 1);
    return scanline;
}

void PPU::VBlank() {
    oam->invalidateAddress();
}