#include <stdint.h>
#include "defines.h"
using namespace std;

class Mem {
    protected:
        Mem();
        static Mem *mem;
    public:
        static Mem *getInstance();
        byte  readByte(longw address);
        word  readWord(longw address);
        longw readLong(longw address);
};