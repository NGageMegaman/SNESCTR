#include "defines.h"
#include "regfile.h"
#include "romMapper.h"
#include "ppuParams.h"
#include "windowParams.h"
#include "backgroundParams.h"
#include "characterParams.h"
#include "wram.h"
#include "vram.h"
#include "cgram.h"
#include "oam.h"
#include "joypad.h"
#include "muldiv.h"
#pragma once
using namespace std;

class DMA;

class Mem {
    protected:
        Mem();
        static Mem *mem;
    public:
        static Mem *getInstance();
        void initMem();
        byte_t readByte(longw address);
        word   readWord(longw address);
        longw  readLong(longw address);
        void writeByte(longw address, byte_t operand);
        void writeWord(longw address, word operand);
        void writeLong(longw address, longw operand);
        void pushStack(byte_t operand);
        byte_t pullStack();
    private:
        longw getMirroredAddress(longw address);
        
        Regfile *regfile;
        RomMapper *romMapper;
        PpuParams *ppuParams;
        WindowParams *windowParams;
        BackgroundParams *backgroundParams;
        CharacterParams *characterParams;
        WRAM *wram;
        VRAM *vram;
        CGRAM *cgram;
        DMA *dma;
        OAM *oam;
        Joypad *joypad;
        Muldiv *muldiv;
        byte_t memory[0x1000000];
};