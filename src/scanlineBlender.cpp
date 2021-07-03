#include "scanlineBlender.h"
using namespace std;

ScanlineBlender::ScanlineBlender() {
    backgroundParams = BackgroundParams::getInstance();
    ppuParams = PpuParams::getInstance();
}

ScanlineBlender *ScanlineBlender::scanlineBlender = nullptr;

ScanlineBlender *ScanlineBlender::getInstance() {
    if (scanlineBlender == nullptr) {
        scanlineBlender = new ScanlineBlender();
    }
    return scanlineBlender;
}

Scanline ScanlineBlender::blendScanlines(Scanline *layers) {
    static Scanline scanline;
    byte_t mode = backgroundParams->getBGMode();
    switch (mode) {
        case 0: scanline = blendMode0(layers); break;
        case 1: scanline = blendMode1(layers); break;
        case 2: scanline = blendMode2(layers); break;
        case 3: scanline = blendMode3(layers); break;
        case 4: scanline = blendMode4(layers); break;
        case 5: scanline = blendMode5(layers); break;
        case 6: scanline = blendMode6(layers); break;
    }
    return scanline;
}

////////////////////////////
// MISSING FEATURES:
//
// - Main and Sub screens
// - Color math
// - Sprites
////////////////////////////

Scanline ScanlineBlender::blendMode0(Scanline *layers) {
    Scanline scanline;
    longw c1, c2, c3, c4, co, c;
    byte_t p1, p2, p3, p4, po;
    for (int i = 0; i<256; ++i) {
        c1 = layers[0].getPixel(i).getBGRColor();
        c2 = layers[1].getPixel(i).getBGRColor();
        c3 = layers[2].getPixel(i).getBGRColor();
        c4 = layers[3].getPixel(i).getBGRColor();
        co = layers[4].getPixel(i).getBGRColor();
        p1 = layers[0].getPixel(i).getPriority();
        p2 = layers[1].getPixel(i).getPriority();
        p3 = layers[2].getPixel(i).getPriority();
        p4 = layers[3].getPixel(i).getPriority();
        po = layers[4].getPixel(i).getPriority();
        if (co != COLOR_TRANSPARENT && po == 3) {
            c = co;
        }
        else if (c1 != COLOR_TRANSPARENT && p1) {
            c = c1;
        }
        else if (c2 != COLOR_TRANSPARENT && p2) {
            c = c2;
        }
        else if (co != COLOR_TRANSPARENT && po == 2) {
            c = co;
        }
        else if (c1 != COLOR_TRANSPARENT && !p1) {
            c = c1;
        }
        else if (c2 != COLOR_TRANSPARENT && !p2) {
            c = c2;
        }
        else if (co != COLOR_TRANSPARENT && po == 1) {
            c = co;
        }
        else if (c3 != COLOR_TRANSPARENT && p3) {
            c = c3;
        }
        else if (c4 != COLOR_TRANSPARENT && p4) {
            c = c4;
        }
        else if (co != COLOR_TRANSPARENT && po == 0) {
            c = co;
        }
        else if (c3 != COLOR_TRANSPARENT && !p3) {
            c = c3;
        }
        else if (c4 != COLOR_TRANSPARENT && !p4) {
            c = c4;
        }
        else c = 0;
        scanline.setPixelColor(i, applyBrightness(c));
    }
    return scanline;
}

Scanline ScanlineBlender::blendMode1(Scanline *layers) {
    Scanline scanline;
    longw c1, c2, c3, co, c;
    byte_t p1, p2, p3, po;
    bool prio3 = backgroundParams->isM1BG3priority();
    for (int i = 0; i<256; ++i) {
        c1 = layers[0].getPixel(i).getBGRColor();
        c2 = layers[1].getPixel(i).getBGRColor();
        c3 = layers[2].getPixel(i).getBGRColor();
        co = layers[4].getPixel(i).getBGRColor();
        p1 = layers[0].getPixel(i).getPriority();
        p2 = layers[1].getPixel(i).getPriority();
        p3 = layers[2].getPixel(i).getPriority();
        po = layers[4].getPixel(i).getPriority();
        if (c3 != COLOR_TRANSPARENT && p3 == 1 && prio3 == 1) {
            c = c3;
        }
        else if (co != COLOR_TRANSPARENT && po == 3) {
            c = co;
        }
        else if (c1 != COLOR_TRANSPARENT && p1 == 1) {
            c = c1;
        }
        else if (c2 != COLOR_TRANSPARENT && p2 == 1) {
            c = c2;
        }
        else if (co != COLOR_TRANSPARENT && po == 2) {
            c = co;
        }
        else if (c1 != COLOR_TRANSPARENT && p1 == 0) {
            c = c1;
        }
        else if (c2 != COLOR_TRANSPARENT && p2 == 0) {
            c = c2;
        }
        else if (co != COLOR_TRANSPARENT && po == 1) {
            c = co;
        }
        else if (c3 != COLOR_TRANSPARENT && p3 == 1 && prio3 == 0) {
            c = c3;
        }
        else if (co != COLOR_TRANSPARENT && po == 0) {
            c = co;
        }
        else if (c3 != COLOR_TRANSPARENT && p3 == 0) {
            c = c3;
        }
        else c = 0;
        scanline.setPixelColor(i, applyBrightness(c));
    }
    return scanline;
}

Scanline ScanlineBlender::blendMode2(Scanline *layers) {
    Scanline scanline;
    Pixel p1, p2, p;
    for (int i = 0; i<256; ++i) {
        p1 = layers[0].getPixel(i);
        p2 = layers[1].getPixel(i);
        if (p1.getBGRColor() != COLOR_TRANSPARENT && p1.getPriority()) {
            p = p1;
        }
        else if (p2.getBGRColor() != COLOR_TRANSPARENT && p2.getPriority()) {
            p = p2;
        }
        else if (p1.getBGRColor() != COLOR_TRANSPARENT && !p1.getPriority()) {
            p = p1;
        }
        else if (p2.getBGRColor() != COLOR_TRANSPARENT && !p2.getPriority()) {
            p = p2;
        }
        else p.setColor(COLOR_TRANSPARENT);
        p.setColor(applyBrightness(p.getBGRColor()));
        scanline.setPixel(i, p);
    }
    return scanline;
}

Scanline ScanlineBlender::blendMode3(Scanline *layers) {
    Scanline scanline;
    Pixel p1, p2, p;
    for (int i = 0; i<256; ++i) {
        p1 = layers[0].getPixel(i);
        p2 = layers[1].getPixel(i);
        if (p1.getBGRColor() != COLOR_TRANSPARENT && p1.getPriority()) {
            p = p1;
        }
        else if (p2.getBGRColor() != COLOR_TRANSPARENT && p2.getPriority()) {
            p = p2;
        }
        else if (p1.getBGRColor() != COLOR_TRANSPARENT && !p1.getPriority()) {
            p = p1;
        }
        else if (p2.getBGRColor() != COLOR_TRANSPARENT && !p2.getPriority()) {
            p = p2;
        }
        else p.setColor(COLOR_TRANSPARENT);
        p.setColor(applyBrightness(p.getBGRColor()));
        scanline.setPixel(i, p);
    }
    return scanline;
}

Scanline ScanlineBlender::blendMode4(Scanline *layers) {
    Scanline scanline;
    Pixel p1, p2, p;
    for (int i = 0; i<256; ++i) {
        p1 = layers[0].getPixel(i);
        p2 = layers[1].getPixel(i);
        if (p1.getBGRColor() != COLOR_TRANSPARENT && p1.getPriority()) {
            p = p1;
        }
        else if (p2.getBGRColor() != COLOR_TRANSPARENT && p2.getPriority()) {
            p = p2;
        }
        else if (p1.getBGRColor() != COLOR_TRANSPARENT && !p1.getPriority()) {
            p = p1;
        }
        else if (p2.getBGRColor() != COLOR_TRANSPARENT && !p2.getPriority()) {
            p = p2;
        }
        else p.setColor(COLOR_TRANSPARENT);
        p.setColor(applyBrightness(p.getBGRColor()));
        scanline.setPixel(i, p);
    }
    return scanline;
}

Scanline ScanlineBlender::blendMode5(Scanline *layers) {
    Scanline scanline;
    Pixel p1, p2, p;
    for (int i = 0; i<256; ++i) {
        p1 = layers[0].getPixel(i);
        p2 = layers[1].getPixel(i);
        if (p1.getBGRColor() != COLOR_TRANSPARENT && p1.getPriority()) {
            p = p1;
        }
        else if (p2.getBGRColor() != COLOR_TRANSPARENT && p2.getPriority()) {
            p = p2;
        }
        else if (p1.getBGRColor() != COLOR_TRANSPARENT && !p1.getPriority()) {
            p = p1;
        }
        else if (p2.getBGRColor() != COLOR_TRANSPARENT && !p2.getPriority()) {
            p = p2;
        }
        else p.setColor(COLOR_TRANSPARENT);
        p.setColor(applyBrightness(p.getBGRColor()));
        scanline.setPixel(i, p);
    }
    return scanline;
}

Scanline ScanlineBlender::blendMode6(Scanline *layers) {
    Scanline scanline;
    Pixel p1, p;
    for (int i = 0; i<256; ++i) {
        p1 = layers[0].getPixel(i);
        if (p1.getBGRColor() != COLOR_TRANSPARENT && p1.getPriority()) {
            p = p1;
        }
        else if (p1.getBGRColor() != COLOR_TRANSPARENT && !p1.getPriority()) {
            p = p1;
        }
        else p.setColor(COLOR_TRANSPARENT);
        p.setColor(applyBrightness(p.getBGRColor()));
        scanline.setPixel(i, p);
    }
    return scanline;
}

longw ScanlineBlender::applyBrightness(longw color) {
    longw r = color & 0x1f;
    longw g = (color >> 5) & 0x1f;
    longw b = (color >> 10) & 0x1f;
    // 0 brightness = black
    // I should consider a new approach
    byte_t brightness = ppuParams->getBrightness();
    r = r & ((brightness << 1) | (brightness & 1));
    g = g & ((brightness << 1) | (brightness & 1));
    b = b & ((brightness << 1) | (brightness & 1));
    longw newColor = (b << 10) | (g << 5) | r;
    return newColor;
}