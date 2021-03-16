#include "romMapper.h"
using namespace std;

RomMapper::RomMapper() {

}

RomMapper *RomMapper::romMapper = nullptr;

RomMapper *RomMapper::getInstance() {
    if (romMapper == nullptr) {
        romMapper = new RomMapper();
    }
    return romMapper;
}

byte_t *RomMapper::mapRom(char *romName) {
    byte_t *rom;
    byte_t *header = loadHeader(romName);
    for (int i = 0; i<21; ++i) {
        cout << (char) header[i];
    }
    cout << endl;
    byte_t mapMode    = header[21];
    byte_t romType    = header[22];
    byte_t romSize    = header[23];
    byte_t sramSize   = header[24];
    byte_t dest       = header[25];
    byte_t fixedval   = header[26];
    byte_t version    = header[27];
    word complement = (header[29] << 8) | header[28];
    word checksum   = (header[31] << 8) | header[30];
    
    unsigned int size = 1024 * (1 << romSize);
    if (mapMode == 0x20) rom = loadLoRom(romName, size);
    return rom;
}

byte_t *RomMapper::loadHeader(char *romName) {
    /* Header format:
    Address   len  
    ---------------------------------
    $00:7fc0 | 21 | Internal ROM Name
    $00:7fd5 |  1 | Map Mode
    $00:7fd6 |  1 | ROM Type
    $00:7fd7 |  1 | ROM Size
    $00:7fd8 |  1 | SRAM Size
    $00:7fd9 |  1 | Destination Code
    $00:7fda |  1 | Fixed Value ($33)
    $00:7fdb |  1 | Version#
    $00:7fdc |  2 | Complement check
    $00:7fde |  2 | Checksum
    ----------------------------------
    */
    ifstream rom;
    rom.open(romName, std::ios_base::binary);
    rom.seekg(0x7fc0, ios::beg);

    static char header[0x1e];
    rom.read(header, HEADER_SIZE);
    rom.close();
    return (byte_t *) header;
}

byte_t *RomMapper::loadLoRom(char *romName, unsigned int romSize) {
    // For each bank, we map 0x8000 bytes from rom to upper half of bank
    // $80:8000 ~ $80:ffff <- rom[$00:0000] ~ rom[$00:7fff]
    // $81:8000 ~ $81:ffff <- rom[$00:8000] ~ rom[$00:ffff]
    // $82:8000 ~ $82:ffff <- rom[$01:0000] ~ rom[$01:7fff]
    // $83:8000 ~ $83:ffff <- rom[$01:8000] ~ rom[$01:ffff]
    // ...
    static char romMapped[0x1000000];
    ifstream rom;
    rom.open(romName, std::ios_base::binary);
    rom.seekg(0, ios::beg);
    for (int i = 0; romSize != 0; ++i) {
        rom.read(romMapped + 0x800000 + 0x8000 + (0x10000 * i), 0x8000);
        romSize -= 0x8000;
    }
    rom.close();
    return (byte_t *) romMapped;
}