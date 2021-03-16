#include "defines.h"
#include "pixel.h"
#pragma once
using namespace std;

class Tile {
    public:
        Tile();
        void setParams(int size_p, word tileNumber_p, word palette_p, word priority_p, bool hFlip_p, bool vFlip_p);
        void buildTile(Pixel *pixels_p);
        void setPixel(int x, int y, Pixel pixel);
        void setPixelColor(int x, int y, longw color);
        Pixel getPixel(int x, int y);
        Pixel *getRow(int y);
        word getTileNumber();
        word getPalette();
        word getPriority();
        bool getHFlip();
        bool getVFlip();
    private:
        Pixel pixels[16*16];
        int size;
        word tileNumber;
        word palette;
        word priority;
        bool hFlip;
        bool vFlip;
};