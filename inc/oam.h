#include "defines.h"
#include "sprite.h"
#pragma once
using namespace std;

class OAM {
    protected:
        OAM();
        static OAM *oam;
    public:
        static OAM *getInstance();
        void writeOAMADDL(byte_t data);
        void writeOAMADDH(byte_t data);
        void writeOAMDATA(byte_t data);
        byte_t readOAMDATA();
        Sprite *getSpritesRow(int line, int &size);
    private:
        longw address;
        longw incrementedAddress;
        Sprite sprites[OAM_NUM_SPRITES];
        Sprite spriteBuffer;
};