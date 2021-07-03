#include "defines.h"
#include "pixel.h"
#include "backgroundParams.h"
#include "characterParams.h"
#include "tile.h"
#include "vram.h"
#include "cgram.h"
#include "oam.h"
#include "scanline.h"
#pragma once
using namespace std;

class ScanlineRenderer {
    protected:
        ScanlineRenderer();
        static ScanlineRenderer *scanlineRenderer;
    public:
        static ScanlineRenderer *getInstance();
        Scanline getScanline(int scanlineNumber, int background, Scanline &scanline);
        Scanline getOBJScanline(int scanlineNumber);
    private:
        void getBackgroundParams(int background);
        word getTileWord(int tileNumber, int line);
        Tile buildTile(word tileWord, int lineNumber);
        Tile buildTileOBJ(byte_t palette, byte_t priority, bool hFlip, bool vFlip, longw tileAddress);

        BackgroundParams *backgroundParams;
        CharacterParams *characterParams;
        VRAM *vram;
        CGRAM *cgram;
        OAM *oam;

        Tile tile;
        bool mainEnable, subEnable;
        longw tilemapAddress, characterAddress;
        bool tilemapHMirror, tilemapVMirror;
        longw hScroll, vScroll;
        byte_t mosaic;
        longw tileSizeX, tileSizeY;
        byte_t BGMode, bpp;
        longw paletteAddress;
};