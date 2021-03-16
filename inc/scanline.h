#include "defines.h"
#include "pixel.h"
#pragma once
using namespace std;

class Scanline {
    public:
        Scanline();
        void setTilePixels(int tile, int size, Pixel *tilePixels);
        Pixel *getPixels();
        Pixel getPixel(int i);
        void setRow(longw color);
        void setPixel(int i, Pixel p);
        void setPixelColor(int i, longw color);
    private:
        Pixel pixels[SCANLINE_SIZE];
};