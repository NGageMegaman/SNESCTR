#include "scanlineRenderer.h"
using namespace std;

ScanlineRenderer::ScanlineRenderer() {
    backgroundParams = BackgroundParams::getInstance();
    characterParams = CharacterParams::getInstance();
    vram = VRAM::getInstance();
    cgram = CGRAM::getInstance();
    oam = OAM::getInstance();
}

ScanlineRenderer *ScanlineRenderer::scanlineRenderer = nullptr;

ScanlineRenderer *ScanlineRenderer::getInstance() {
    if (scanlineRenderer == nullptr) {
        scanlineRenderer = new ScanlineRenderer();
    }
    return scanlineRenderer;
}

Scanline ScanlineRenderer::getScanline(int scanlineNumber, int background, Scanline &scanline) {
    scanline.setRow(TRANSPARENT);
    getBackgroundParams(background);
    longw numberTiles = (256 / tileSizeX) + 1;
    longw line = (scanlineNumber + vScroll)%512;
    for (longw i = 0; i<numberTiles; ++i) {
        word tileWord = getTileWord(i, line);
        Tile tile = buildTile(tileWord, line);
        Pixel *tileRow = tile.getRow(line % tileSizeY);
        //scanline.setTilePixels((i*tileSizeX) + hScroll, tileSizeX, tileRow);
        scanline.setTilePixels((i*tileSizeX) - (hScroll % tileSizeX), tileSizeX, tileRow);
    }
    return scanline;
}

Scanline ScanlineRenderer::getOBJScanline(int scanlineNumber) {
    //TODO: Coment and better this. It's a fucking mess
    static Scanline scanline = Scanline();
    scanline.setRow(TRANSPARENT);
    int size = 0;
    Sprite *sprites = oam->getSpritesRow(scanlineNumber, size);
    for (int i = 0; i<size; ++i) {
        Sprite s = sprites[i];
        if (s.getX() <= 256) {
            for (int j = 0; j<s.getSizeX()/8; ++j) {
                int jFlipped = j;
                if (s.getHFlip()) jFlipped = (s.getSizeX()/8)-1-j;
                int yFlipped = (scanlineNumber - s.getY()) / 8;
                if (s.getVFlip()) yFlipped = (s.getSizeY()/8)-1-yFlipped;
                longw firstTile = s.getFirstTile();
                byte_t offsetX = firstTile & 0x00f;
                byte_t offsetY = firstTile & 0x0f0;
                offsetX = (offsetX + jFlipped) & 0x00f;
                offsetY = (offsetY + (yFlipped <<4)) & 0x0f0;
                byte_t tileNumber = offsetY | offsetX;
                longw tileAddress = (s.getNameTableAddress() + (tileNumber << 4)) & 0x7fff;
                Tile tile = buildTileOBJ(s.getPalette(), s.getPriority(), s.getHFlip(), s.getVFlip(), tileAddress);
                Pixel *tileRow = tile.getRow((scanlineNumber - s.getY()) % 8);
                scanline.setTilePixels(s.getX() + (j*8), 8, tileRow);
            }
        }
    }
    return scanline;
}

void ScanlineRenderer::getBackgroundParams(int background) {
    mainEnable = backgroundParams->getMainScreenEnable(background);
    subEnable = backgroundParams->getSubScreenEnable(background);
    tilemapAddress = backgroundParams->getTilemapAddress(background);
    characterAddress = backgroundParams->getBaseAddress(background);
    tilemapHMirror = backgroundParams->getTilemapHMirror(background);
    tilemapVMirror = backgroundParams->getTilemapVMirror(background);
    hScroll = backgroundParams->getHOffset(background);
    vScroll = backgroundParams->getVOffset(background);
    mosaic = backgroundParams->getMosaic(background);
    tileSizeX = backgroundParams->getCharSize(background).first;
    tileSizeY = backgroundParams->getCharSize(background).second;
    BGMode = backgroundParams->getBGMode();
    bpp = backgroundParams->getBpp(background);
    paletteAddress = backgroundParams->getPaletteAddress(background);
}

word ScanlineRenderer::getTileWord(int tileNumber, int line) {
    longw address = 0;
    longw addressX = ((tileNumber * tileSizeX) + hScroll)%512;
    if (addressX >= 256) {
        addressX -= 256;
        if (tilemapHMirror) address += 0x400;
    }
    longw addressY = line;
    if (addressY >= 256) {
        addressY -= 256;
        if (tilemapVMirror && tilemapHMirror) address += 0x800;
        else if (tilemapVMirror) address += 0x400;
    }
    address += tilemapAddress;
    address += (addressY/tileSizeY)*(256/tileSizeX);
    address += addressX/tileSizeX;
    word tileWord = vram->read(address);
    return tileWord;
}

Tile ScanlineRenderer::buildTile(word tileWord, int lineNumber) {
    word tileNumber = tileWord & 0x03ff;
    word palette    = (tileWord >> 10) & 0x0007;
    word priority   = (tileWord >> 13) & 0x0001;
    bool hFlip      = (tileWord >> 14) & 0x0001;
    bool vFlip      = (tileWord >> 15) & 0x0001;
    tile.setParams(tileSizeX, tileNumber, palette, priority, hFlip, vFlip);

    //If tile is 16x16, we build 4 tiles
    int ty = (lineNumber%tileSizeY)/8;
    int i = (lineNumber%8);
    if (vFlip) i = tileSizeY - 1 - i;
    for (int tx = 0; tx<tileSizeX/8; ++tx) {
        //for (int ty = 0; ty<tileSizeY/8; ++ty) {
            longw tileSubNumber = tileNumber + tx + (16*ty);
            longw tileAddress = characterAddress + (tileSubNumber*4*bpp);

            //for (int i = 0; i<8; ++i) {
                for (int j = 0; j<8; ++j) {
                    byte_t cgIndex = 0;
                    for (int plane = 0; plane < bpp; plane += 2) {
                        longw planeAddress = tileAddress + (4*plane) + i;
                        word planes = vram->read(planeAddress);
                        byte_t planeL = planes & 0x00ff;
                        byte_t planeH = (planes >> 8) & 0x00ff;
                        planeL = (planeL >> 7-j) & 1;
                        planeH = ((planeH >> 7-j) & 1) << 1;
                        cgIndex |= (planeH | planeL) << plane;
                    }
                    word color;
                    if (cgIndex == 0) color = -1;
                    else {
                        longw cgAddress = paletteAddress + (palette*bpp*bpp) + cgIndex;
                        color = cgram->read(cgAddress);
                    }
                    tile.setPixelColor((tx*8)+j, (ty*8)+i, color);
                }
            //}
        //}
    }
    return tile;
}

Tile ScanlineRenderer::buildTileOBJ(byte_t palette, byte_t priority, bool hFlip, bool vFlip, longw tileAddress) {
    tile.setParams(8, 0, palette, priority, hFlip, vFlip);
    for (int i = 0; i<8; ++i) {
        for (int j = 0; j<8; ++j) {
            byte_t cgIndex = 0;
            //bpp always = 4
            for (int plane = 0; plane < 4; plane += 2) {
                longw planeAddress = tileAddress + (4*plane) + i;
                word planes = vram->read(planeAddress);
                byte_t planeL = planes & 0x00ff;
                byte_t planeH = (planes >> 8) & 0x00ff;
                planeL = (planeL >> 7-j) & 1;
                planeH = ((planeH >> 7-j) & 1) << 1;
                cgIndex |= (planeH | planeL) << plane;
            }
            word color;
            if (cgIndex == 0) color = -1;
            else {
                longw cgAddress = 128 + (palette*4*4) + cgIndex;
                color = cgram->read(cgAddress);
            }
            Pixel p = Pixel();
            p.setColor(color);
            tile.setPixel(j, i, p);
        }
    }
    return tile;
}