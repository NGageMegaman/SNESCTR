#include "backgroundParams.h"
using namespace std;

BackgroundParams::BackgroundParams() {
    BGMode = 0;
    M1BG3priority = 0;
    BG1charSize = BG2charSize = BG3charSize = BG4charSize = 0;
    BG1Mosaic = BG2Mosaic = BG3Mosaic = BG4Mosaic = 0;
    mosaicSize = 0;
    BG1TilemapHMirror = BG1TilemapVMirror = 0;
    BG2TilemapHMirror = BG2TilemapVMirror = 0;
    BG3TilemapHMirror = BG3TilemapVMirror = 0;
    BG4TilemapHMirror = BG4TilemapVMirror = 0;
    BG1TilemapAddress = BG2TilemapAddress = 0;
    BG3TilemapAddress = BG4TilemapAddress = 0;
    BG1BaseAddress = BG2BaseAddress = 0;
    BG3BaseAddress = BG4BaseAddress = 0;
    BG1HOFSWriteHigh = BG1VOFSWriteHigh = 0;
    BG2HOFSWriteHigh = BG2VOFSWriteHigh = 0;
    BG3HOFSWriteHigh = BG3VOFSWriteHigh = 0;
    BG4HOFSWriteHigh = BG4VOFSWriteHigh = 0;
    BG1HOffsetH = BG1HOffsetL = 0;
    BG1VOffsetH = BG1VOffsetL = 0;
    BG2HOffsetH = BG2HOffsetL = 0;
    BG2VOffsetH = BG2VOffsetL = 0;
    BG3HOffsetH = BG3HOffsetL = 0;
    BG3VOffsetH = BG3VOffsetL = 0;
    BG4HOffsetH = BG4HOffsetL = 0;
    BG4VOffsetH = BG4VOffsetL = 0;
    BG1MainScreenEnable = BG2MainScreenEnable = 0;
    BG3MainScreenEnable = BG4MainScreenEnable = 0;
    OBJMainScreenEnable = 0;
    BG1SubScreenEnable = BG2SubScreenEnable = 0;
    BG3SubScreenEnable = BG4SubScreenEnable = 0;
    OBJSubScreenEnable = 0;
    directColorEnable = addSubscreen = 0;
    preventColorMath = clipColorsBlack = 0;
    BG1ColorMathEnable = BG2ColorMathEnable = 0;
    BG3ColorMathEnable = BG4ColorMathEnable = 0;
    OBJColorMathEnable = BDPColorMathEnable = 0;
    halfColorMath = addSubColors = 0;
    colorIntensity = 0;
    colorIntensityR = colorIntensityG = colorIntensityB = 0;
    initBppMatrix();
}

BackgroundParams *BackgroundParams::backgroundParams = nullptr;

BackgroundParams *BackgroundParams::getInstance() {
    if (backgroundParams == nullptr) {
        backgroundParams = new BackgroundParams();
    }
    return backgroundParams;
}

void BackgroundParams::writeBGMODE(byte_t data) {
    BGMode = data & 0x07;
    M1BG3priority = (data >> 3) & 1;
    BG1charSize = (data >> 4) & 1;
    BG2charSize = (data >> 5) & 1;
    BG3charSize = (data >> 6) & 1;
    BG4charSize = (data >> 7) & 1;
}

void BackgroundParams::writeMOSAIC(byte_t data) {
    BG1Mosaic = data & 1;
    BG2Mosaic = (data >> 1) & 1;
    BG3Mosaic = (data >> 2) & 1;
    BG4Mosaic = (data >> 3) & 1;
    mosaicSize = (data >> 4) & 0x0f;
}

void BackgroundParams::writeBG1SC(byte_t data) {
    BG1TilemapHMirror = data & 1;
    BG1TilemapVMirror = (data >> 1) & 1;
    BG1TilemapAddress = (data >> 2) & 0x3f;
}

void BackgroundParams::writeBG2SC(byte_t data) {
    BG2TilemapHMirror = data & 1;
    BG2TilemapVMirror = (data >> 1) & 1;
    BG2TilemapAddress = (data >> 2) & 0x3f;
}

void BackgroundParams::writeBG3SC(byte_t data) {
    BG3TilemapHMirror = data & 1;
    BG3TilemapVMirror = (data >> 1) & 1;
    BG3TilemapAddress = (data >> 2) & 0x3f;
}

void BackgroundParams::writeBG4SC(byte_t data) {
    BG4TilemapHMirror = data & 1;
    BG4TilemapVMirror = (data >> 1) & 1;
    BG4TilemapAddress = (data >> 2) & 0x3f;
}

void BackgroundParams::writeBG12NBA(byte_t data) {
    BG1BaseAddress = data & 0x0f;
    BG2BaseAddress = (data >> 4) & 0x0f;
}

void BackgroundParams::writeBG34NBA(byte_t data) {
    BG3BaseAddress = data & 0x0f;
    BG4BaseAddress = (data >> 4) & 0x0f;
}

void BackgroundParams::writeBG1HOFS(byte_t data) {
    if (BG1HOFSWriteHigh) {
        BG1HOffsetH = data & 0x03;
        BG1HOFSWriteHigh = false;
    }
    else {
        BG1HOffsetL = data;
        BG1HOFSWriteHigh = true;
    }
}

void BackgroundParams::writeBG1VOFS(byte_t data) {
    if (BG1VOFSWriteHigh) {
        BG1VOffsetH = data & 0x03;
        BG1VOFSWriteHigh = false;
    }
    else {
        BG1VOffsetL = data;
        BG1VOFSWriteHigh = true;
    }
}

void BackgroundParams::writeBG2HOFS(byte_t data) {
    if (BG2HOFSWriteHigh) {
        BG2HOffsetH = data & 0x03;
        BG2HOFSWriteHigh = false;
    }
    else {
        BG2HOffsetL = data;
        BG2HOFSWriteHigh = true;
    }
}

void BackgroundParams::writeBG2VOFS(byte_t data) {
    if (BG2VOFSWriteHigh) {
        BG2VOffsetH = data & 0x03;
        BG2VOFSWriteHigh = false;
    }
    else {
        BG2VOffsetL = data;
        BG2VOFSWriteHigh = true;
    }
}

void BackgroundParams::writeBG3HOFS(byte_t data) {
    if (BG3HOFSWriteHigh) {
        BG3HOffsetH = data & 0x03;
        BG3HOFSWriteHigh = false;
    }
    else {
        BG3HOffsetL = data;
        BG3HOFSWriteHigh = true;
    }
}

void BackgroundParams::writeBG3VOFS(byte_t data) {
    if (BG3VOFSWriteHigh) {
        BG3VOffsetH = data & 0x03;
        BG3VOFSWriteHigh = false;
    }
    else {
        BG3VOffsetL = data;
        BG3VOFSWriteHigh = true;
    }
}

void BackgroundParams::writeBG4VOFS(byte_t data) {
    if (BG4VOFSWriteHigh) {
        BG4VOffsetH = data & 0x03;
        BG4VOFSWriteHigh = false;
    }
    else {
        BG4VOffsetL = data;
        BG4VOFSWriteHigh = true;
    }
}

void BackgroundParams::writeBG4HOFS(byte_t data) {
    if (BG4HOFSWriteHigh) {
        BG4HOffsetH = data & 0x03;
        BG4HOFSWriteHigh = false;
    }
    else {
        BG4HOffsetL = data;
        BG4HOFSWriteHigh = true;
    }
}

void BackgroundParams::writeTM(byte_t data) {
    BG1MainScreenEnable = data & 1;
    BG2MainScreenEnable = (data >> 1) & 1;
    BG3MainScreenEnable = (data >> 2) & 1;
    BG4MainScreenEnable = (data >> 3) & 1;
    OBJMainScreenEnable = (data >> 4) & 1;
}

void BackgroundParams::writeTS(byte_t data) {
    BG1SubScreenEnable = data & 1;
    BG2SubScreenEnable = (data >> 1) & 1;
    BG3SubScreenEnable = (data >> 2) & 1;
    BG4SubScreenEnable = (data >> 3) & 1;
    OBJSubScreenEnable = (data >> 4) & 1;
}

void BackgroundParams::writeCGWSEL(byte_t data) {
    directColorEnable = data & 1;
    addSubscreen      = (data >> 1) & 1;
    preventColorMath  = (data >> 4) & 0x03;
    clipColorsBlack   = (data >> 6) & 0x03;
}

void BackgroundParams::writeCGADSUB(byte_t data) {
    BG1ColorMathEnable = data & 1;
    BG2ColorMathEnable = (data >> 1) & 1;
    BG3ColorMathEnable = (data >> 2) & 1;
    BG4ColorMathEnable = (data >> 3) & 1;
    OBJColorMathEnable = (data >> 4) & 1;
    BDPColorMathEnable = (data >> 5) & 1;
    halfColorMath      = (data >> 6) & 1;
    addSubColors       = (data >> 7) & 1;
}

void BackgroundParams::writeCOLDATA(byte_t data) {
    colorIntensity  = data & 0x1f;
    colorIntensityR = (data >> 5) & 1;
    colorIntensityG = (data >> 6) & 1;
    colorIntensityB = (data >> 7) & 1;
}

byte_t BackgroundParams::getBGMode() {
    return BGMode;
}

bool BackgroundParams::isM1BG3priority() {
    if (BGMode == 1) return M1BG3priority;
    else return false;
}

pair<byte_t, byte_t> BackgroundParams::getCharSize(byte_t background) {
    byte_t x, y;
    switch (background) {
        case 1: x = BG1charSize ? 16 : 8; break;
        case 2: x = BG2charSize ? 16 : 8; break;
        case 3: x = BG3charSize ? 16 : 8; break;
        default: x = BG4charSize ? 16 : 8;
    }
    y = x;
    return make_pair(x, y);
}

byte_t BackgroundParams::getMosaic(byte_t background) {
    byte_t size;
    switch (background) {
        case 1: size = BG1Mosaic ? mosaicSize : 1; break;
        case 2: size = BG2Mosaic ? mosaicSize : 1; break;
        case 3: size = BG3Mosaic ? mosaicSize : 1; break;
        default: size = BG4Mosaic ? mosaicSize : 1;
    }
    return size;
}

longw BackgroundParams::getTilemapAddress(byte_t background) {
    longw tilemapAddress;
    switch(background) {
        case 1: tilemapAddress = BG1TilemapAddress; break;
        case 2: tilemapAddress = BG2TilemapAddress; break;
        case 3: tilemapAddress = BG3TilemapAddress; break;
        default: tilemapAddress = BG4TilemapAddress;
    }
    tilemapAddress <<= 10;
    return tilemapAddress;
}

bool BackgroundParams::getTilemapHMirror(byte_t background) {
    bool mirror;
    switch(background) {
        case 1: mirror = BG1TilemapHMirror; break;
        case 2: mirror = BG2TilemapHMirror; break;
        case 3: mirror = BG3TilemapHMirror; break;
        default: mirror = BG4TilemapHMirror;
    }
    return mirror;
}

bool BackgroundParams::getTilemapVMirror(byte_t background) {
    bool mirror;
    switch(background) {
        case 1: mirror = BG1TilemapVMirror; break;
        case 2: mirror = BG2TilemapVMirror; break;
        case 3: mirror = BG3TilemapVMirror; break;
        default: mirror = BG4TilemapVMirror;
    }
    return mirror;
}

longw BackgroundParams::getBaseAddress(byte_t background) {
    longw baseAddress;
    switch(background) {
        case 1: baseAddress = BG1BaseAddress; break;
        case 2: baseAddress = BG2BaseAddress; break;
        case 3: baseAddress = BG3BaseAddress; break;
        default: baseAddress = BG4BaseAddress;
    }
    baseAddress <<= 12;
    return baseAddress;
}

word BackgroundParams::getHOffset(byte_t background) {
    word HOffset;
    switch(background) {
        case 1: HOffset = (BG1HOffsetH << 8) | BG1HOffsetL; break;
        case 2: HOffset = (BG2HOffsetH << 8) | BG2HOffsetL; break;
        case 3: HOffset = (BG3HOffsetH << 8) | BG3HOffsetL; break;
        default: HOffset = (BG4HOffsetH << 8) | BG4HOffsetL;
    }
    return HOffset;
}

word BackgroundParams::getVOffset(byte_t background) {
    word VOffset;
    switch(background) {
        case 1: VOffset = (BG1VOffsetH << 8) | BG1VOffsetL; break;
        case 2: VOffset = (BG2VOffsetH << 8) | BG2VOffsetL; break;
        case 3: VOffset = (BG3VOffsetH << 8) | BG3VOffsetL; break;
        default: VOffset = (BG4VOffsetH << 8) | BG4VOffsetL;
    }
    return VOffset;
}

bool BackgroundParams::getMainScreenEnable(byte_t background) {
    bool mainScreenEnable;
    switch(background) {
        case 1: mainScreenEnable = BG1MainScreenEnable; break;
        case 2: mainScreenEnable = BG2MainScreenEnable; break;
        case 3: mainScreenEnable = BG3MainScreenEnable; break;
        case 4: mainScreenEnable = BG4MainScreenEnable; break;
        default: mainScreenEnable = OBJMainScreenEnable;
    }
    return mainScreenEnable;
}

bool BackgroundParams::getSubScreenEnable(byte_t background) {
    bool subScreenEnable;
    switch(background) {
        case 1: subScreenEnable = BG1SubScreenEnable; break;
        case 2: subScreenEnable = BG2SubScreenEnable; break;
        case 3: subScreenEnable = BG3SubScreenEnable; break;
        case 4: subScreenEnable = BG4SubScreenEnable; break;
        default: subScreenEnable = OBJSubScreenEnable;
    }
    return subScreenEnable;
}

bool BackgroundParams::getDirectColorEnable() {
    return directColorEnable;
}

bool BackgroundParams::getAddSubscreen() {
    return addSubscreen;
}

byte_t BackgroundParams::getPreventColorMath() {
    return preventColorMath;
}

byte_t BackgroundParams::getClipColorsBlack() {
    return clipColorsBlack;
}

bool BackgroundParams::getColorMathEnable(byte_t background) {
    bool colorMathEnable;
    switch(background) {
        case 1: colorMathEnable = BG1ColorMathEnable; break;
        case 2: colorMathEnable = BG2ColorMathEnable; break;
        case 3: colorMathEnable = BG3ColorMathEnable; break;
        case 4: colorMathEnable = BG4ColorMathEnable; break;
        case 5: colorMathEnable = OBJColorMathEnable; break;
        default: colorMathEnable = BDPColorMathEnable;
    }
    return colorMathEnable;
}

bool BackgroundParams::getHalfColorMath() {
    return halfColorMath;
}

bool BackgroundParams::getAddSubColors() {
    return addSubColors;
}

byte_t BackgroundParams::getColorIntensity() {
    return colorIntensity;
}

byte_t BackgroundParams::getColorIntensityR() {
    return colorIntensityR;
}

byte_t BackgroundParams::getColorIntensityG() {
    return colorIntensityG;
}

byte_t BackgroundParams::getColorIntensityB() {
    return colorIntensityB;
}

byte_t BackgroundParams::getBpp(byte_t background) {
    return bppMatrix[4*BGMode + (background-1)];
}

longw BackgroundParams::getPaletteAddress(byte_t background) {
    if (BGMode == 0) return 4*4*(background-1);
    else return 0;
}

void BackgroundParams::initBppMatrix() {
    bppMatrix[0] = 2;
    bppMatrix[1] = 2;
    bppMatrix[2] = 2;
    bppMatrix[3] = 2;
    bppMatrix[4] = 4;
    bppMatrix[5] = 4;
    bppMatrix[6] = 2;
    bppMatrix[7] = 0;
    bppMatrix[8] = 4;
    bppMatrix[9] = 4;
    bppMatrix[10] = 0;
    bppMatrix[11] = 0;
    bppMatrix[12] = 8;
    bppMatrix[13] = 4;
    bppMatrix[14] = 0;
    bppMatrix[15] = 0;
    bppMatrix[16] = 8;
    bppMatrix[17] = 2;
    bppMatrix[18] = 0;
    bppMatrix[19] = 0;
    bppMatrix[20] = 4;
    bppMatrix[21] = 2;
    bppMatrix[22] = 0;
    bppMatrix[23] = 0;
    bppMatrix[24] = 4;
    bppMatrix[25] = 0;
    bppMatrix[26] = 0;
    bppMatrix[27] = 0;
    bppMatrix[28] = 8;
}