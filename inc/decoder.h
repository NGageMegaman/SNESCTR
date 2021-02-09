#include "defines.h"
#include "regfile.h"
#include "mem.h"
#pragma once
using namespace std;

class Decoder {
    protected:
        Decoder();
        static Decoder *decoder;
    public:
        static Decoder *getInstance();
        void decode(inst_t, longw *operand, longw *address);
    private:
        void decodeColumn00(inst_t inst, longw *operand, longw *address);
        void decodeColumn02(inst_t inst, longw *operand, longw *address);
        void decodeColumn04(inst_t inst, longw *operand, longw *address);
        void decodeColumn09(inst_t inst, longw *operand, longw *address);
        void decodeColumn0c(inst_t inst, longw *operand, longw *address);
        void decodeColumn14(inst_t inst, longw *operand, longw *address);
        void decodeColumn16(inst_t inst, longw *operand, longw *address);
        void decodeColumn1c(inst_t inst, longw *operand, longw *address);
        void decodeColumn1e(inst_t inst, longw *operand, longw *address);

        void decodeOperandImmediate(longw *operand, longw *address);
        void decodeOperandImmediateWord(longw *operand, longw *address);
        void decodeOperandImmediateLong(longw *operand, longw *address);
        void decodeOperandAbsolute(longw *operand, longw *address);
        void decodeOperandAbsoluteLong(longw *operand, longw *address);
        void decodeOperandAbsoluteLongIndexed(longw *operand, longw *address);
        void decodeOperandAbsoluteIndexedX(longw *operand, longw *address);
        void decodeOperandAbsoluteIndexedY(longw *operand, longw *address);
        void decodeOperandAbsoluteIndirect(longw *operand, longw *address);
        void decodeOperandAbsoluteIndirectLong(longw *operand, longw *address);
        void decodeOperandAbsoluteIndexedIndirect(longw *operand, longw *address);
        void decodeOperandDirect(longw *operand, longw *address);
        void decodeOperandDirectIndirect(longw *operand, longw *address);
        void decodeOperandDirectIndirectLong(longw *operand, longw *address);
        void decodeOperandDirectIndexedX(longw *operand, longw *address);
        void decodeOperandDirectIndexedY(longw *operand, longw *address);
        void decodeOperandDirectIndexedIndirect(longw *operand, longw *address);
        void decodeOperandDirectIndirectIndexed(longw *operand, longw *address);
        void decodeOperandDirectIndirectLongIndexed(longw *operand, longw *address);
        void decodeOperandRelative(longw *operand, longw *address);
        void decodeOperandRelativeLong(longw *operand, longw *address);
        void decodeOperandStackRelative(longw *operand, longw *address);
        void decodeOperandStackRelativeIndirectIndexed(longw *operand, longw *address);
        void decodeOperandBlockMove(longw *operand, longw *address);
        void decodeNoOperand(longw *operand, longw *address);

        void implicitIncrement(int increment);

        Regfile *regfile;
        Mem *mem;
};