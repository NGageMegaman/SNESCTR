#include "scanline.h"
using namespace std;

Scanline::Scanline() {
    for (int i = 0; i<256; ++i) {
        pixels[i] = Pixel();
        pixels[i].setColor(TRANSPARENT);
    }
}

void Scanline::setTilePixels(int x, int size, Pixel *tilePixels) {
    for (int i = 0; i<size; ++i) {
        if ((x + i) < 256 && tilePixels[i].getBGRColor() != TRANSPARENT) {
            pixels[(x + i)].setColor(tilePixels[i].getBGRColor());
            pixels[(x + i)].setPriority(tilePixels[i].getPriority());
        }
    }
}

Pixel *Scanline::getPixels() {
    return pixels;
}

Pixel Scanline::getPixel(int i) {
    return pixels[i];
}

void Scanline::setRow(longw color) {
    for (int i = 0; i<256; ++i) {
        pixels[i].setColor(color);
    }
}

void Scanline::setPixel(int i, Pixel p) {
    if (p.getBGRColor() != TRANSPARENT)
    pixels[i] = p;
}

void Scanline::setPixelColor(int i, longw color) {
    pixels[i].setColor(color);
}