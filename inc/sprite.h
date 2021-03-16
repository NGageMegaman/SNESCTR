#include "defines.h"
#include "characterParams.h"
#pragma once

class Sprite {
    public:
        Sprite();
        void setX(longw x_p);
        void setY(longw y_p);
        void setFirstTile(word firstTile_p);
        void setNameTable(bool nameTable_p);
        void setPalette(byte_t palette_p);
        void setPriority(byte_t priority_p);
        void setFlip(bool hFlip_p, bool vFlip_p);
        void setSize(bool size_p);
        longw getX();
        longw getY();
        word getFirstTile();
        bool getNameTable();
        byte_t getPalette();
        byte_t getPriority();
        bool getHFlip();
        bool getVFlip();
        byte_t getSizeX();
        byte_t getSizeY();
        longw getNameTableAddress();
        longw getFirstTileAddress();
    private:
        longw x, y;
        word firstTile;
        bool nameTable;
        byte_t palette;
        byte_t priority;
        bool hFlip, vFlip;
        byte_t sizeX, sizeY;

        CharacterParams *characterParams;
};