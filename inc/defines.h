#include <stdint.h>
using namespace std;

typedef uint8_t  byte;
typedef uint16_t word;
typedef uint32_t longw;
typedef int8_t   s_byte;
typedef int16_t  s_word;

const longw RESET_VECTOR = 0x00fffc;
const longw SP_INIT_VALUE = 0x00001ff;

enum PFlags_t { 
    CARRY_FLAG, ZERO_FLAG, OVERFLOW_FLAG, NEGATIVE_FLAG,
    DECIMAL_FLAG, EMULATION_FLAG, ACCUMULATOR_FLAG,
    ACCUMULATOR_FLAG, INDEX_FLAG, INTERRUPT_FLAG
};

enum addr_mode_t {
    IMPLIED,
    IMMEDIATE,
    RELATIVE,
    RELATIVE_LONG,
    DIRECT,
    DIRECT_INDEXED,
    DIRECT_INDIRECT,
    DIRECT_INDEXED_INDIRECT,
    DIRECT_INDIRECT_INDEXED,
    DIRECT_INDIRECT_LONG,
    DIRECT_INDIRECT_LONG_INDEXED,
    ABSOLUTE,
    ABSOLUTE_INDEXED,
    ABSOLUTE_LONG,
    ABSOLUTE_INDEXED_LONG,
    STACK_RELATIVE,
    STACK_RELATIVE_INDIRECT_INDEXED,
    ABSOLUTE_INDIRECT,
    ABSOLUTE_INDIRECT_LONG,
    ABSOLUTE_INDEXED_INDIRECT,
    IMPLIED_ACCUMULATOR,
    BLOCK_MOVE
};

enum inst_t {
    ADC1 = 0x61, ADC2 = 0x63, ADC3 = 0x65, ADC4 = 0x67, ADC5 = 0x69,
    ADC6 = 0x6d, ADC7 = 0x6f, ADC8 = 0x71, ADC9 = 0x72, ADCa = 0x73,
    ADCb = 0x75, ADCc = 0x77, ADCd = 0x79, ADCe = 0x7d, ADCf = 0x7f,
    AND1 = 0x21, AND2 = 0x23, AND3 = 0x25, AND4 = 0x27, AND5 = 0x29,
    AND6 = 0x2d, AND7 = 0x2f, AND8 = 0x31, AND9 = 0x32, ANDa = 0x33,
    ANDb = 0x35, ANDc = 0x37, ANDd = 0x39, ANDe = 0x3d, ANDf = 0x3f,
    ASL1 = 0x06, ASL2 = 0x0a, ASL3 = 0x0e, ASL4 = 0x16, ASL5 = 0x1e,
    BCC  = 0x90,
    BCS  = 0xb0,
    BEQ  = 0xf0,
    BIT1 = 0x24, BIT2 = 0x2c, BIT3 = 0x34, BIT4 = 0x3c, BIT5 = 0x89,
    BMI  = 0x30,
    BNE  = 0xd0,
    BPL  = 0x10,
    BRA  = 0x80,
    BRK  = 0x00,
    BRL  = 0x82,
    BVC  = 0x50,
    BVS  = 0x70,
    CLC  = 0x18,
    CLD  = 0xd8,
    CLI  = 0x58,
    CLV  = 0xb8,
    CMP1 = 0xc1, CMP2 = 0xc3, CMP3 = 0xc5, CMP4 = 0xc7, CMP5 = 0xc9,
    CMP6 = 0xcd, CMP7 = 0xcf, CMP8 = 0xd1, CMP9 = 0xd2, CMPa = 0xd3,
    CMPb = 0xd5, CMPc = 0xd7, CMPd = 0xd9, CMPe = 0xdd, CMPf = 0xdf,
    COP  = 0x02,
    CPX1 = 0xe0, CPX2 = 0xe4, CPX3 = 0xec,
    CPY1 = 0xc0, CPY2 = 0xc4, CPY3 = 0xcc,
    DEC1 = 0x3a, DEC2 = 0xc6, DEC3 = 0xce, DEC4 = 0xd6, DEC5 = 0xde,
    DEX  = 0xca,
    DEY  = 0x88,
    EOR1 = 0x41, EOR2 = 0x43, EOR3 = 0x45, EOR4 = 0x47, EOR5 = 0x49,
    EOR6 = 0x4d, EOR7 = 0x4f, EOR8 = 0x51, EOR9 = 0x52, EORa = 0x53,
    EORb = 0x55, EORc = 0x57, EORd = 0x59, EORe = 0x5d, EORf = 0x5f,
    INC1 = 0x1a, INC2 = 0xe6, INC3 = 0xee, INC4 = 0xf6, INC5 = 0xfe,
    INX  = 0xe8,
    INY  = 0xc8,
    JMP1 = 0x4c, JMP2 = 0x5c, JMP3 = 0x6c, JMP4 = 0x7c, JMP5 = 0xdc,
    JSR1 = 0x20, JSR2 = 0xfc, 
    JSL  = 0x22,
    LDA1 = 0xa1, LDA2 = 0xa3, LDA3 = 0xa5, LDA4 = 0xa7, LDA5 = 0xa9,
    LDA6 = 0xad, LDA7 = 0xaf, LDA8 = 0xb1, LDA9 = 0xb2, LDAa = 0xb3,
    LDAb = 0xb5, LDAc = 0xb7, LDAd = 0xb9, LDAe = 0xbd, LDAf = 0xbf,
    LDX1 = 0xa2, LDX2 = 0xa6, LDX3 = 0xae, LDX4 = 0xb6, LDX5 = 0xbe,
    LDY1 = 0xa0, LDY2 = 0xa4, LDY3 = 0xac, LDY4 = 0xb4, LDY5 = 0xbc,
    LSR1 = 0x46, LSR2 = 0x4a, LSR3 = 0x4e, LSR4 = 0x56, LSR5 = 0x5e,
    MVN  = 0x54,
    MVP  = 0x44,
    NOP  = 0xea,
    ORA1 = 0x01, ORA2 = 0x03, ORA3 = 0x05, ORA4 = 0x07, ORA5 = 0x09,
    ORA6 = 0x0d, ORA7 = 0x0f, ORA8 = 0x11, ORA9 = 0x12, ORAa = 0x13,
    ORAb = 0x15, ORAc = 0x17, ORAd = 0x19, ORAe = 0x1d, ORAf = 0x1f,
    PEA  = 0xf4,
    PEI  = 0xd4,
    PER  = 0x62,
    PHA  = 0x48,
    PHB  = 0x8b,
    PHD  = 0x0b,
    PHK  = 0x4b,
    PHP  = 0x08,
    PHX  = 0xda,
    PHY  = 0x5a,
    PLA  = 0x68,
    PLB  = 0xab,
    PLD  = 0x2b,
    PLP  = 0x28,
    PLX  = 0xfa,
    PLY  = 0x7a,
    REP  = 0xc2,
    ROL1 = 0x26, ROL2 = 0x2a, ROL3 = 0x2e, ROL4 = 0x36, ROL5 = 0x3e,
    ROR1 = 0x66, ROR2 = 0x6a, ROR3 = 0x6e, ROR4 = 0x76, ROR5 = 0x7e,
    RTI  = 0x40,
    RTL  = 0x6b,
    RTS  = 0x60,
    SBC1 = 0xe1, SBC2 = 0xe3, SBC3 = 0xe5, SBC4 = 0xe7, SBC5 = 0xe9,
    SBC6 = 0xed, SBC7 = 0xef, SBC8 = 0xf1, SBC9 = 0xf2, SBCa = 0xf3,
    SBCb = 0xf5, SBCc = 0xf7, SBCd = 0xf9, SBCe = 0xfd, SBCf = 0xff,
    SEC  = 0x38,
    SED  = 0xf8,
    SEI  = 0x78,
    SEP  = 0xe2,
    STA1 = 0x81, STA2 = 0x83, STA3 = 0x85, STA4 = 0x87, STA5 = 0x8d,
    STA6 = 0x8f, STA7 = 0x91, STA8 = 0x92, STA9 = 0x93, STAa = 0x95,
    STAb = 0x97, STAc = 0x99, STAd = 0x9d, STAe = 0x9f,
    STP  = 0xdb,
    STX1 = 0x86, STX2 = 0x8e, STX3 = 0x96,
    STY1 = 0x84, STY2 = 0x8c, STY3 = 0x94,
    STZ1 = 0x64, STZ2 = 0x74, STZ3 = 0x9c, STZ4 = 0x9e,
    TAX  = 0xaa,
    TAY  = 0xa8,
    TCD  = 0x5b,
    TCS  = 0x1b,
    TDC  = 0x7b,
    TRB1 = 0x14, TRB2 = 0x1c,
    TSB1 = 0x04, TSB2 = 0x0c,
    TSC  = 0x3b,
    TSX  = 0xba,
    TXA  = 0x8a,
    TXS  = 0x9a,
    TXY  = 0x9b,
    TYA  = 0x98,
    TYX  = 0xbb,
    WAI  = 0xcb,
    WDM  = 0x42,
    XBA  = 0xeb,
    XCE  = 0xfb
};