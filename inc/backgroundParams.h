#include "defines.h"
#pragma once
using namespace std;

class BackgroundParams {
    protected:
        BackgroundParams();
        static BackgroundParams *backgroundParams;
    public:
        static BackgroundParams *getInstance();
        void writeBGMODE(byte_t data);
        void writeMOSAIC(byte_t data);
        void writeBG1SC(byte_t data);
        void writeBG2SC(byte_t data);
        void writeBG3SC(byte_t data);
        void writeBG4SC(byte_t data);
        void writeBG12NBA(byte_t data);
        void writeBG34NBA(byte_t data);
        void writeBG1HOFS(byte_t data);
        void writeBG1VOFS(byte_t data);
        void writeBG2HOFS(byte_t data);
        void writeBG2VOFS(byte_t data);
        void writeBG3HOFS(byte_t data);
        void writeBG3VOFS(byte_t data);
        void writeBG4HOFS(byte_t data);
        void writeBG4VOFS(byte_t data);
        void writeTM(byte_t data);
        void writeTS(byte_t data);
        void writeCGWSEL(byte_t data);
        void writeCGADSUB(byte_t data);
        void writeCOLDATA(byte_t data);

        byte_t getBGMode();
        bool isM1BG3priority();
        pair<byte_t, byte_t> getCharSize(byte_t background);
        byte_t getMosaic(byte_t background);
        bool getTilemapHMirror(byte_t background);
        bool getTilemapVMirror(byte_t background);
        longw getBaseAddress(byte_t background);
        word getHOffset(byte_t background);
        word getVOffset(byte_t background);
        bool getMainScreenEnable(byte_t background);
        bool getSubScreenEnable(byte_t background);
        bool getDirectColorEnable();
        bool getAddSubscreen();
        byte_t getPreventColorMath();
        byte_t getClipColorsBlack();
        bool getColorMathEnable(byte_t backgorund);
        bool getHalfColorMath();
        bool getAddSubColors();
        byte_t getColorIntensity();
        byte_t getColorIntensityR();
        byte_t getColorIntensityG();
        byte_t getColorIntensityB();
        
    private:
        byte_t BGMode;
        bool M1BG3priority;
        bool BG1charSize, BG2charSize, BG3charSize, BG4charSize;
        bool BG1Mosaic, BG2Mosaic, BG3Mosaic, BG4Mosaic;
        byte_t mosaicSize;
        bool BG1TilemapHMirror, BG1TilemapVMirror;
        bool BG2TilemapHMirror, BG2TilemapVMirror;
        bool BG3TilemapHMirror, BG3TilemapVMirror;
        bool BG4TilemapHMirror, BG4TilemapVMirror;
        longw BG1TilemapAddress, BG2TilemapAddress;
        longw BG3TilemapAddress, BG4TilemapAddress;
        byte_t BG1BaseAddress, BG2BaseAddress;
        byte_t BG3BaseAddress, BG4BaseAddress;
        bool BG1HOFSWriteHigh, BG1VOFSWriteHigh;
        bool BG2HOFSWriteHigh, BG2VOFSWriteHigh;
        bool BG3HOFSWriteHigh, BG3VOFSWriteHigh;
        bool BG4HOFSWriteHigh, BG4VOFSWriteHigh;
        byte_t BG1HOffsetH, BG1HOffsetL;
        byte_t BG1VOffsetH, BG1VOffsetL;
        byte_t BG2HOffsetH, BG2HOffsetL;
        byte_t BG2VOffsetH, BG2VOffsetL;
        byte_t BG3HOffsetH, BG3HOffsetL;
        byte_t BG3VOffsetH, BG3VOffsetL;
        byte_t BG4HOffsetH, BG4HOffsetL;
        byte_t BG4VOffsetH, BG4VOffsetL;
        bool BG1MainScreenEnable, BG2MainScreenEnable;
        bool BG3MainScreenEnable, BG4MainScreenEnable;
        bool OBJMainScreenEnable;
        bool BG1SubScreenEnable, BG2SubScreenEnable;
        bool BG3SubScreenEnable, BG4SubScreenEnable;
        bool OBJSubScreenEnable;
        bool directColorEnable, addSubscreen;
        byte_t preventColorMath, clipColorsBlack;
        bool BG1ColorMathEnable, BG2ColorMathEnable;
        bool BG3ColorMathEnable, BG4ColorMathEnable;
        bool OBJColorMathEnable, BDPColorMathEnable;
        bool halfColorMath, addSubColors;
        byte_t colorIntensity;
        bool colorIntensityR, colorIntensityG, colorIntensityB;
};