#include "oam.h"
using namespace std;

OAM::OAM() {
    for (int i = 0; i<OAM_NUM_SPRITES; ++i) {
        sprites[i] = Sprite();
    }
    address = 0;
    incrementedAddress = 0;
    spriteBuffer = Sprite();
}

OAM *OAM::oam = nullptr;

OAM *OAM::getInstance() {
    if (oam == nullptr) {
        oam = new OAM;
    }
    return oam;
}

////////////////////////////////////////////////////////////////////////
// "address" contains the base WORD address of oam
// "incrementedAddress" contains the BYTE address of the current access
// This makes it easier to account for low/high access and reset due
// to writes to OAMADDx
////////////////////////////////////////////////////////////////////////

void OAM::writeOAMADDL(byte_t data) {
    address = (address & 0x1ff) | data;
    incrementedAddress = address << 1; 
}

void OAM::writeOAMADDH(byte_t data) {
    address = ((data << 8) & 1) | address;
    //TODO: PRIORITY BIT, WHAT DOES IT EVEN DO
    incrementedAddress = address << 1;
}

void OAM::writeOAMDATA(byte_t data) {
    // For word address high table starts at 0x100
    // But remember, this is byte address, so it's 0x200
    longw spriteAddress, x;
    if (incrementedAddress < 0x200) {
        //LOW TABLE
        spriteAddress = incrementedAddress / 4;
        switch (incrementedAddress % 4) {
            case 0:
                x = spriteBuffer.getX();
                x = (x & 0x100) | data;
                spriteBuffer.setX(x);
                break;
            case 1:
                sprites[spriteAddress].setX(spriteBuffer.getX());
                sprites[spriteAddress].setY(data);
                break;
            case 2:
                spriteBuffer.setFirstTile(data);
                break;
            case 3:
                sprites[spriteAddress].setFirstTile(spriteBuffer.getFirstTile());
                sprites[spriteAddress].setNameTable(data & 1);
                sprites[spriteAddress].setPalette((data >> 1) & 0x7);
                sprites[spriteAddress].setPriority((data >> 4) & 0x3);
                sprites[spriteAddress].setFlip((data >> 6) & 1, (data >> 7) & 1);
                break;
        }
    }
    else {
        //HIGH TABLE
        spriteAddress = (incrementedAddress - 512) * 4;
        for (int i = 0; i<4; ++i) {
            longw x = sprites[spriteAddress + i].getX();
            x = (((data >> (2*i)) & 1) << 8) | (x & 0x0ff);
            sprites[spriteAddress + i].setX(x);
            sprites[spriteAddress + i].setSize((data >> (1 + (2*i))) & 1);
        }
    }
    incrementedAddress++;
}

byte_t OAM::readOAMDATA() {
    //TBI
    return 0;
}

Sprite *OAM::getSpritesRow(int line, int &size) {
    longw y0, y1;
    static Sprite row[OAM_NUM_SPRITES];
    for (int i = 0; i < OAM_NUM_SPRITES; ++i) {
        y0 = sprites[i].getY();
        y1 = y0 + sprites[i].getSizeY();
        if (line >= y0 && line <= y1) {
            row[size] = sprites[i];
            size++;
        }
    }
    return row;
}