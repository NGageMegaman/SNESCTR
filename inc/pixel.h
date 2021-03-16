#include "defines.h"
#pragma once
using namespace std;

class Pixel {
    public:
        Pixel();
        void setColor(word value);
        void setPriority(byte_t value);
        word getBGRColor();
        longw getRGBColor();
        byte_t getPriority();
    private:
        word BGRColor;
        byte_t priority;
};