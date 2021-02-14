#include "characterParams.h"
using namespace std;

CharacterParams::CharacterParams() {

}

CharacterParams *CharacterParams::characterParams = nullptr;

CharacterParams *CharacterParams::getInstance() {
    if (characterParams == nullptr) {
        characterParams = new CharacterParams();
    }
    return characterParams;
}

void CharacterParams::writeOBSEL(byte_t data) {
    nameBaseSelect = (data & 0x07) << 13;
    nameSelect = (data >> 3) & 0x03;
    objectSize = (data >> 5) & 0x07;
}

word CharacterParams::getNameTableAddress(bool selectNametable) {
    word address = nameBaseSelect;
    if (selectNametable) {
        //The nameSelect is used to determine which
        //Nametable we must use
        address += (nameSelect + 1) << 12;
    }
    return address & 0x7fff;
}

pair<byte_t, byte_t> CharacterParams::getCharacterSize(bool large) {
    byte_t x, y;
    switch (objectSize) {
        case 0:
            x = large ? 16 : 8;
            y = large ? 16 : 8;
            break;
        case 1:
            x = large ? 32 : 8;
            y = large ? 32 : 8;
            break;
        case 2:
            x = large ? 64 : 8;
            y = large ? 64 : 8;
            break;
        case 3:
            x = large ? 32 : 16;
            y = large ? 32 : 16;
            break;
        case 4:
            x = large ? 64 : 16;
            y = large ? 64 : 16;
            break;
        case 5:
            x = large ? 64 : 32;
            y = large ? 64 : 32;
            break;
        case 6:
            x = large ? 32 : 16;
            y = large ? 64 : 32;
            break;
        default:
            x = large ? 32 : 16;
            y = large ? 32 : 32;
    }
    return make_pair(x, y);
}