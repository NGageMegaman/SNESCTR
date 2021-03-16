#include "tile.h"
using namespace std;

Tile::Tile() {
    size = 0;
    tileNumber = 0;
    palette = 0;
    priority = 0;
    hFlip = 0;
    vFlip = 0;
}

void Tile::setParams(int size_p, word tileNumber_p, word palette_p, word priority_p, bool hFlip_p, bool vFlip_p) {
    size = size_p;
    tileNumber = tileNumber_p;
    palette = palette_p;
    priority = priority_p;
    hFlip = hFlip_p;
    vFlip = vFlip_p;
}

void Tile::buildTile(Pixel *pixels_p) {
    for (int i = 0; i<size*size; ++i) {
        pixels[i] = pixels_p[i];
    }
}

void Tile::setPixel(int x, int y, Pixel pixel) {
    pixel.setPriority(priority);
    pixels[x + (y*size)] = pixel;
}

void Tile::setPixelColor(int x, int y, longw color) {
    pixels[x + (y*size)].setColor(color);
    pixels[x + (y*size)].setPriority(priority);

}

Pixel Tile::getPixel(int x, int y) {
    return pixels[x + (y*size)];
}

Pixel *Tile::getRow(int y) {    
    static Pixel row[16];
    int yy, xx;
    if (vFlip) yy = (size-1-y);
    else yy = y;
    
    for (int i = 0; i<size; ++i) {
        if (hFlip) xx = (size-1-i);
        else xx = i;
        row[i] = pixels[xx + (yy*size)];
    }
    return row;
}

word Tile::getTileNumber() {
    return tileNumber;
}

word Tile::getPalette() {
    return palette;
}

word Tile::getPriority() {
    return priority;
}

bool Tile::getHFlip() {
    return hFlip;
}

bool Tile::getVFlip() {
    return vFlip;
}