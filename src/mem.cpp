#include "mem.h"
#include "dma.h"
using namespace std;

Mem::Mem() {
    regfile = Regfile::getInstance();
    romMapper = RomMapper::getInstance();
    ppuParams = PpuParams::getInstance();
    windowParams = WindowParams::getInstance();
    backgroundParams = BackgroundParams::getInstance();
    characterParams = CharacterParams::getInstance();
    wram = WRAM::getInstance();
    vram = VRAM::getInstance();
    cgram = CGRAM::getInstance();
    oam = OAM::getInstance();
    dma = DMA::getInstance(this);
    joypad = Joypad::getInstance();
    muldiv = Muldiv::getInstance();
    initMem();
}

Mem *Mem::mem = nullptr;

Mem *Mem::getInstance() {
    if (mem == nullptr) {
        mem = new Mem;
    }
    return mem;
}


void Mem::initMem() {
    byte_t *rom = romMapper->mapRom((char *)"smw.sfc");
    for (int i = 0; i<0xffffff; ++i) {
        writeByte(i, rom[i]);
    }    
    regfile->initPC(readWord(RST_VECTOR));
}

word Mem::readWord(longw address) {
    byte_t lowByte  = readByte(address);
    byte_t highByte = readByte(address+1);
    return (highByte << 8) | lowByte;
}

longw Mem::readLong(longw address) {
    byte_t lowByte    = readByte(address);
    byte_t middleByte = readByte(address+1);
    byte_t highByte   = readByte(address+2);
    return (highByte << 16) | (middleByte << 8) | lowByte;
}

void Mem::writeWord(longw address, word operand) {
    writeByte(address, operand);
    writeByte(address+1, operand >> 8);
}

void Mem::writeLong(longw address, longw operand) {
    writeByte(address, operand);
    writeByte(address+1, operand >> 8);
    writeByte(address+2, operand >> 16);
}

void Mem::pushStack(byte_t operand) {
    word SP = regfile->readSP();
    writeByte(SP, operand);
    regfile->writeSP(SP-1);
}

byte_t Mem::pullStack() {
    word SP = regfile->readSP() + 1;
    regfile->writeSP(SP);
    byte_t result = readByte(SP);
    return result;
}

byte_t Mem::readByte(longw address) {
    longw mirroredAddress = getMirroredAddress(address);
    byte_t readData;
    byte_t channel = (mirroredAddress >> 4) & 0x0f;
    switch (mirroredAddress) {
        //case 0x2137: readData = ->readSLHV(); break;
        case 0x2138: readData = oam->readOAMDATA(); break;
        case 0x2139: readData = vram->readVMDATAL(); break;
        case 0x213a: readData = vram->readVMDATAH(); break;
        case 0x213b: readData = cgram->readCGDATA(); break;
        case 0x2180: readData = wram->readWMDATA(); break;
        case 0x4214: readData = muldiv->readRDDIVL(); break;
        case 0x4215: readData = muldiv->readRDDIVH(); break;
        case 0x4216: readData = muldiv->readRDMPYL(); break;
        case 0x4217: readData = muldiv->readRDMPYH(); break;
        case 0x4016: readData = joypad->readJOYSER0(); break;
        case 0x4017: readData = joypad->readJOYSER1(); break;
        case 0x4212: readData = joypad->readHVBJOY(); break;
        case 0x4218: readData = joypad->readJOY1L(); break;
        case 0x4219: readData = joypad->readJOY1H(); break;
        case 0x421a: readData = joypad->readJOY2L(); break;
        case 0x421b: readData = joypad->readJOY2H(); break;
        case 0x4300: case 0x4310: case 0x4320: case 0x4330:
        case 0x4340: case 0x4350: case 0x4360: case 0x4370:
            readData = dma->readDMAPx(channel); break;
        case 0x4301: case 0x4311: case 0x4321: case 0x4331:
        case 0x4341: case 0x4351: case 0x4361: case 0x4371:
            readData = dma->readBBADx(channel); break;
        case 0x4302: case 0x4312: case 0x4322: case 0x4332:
        case 0x4342: case 0x4352: case 0x4362: case 0x4372:
            readData = dma->readA1TxL(channel); break;
        case 0x4303: case 0x4313: case 0x4323: case 0x4333:
        case 0x4343: case 0x4353: case 0x4363: case 0x4373:
            readData = dma->readA1TxH(channel); break;
        case 0x4304: case 0x4314: case 0x4324: case 0x4334:
        case 0x4344: case 0x4354: case 0x4364: case 0x4374:
            readData = dma->readA1Bx(channel); break;
        case 0x4305: case 0x4315: case 0x4325: case 0x4335:
        case 0x4345: case 0x4355: case 0x4365: case 0x4375:
            readData = dma->readDASxL(channel); break;
        case 0x4306: case 0x4316: case 0x4326: case 0x4336:
        case 0x4346: case 0x4356: case 0x4366: case 0x4376:
            readData = dma->readDASxH(channel); break;
        default: readData = memory[mirroredAddress];
    }
    if (mirroredAddress >= 0x7e0000 && mirroredAddress <= 0x7fffff) {
        readData = wram->read(mirroredAddress);
    }
    return readData;
}

void Mem::writeByte(longw address, byte_t operand) {
    longw mirroredAddress = getMirroredAddress(address);
    byte_t channel = (mirroredAddress >> 4) & 0x0f;
    switch (mirroredAddress) {
        case 0x2100: ppuParams->writeINIDISP(operand); break;
        case 0x2101: characterParams->writeOBSEL(operand); break;
        case 0x2102: oam->writeOAMADDL(operand); break;
        case 0x2103: oam->writeOAMADDH(operand); break;
        case 0x2104: oam->writeOAMDATA(operand); break;
        case 0x2105: backgroundParams->writeBGMODE(operand); break;
        case 0x2106: backgroundParams->writeMOSAIC(operand); break;
        case 0x2107: backgroundParams->writeBG1SC(operand); break;
        case 0x2108: backgroundParams->writeBG2SC(operand); break;
        case 0x2109: backgroundParams->writeBG3SC(operand); break;
        case 0x210a: backgroundParams->writeBG4SC(operand); break;
        case 0x210b: backgroundParams->writeBG12NBA(operand); break;
        case 0x210c: backgroundParams->writeBG34NBA(operand); break;
        case 0x210d: backgroundParams->writeBG1HOFS(operand); break;
        case 0x210e: backgroundParams->writeBG1VOFS(operand); break;
        case 0x210f: backgroundParams->writeBG2HOFS(operand); break;
        case 0x2110: backgroundParams->writeBG2VOFS(operand); break;
        case 0x2111: backgroundParams->writeBG3HOFS(operand); break;
        case 0x2112: backgroundParams->writeBG3VOFS(operand); break;
        case 0x2113: backgroundParams->writeBG4HOFS(operand); break;
        case 0x2114: backgroundParams->writeBG4VOFS(operand); break;
        case 0x2115: vram->writeVMAIN(operand); break;
        case 0x2116: vram->writeVMADDL(operand); break;
        case 0x2117: vram->writeVMADDH(operand); break;
        case 0x2118: vram->writeVMDATAL(operand); break;
        case 0x2119: vram->writeVMDATAH(operand); break;
        //case 0x211a: ->writeM7SEL(operand); break;
        //case 0x211b: ->writeM7A(operand); break;
        //case 0x211c: ->writeM7B(operand); break;
        //case 0x211d: ->writeM7C(operand); break;
        //case 0x211e: ->writeM7D(operand); break;
        //case 0x211f: ->writeM7X(operand); break;
        //case 0x2120: ->writeM7Y(operand); break;
        case 0x2121: cgram->writeCGADD(operand); break;
        case 0x2122: cgram->writeCGDATA(operand); break;
        case 0x2123: windowParams->writeW12SEL(operand); break;
        case 0x2124: windowParams->writeW34SEL(operand); break;
        case 0x2125: windowParams->writeWOBJSEL(operand); break;
        case 0x2126: windowParams->writeWH0(operand); break;
        case 0x2127: windowParams->writeWH1(operand); break;
        case 0x2128: windowParams->writeWH2(operand); break;
        case 0x2129: windowParams->writeWH3(operand); break;
        case 0x212a: windowParams->writeWBGLOG(operand); break;
        case 0x212b: windowParams->writeWOBJLOG(operand); break;
        case 0x212c: backgroundParams->writeTM(operand); break;
        case 0x212d: backgroundParams->writeTS(operand); break;
        case 0x212e: windowParams->writeTMW(operand); break;
        case 0x212f: windowParams->writeTSW(operand); break;
        case 0x2130: backgroundParams->writeCGWSEL(operand); break;
        case 0x2131: backgroundParams->writeCGADSUB(operand); break;
        case 0x2132: backgroundParams->writeCOLDATA(operand); break;
        //case 0x2133: ->writeSETINI(operand); break;
        case 0x2180: wram->writeWMDATA(operand); break;
        case 0x2181: wram->writeWMADDL(operand); break;
        case 0x2182: wram->writeWMADDM(operand); break;
        case 0x2183: wram->writeWMADDH(operand); break;
        case 0x4016: joypad->writeJOYSER0(operand); break;
        case 0x4200: joypad->writeNMITIMEN(operand); break;
        case 0x4202: muldiv->writeWRMPYA(operand); break;
        case 0x4203: muldiv->writeWRMPYB(operand); break;
        case 0x4204: muldiv->writeWRDIVL(operand); break;
        case 0x4205: muldiv->writeWRDIVH(operand); break;
        case 0x4206: muldiv->writeWRDIVB(operand); break;
        case 0x420b: dma->writeMDMA(operand); break;
        case 0x4300: case 0x4310: case 0x4320: case 0x4330:
        case 0x4340: case 0x4350: case 0x4360: case 0x4370:
            dma->writeDMAPx(operand, channel); break;
        case 0x4301: case 0x4311: case 0x4321: case 0x4331:
        case 0x4341: case 0x4351: case 0x4361: case 0x4371:
            dma->writeBBADx(operand, channel); break;
        case 0x4302: case 0x4312: case 0x4322: case 0x4332:
        case 0x4342: case 0x4352: case 0x4362: case 0x4372:
            dma->writeA1TxL(operand, channel); break;
        case 0x4303: case 0x4313: case 0x4323: case 0x4333:
        case 0x4343: case 0x4353: case 0x4363: case 0x4373:
            dma->writeA1TxH(operand, channel); break;
        case 0x4304: case 0x4314: case 0x4324: case 0x4334:
        case 0x4344: case 0x4354: case 0x4364: case 0x4374:
            dma->writeA1Bx(operand, channel); break;
        case 0x4305: case 0x4315: case 0x4325: case 0x4335:
        case 0x4345: case 0x4355: case 0x4365: case 0x4375:
            dma->writeDASxL(operand, channel); break;
        case 0x4306: case 0x4316: case 0x4326: case 0x4336:
        case 0x4346: case 0x4356: case 0x4366: case 0x4376:
            dma->writeDASxH(operand, channel); break;
        
        // ...
        // 0x438a
    }
    if (mirroredAddress >= 0x7e0000 && mirroredAddress <= 0x7fffff) {
        wram->write(operand, mirroredAddress);
    }
    memory[mirroredAddress] = operand;
}

longw Mem::getMirroredAddress(longw address) {
    //MAYBE MOVE TO ROMMAPPER
    byte_t bank = (address >> 16) & 0x0000ff;
    word offset = address & 0x00ffff;
    byte_t page = (offset >> 8) & 0x00ff;

    //Quadrants 1 and 3 WRAM, PPU, APU, JOYPAD
    if ((bank >= 0x80 && bank < 0xc0) || (bank < 0x40)) {
        if (offset < 0x2000) {
            //Only these first 0x20 pages of bank 7e are mirrored, not 7f
            bank = 0x7e;
        }
        else if (page == 0x21 || page == 0x42 || page == 0x43) {
            bank = 0;
        }
    }

    //Upper quadrants 1 and 2 Mirrors into quadrants 3 and 4
    if (bank < 0x7e) {
        if (page >= 0x80 || bank >= 0x40) {
            bank += 0x80;
        }
    }

    //Quadrant 4 low ROM mirror into quadrant 4 upper rom
    if (bank >= 0xc0 && bank < 0xf0) {
        if (page < 0x80) {
            offset += 0x8000;
        }
    }
    longw return_address = (bank << 16) | offset;
    return return_address;
}