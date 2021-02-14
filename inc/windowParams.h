#include "defines.h"
#pragma once
using namespace std;

class WindowParams {
    protected:
        WindowParams();
        static WindowParams *windowParams;
    public:
        static WindowParams *getInstance();
        void writeW12SEL(byte_t data);
        void writeW34SEL(byte_t data);
        void writeWOBJSEL(byte_t data);
        void writeWH0(byte_t data);
        void writeWH1(byte_t data);
        void writeWH2(byte_t data);
        void writeWH3(byte_t data);
        void writeWBGLOG(byte_t data);
        void writeWOBJLOG(byte_t data);
        void writeTMW(byte_t data);
        void writeTSW(byte_t data);

        bool getInversion(byte_t background, byte_t window);
        bool getEnable(byte_t background, byte_t window);
        byte_t getMaskLogic(byte_t background);
        bool getWindowMaskingMainScreen(byte_t background);
        bool getWindowMaskingSubScreen(byte_t background);
        byte_t getW1Left();
        byte_t getW1Right();
        byte_t getW2Left();
        byte_t getW2Right();
    private:
        bool BG1W1Inversion, BG1W2Inversion;
        bool BG2W1Inversion, BG2W2Inversion;
        bool BG3W1Inversion, BG3W2Inversion;
        bool BG4W1Inversion, BG4W2Inversion;
        bool OBJW1Inversion, OBJW2Inversion;
        bool BDPW1Inversion, BDPW2Inversion;
        bool BG1W1Enable, BG1W2Enable;
        bool BG2W1Enable, BG2W2Enable;
        bool BG3W1Enable, BG3W2Enable;
        bool BG4W1Enable, BG4W2Enable;
        bool OBJW1Enable, OBJW2Enable;
        bool BDPW1Enable, BDPW2Enable;
        bool BG1WindowMaskingMainScreen, BG1WindowMaskingSubScreen;
        bool BG2WindowMaskingMainScreen, BG2WindowMaskingSubScreen;
        bool BG3WindowMaskingMainScreen, BG3WindowMaskingSubScreen;
        bool BG4WindowMaskingMainScreen, BG4WindowMaskingSubScreen;
        bool OBJWindowMaskingMainScreen, OBJWindowMaskingSubScreen;
        byte_t BG1MaskLogic;
        byte_t BG2MaskLogic;
        byte_t BG3MaskLogic;
        byte_t BG4MaskLogic;
        byte_t OBJMaskLogic;
        byte_t BDPMaskLogic;
        byte_t W1Left, W1Right;
        byte_t W2Left, W2Right;
};