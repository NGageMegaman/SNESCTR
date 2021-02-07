#include <stdint.h>
#include "defines.h"
#include "mem.h"
#include "regfile.h"
#include "decoder.h"
#include "executionUnit.h"
using namespace std;

class CPU{
    protected:
        CPU();
        static CPU *cpu;
    public:
        static CPU *getInstance();
        void executeInstruction();
    private:
        inst_t fetch();
        Mem *mem;
        Regfile *regfile;
        Decoder *decoder;
        ExecutionUnit *executionUnit;
};