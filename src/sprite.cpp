#include "sprite.h"
using namespace std;

Sprite::Sprite() {
    x = 0; y = 0;
    firstTile = 0;
    nameTable = 0;
    palette = 0;
    priority = 0;
    hFlip = 0;
    vFlip = 0;
    sizeX = 0;
    sizeY = 0;
    characterParams = CharacterParams::getInstance();
}

void Sprite::setX(longw x_p) {
    x = x_p;
}

void Sprite::setY(longw y_p) {
    y = y_p;
}

void Sprite::setFirstTile(word firstTile_p) {
    firstTile = firstTile_p;
}

void Sprite::setNameTable(bool nameTable_p) {
    nameTable = nameTable_p;
}

void Sprite::setPalette(byte_t palette_p) {
    palette = palette_p;
}

void Sprite::setPriority(byte_t priority_p) {
    priority = priority_p;
}

void Sprite::setFlip(bool hFlip_p, bool vFlip_p) {
    hFlip = hFlip_p;
    vFlip = vFlip_p;
}

void Sprite::setSize(bool size_p) {
    sizeX = characterParams->getObjectCharacterSize(size_p).first;
    sizeY = characterParams->getObjectCharacterSize(size_p).second;
}

longw Sprite::getX() {
    return x;
}

longw Sprite::getY() {
    return y;
}

word Sprite::getFirstTile() {
    return firstTile;
}

bool Sprite::getNameTable() {
    return nameTable;
}

byte_t Sprite::getPalette() {
    return palette;
}

byte_t Sprite::getPriority() {
    return priority;
}

bool Sprite::getHFlip() {
    return hFlip;
}

bool Sprite::getVFlip() {
    return vFlip;
}

byte_t Sprite::getSizeX() {
    return sizeX;
}

byte_t Sprite::getSizeY() {
    return sizeY;
}

longw Sprite::getNameTableAddress() {
    return characterParams->getNameTableAddress(nameTable);
}

longw Sprite::getFirstTileAddress() {
    return getNameTableAddress() + (firstTile << 4) & 0x7fff;
}