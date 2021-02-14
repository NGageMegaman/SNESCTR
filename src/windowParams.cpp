#include "windowParams.h"
using namespace std;

WindowParams::WindowParams() {
    BG1W1Inversion = BG1W2Inversion = false;
    BG2W1Inversion = BG2W2Inversion = false;
    BG3W1Inversion = BG3W2Inversion = false;
    BG4W1Inversion = BG4W2Inversion = false;
    OBJW1Inversion = OBJW2Inversion = false;
    BDPW1Inversion = BDPW2Inversion = false;
    BG1W1Enable = BG1W2Enable = false;
    BG2W1Enable = BG2W2Enable = false;
    BG3W1Enable = BG3W2Enable = false;
    BG4W1Enable = BG4W2Enable = false;
    OBJW1Enable = OBJW2Enable = false;
    BDPW1Enable = BDPW2Enable = false;
    BG1WindowMaskingMainScreen = BG1WindowMaskingSubScreen = false;
    BG2WindowMaskingMainScreen = BG2WindowMaskingSubScreen = false;
    BG3WindowMaskingMainScreen = BG3WindowMaskingSubScreen = false;
    BG4WindowMaskingMainScreen = BG4WindowMaskingSubScreen = false;
    OBJWindowMaskingMainScreen = OBJWindowMaskingSubScreen = false;
    BG1MaskLogic = 0;
    BG2MaskLogic = 0;
    BG3MaskLogic = 0;
    BG4MaskLogic = 0;
    OBJMaskLogic = 0;
    BDPMaskLogic = 0;
    W1Left = W1Right = 0;
    W2Left = W2Right = 0;
}

WindowParams *WindowParams::windowParams = nullptr;

WindowParams *WindowParams::getInstance() {
    if (windowParams == nullptr) {
        windowParams = new WindowParams();
    }
    return windowParams;
}

void WindowParams::writeW12SEL(byte_t data) {
    BG1W1Inversion = data & 1;
    BG1W1Enable    = (data >> 1) & 1;
    BG1W2Inversion = (data >> 2) & 1;
    BG1W2Enable    = (data >> 3) & 1;
    BG2W1Inversion = (data >> 4) & 1;
    BG2W1Enable    = (data >> 5) & 1;
    BG2W2Inversion = (data >> 6) & 1;
    BG2W2Enable    = (data >> 7) & 1;
}

void WindowParams::writeW34SEL(byte_t data) {
    BG3W1Inversion = data & 1;
    BG3W1Enable    = (data >> 1) & 1;
    BG3W2Inversion = (data >> 2) & 1;
    BG3W2Enable    = (data >> 3) & 1;
    BG4W1Inversion = (data >> 4) & 1;
    BG4W1Enable    = (data >> 5) & 1;
    BG4W2Inversion = (data >> 6) & 1;
    BG4W2Enable    = (data >> 7) & 1;
}

void WindowParams::writeWOBJSEL(byte_t data) {
    OBJW1Inversion = data & 1;
    OBJW1Enable    = (data >> 1) & 1;
    OBJW2Inversion = (data >> 2) & 1;
    OBJW2Enable    = (data >> 3) & 1;
    BDPW1Inversion = (data >> 4) & 1;
    BDPW1Enable    = (data >> 5) & 1;
    BDPW2Inversion = (data >> 6) & 1;
    BDPW2Enable    = (data >> 7) & 1;
}

void WindowParams::writeWH0(byte_t data) {
    W1Left = data;
}

void WindowParams::writeWH1(byte_t data) {
    W2Right = data;
}

void WindowParams::writeWH2(byte_t data) {
    W2Left = data;
}

void WindowParams::writeWH3(byte_t data) {
    W2Right = data;
}

void WindowParams::writeWBGLOG(byte_t data) {
    BG1MaskLogic = data & 0x03;
    BG2MaskLogic = (data >> 2) & 0x03;
    BG3MaskLogic = (data >> 4) & 0x03;
    BG4MaskLogic = (data >> 6) & 0x03;
}

void WindowParams::writeWOBJLOG(byte_t data) {
    OBJMaskLogic = data & 0x03;
    BDPMaskLogic = (data >> 2) & 0x03;
}

void WindowParams::writeTMW(byte_t data) {
    BG1WindowMaskingMainScreen = data & 1;
    BG2WindowMaskingMainScreen = (data >> 1) & 1;
    BG3WindowMaskingMainScreen = (data >> 2) & 1;
    BG4WindowMaskingMainScreen = (data >> 3) & 1;
    OBJWindowMaskingMainScreen = (data >> 4) & 1;
}

void WindowParams::writeTSW(byte_t data) {
    BG1WindowMaskingSubScreen = data & 1;
    BG2WindowMaskingSubScreen = (data >> 1) & 1;
    BG3WindowMaskingSubScreen = (data >> 2) & 1;
    BG4WindowMaskingSubScreen = (data >> 3) & 1;
    OBJWindowMaskingSubScreen = (data >> 4) & 1;
}

bool WindowParams::getInversion(byte_t background, byte_t window) {
    bool w1, w2;
    switch (background) {
        case 1: w1 = BG1W1Inversion; w2 = BG1W2Inversion; break;
        case 2: w1 = BG2W1Inversion; w2 = BG2W2Inversion; break;
        case 3: w1 = BG3W1Inversion; w2 = BG3W2Inversion; break;
        case 4: w1 = BG4W1Inversion; w2 = BG4W2Inversion; break;
        case 5: w1 = OBJW1Inversion; w2 = OBJW2Inversion; break;
        default: w1 = BDPW1Inversion; w2 = BDPW2Inversion;
    }
    if (window == 1) return w1;
    else return w2;
}

bool WindowParams::getEnable(byte_t background, byte_t window) {
    bool w1, w2;
    switch (background) {
        case 1: w1 = BG1W1Enable; w2 = BG1W2Enable; break;
        case 2: w1 = BG2W1Enable; w2 = BG2W2Enable; break;
        case 3: w1 = BG3W1Enable; w2 = BG3W2Enable; break;
        case 4: w1 = BG4W1Enable; w2 = BG4W2Enable; break;
        case 5: w1 = OBJW1Enable; w2 = OBJW2Enable; break;
        default: w1 = BDPW1Enable; w2 = BDPW2Enable;
    }
    if (window == 1) return w1;
    else return w2;
}

byte_t WindowParams::getMaskLogic(byte_t background) {
    switch (background) {
        case 1: return BG1MaskLogic; break;
        case 2: return BG2MaskLogic; break;
        case 3: return BG3MaskLogic; break;
        case 4: return BG4MaskLogic; break;
        case 5: return OBJMaskLogic; break;
        default: return BDPMaskLogic;
    }
}

bool WindowParams::getWindowMaskingMainScreen(byte_t background) {
    switch (background) {
        case 1: return BG1WindowMaskingMainScreen; break;
        case 2: return BG2WindowMaskingMainScreen; break;
        case 3: return BG3WindowMaskingMainScreen; break;
        case 4: return BG4WindowMaskingMainScreen; break;
        default: return OBJWindowMaskingMainScreen;
    }
}

bool WindowParams::getWindowMaskingSubScreen(byte_t background) {
    switch (background) {
        case 1: return BG1WindowMaskingSubScreen; break;
        case 2: return BG2WindowMaskingSubScreen; break;
        case 3: return BG3WindowMaskingSubScreen; break;
        case 4: return BG4WindowMaskingSubScreen; break;
        default: return OBJWindowMaskingSubScreen;
    }
}

byte_t WindowParams::getW1Left() {
    return W1Left;
}

byte_t WindowParams::getW1Right() {
    return W1Right;
}

byte_t WindowParams::getW2Left() {
    return W2Left;
}

byte_t WindowParams::getW2Right() {
    return W2Right;
}