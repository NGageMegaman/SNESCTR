#include "defines.h"
#pragma once
using namespace std;

class RomMapper {
    protected:
        RomMapper();
        static RomMapper *romMapper;
    public:
        static RomMapper *getInstance();
        byte_t *mapRom(char *name);
        byte_t *loadHeader(char *romName);
        byte_t *loadLoRom(char *romName, unsigned int romSize);
};