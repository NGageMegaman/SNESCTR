#include "defines.h"
#pragma once
using namespace std;

class Joypad {
    protected:
        Joypad();
        static Joypad *joypad;
    public:
        static Joypad *getInstance();
        void writeJOYSER0(byte_t data);
        void writeNMITIMEN(byte_t data);
        byte_t readJOYSER0();
        byte_t readJOYSER1();
        byte_t readHVBJOY();
        byte_t readJOY1L();
        byte_t readJOY1H();
        byte_t readJOY2L();
        byte_t readJOY2H();
        //Players 3 and 4
        //byte_t readJOY3L();
        //byte_t readJOY3H();
        //byte_t readJOY4L();
        //byte_t readJOY4H();
    private:
        void readInputs(int controller);
        word controller0Status, controller1Status;
        word controller0Latch, controller1Latch;
        bool autoJoypad;
};