#include "defines.h"
#include "scanline.h"
#include "backgroundParams.h"
#pragma once
using namespace std;

class Background {
    public:
        Background(int n);
        Scanline getScanline();
        int getNumber();
    private:
        int number;
        BackgroundParams *backgroundParams;
};