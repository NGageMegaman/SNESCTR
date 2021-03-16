#include "defines.h"
#pragma once
using namespace std;

class CharacterParams {
    protected:
        CharacterParams();
        static CharacterParams *characterParams;
    public:
        static CharacterParams *getInstance();
        void writeOBSEL(byte_t data);

        word getNameTableAddress(bool selectNametable);
        pair<byte_t, byte_t> getObjectCharacterSize(bool large);
    private:
        word nameBaseSelect;
        byte_t nameSelect, objectSize;
};