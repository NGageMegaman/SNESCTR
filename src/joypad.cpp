#include "joypad.h"
using namespace std;

Joypad::Joypad() {
    autoJoypad = 0;
    controller0Status = 0xffff;
    controller0Latch = 0xffff;
    controller1Status = 0xffff;
    controller1Latch = 0xffff;
}

Joypad *Joypad::joypad = nullptr;

Joypad *Joypad::getInstance() {
    if (joypad == nullptr) {
        joypad = new Joypad();
    }
    return joypad;
}

void Joypad::writeJOYSER0(byte_t data) {
    //latch strobe, do nothing :)
}

void Joypad::writeNMITIMEN(byte_t data) {
    autoJoypad = data & 1;
    //Joypad normally takes some time
    //But now it's instant
    if (autoJoypad) {
        readInputs(0);
        readInputs(1);
        controller0Latch = controller0Status;
        controller1Latch = controller1Status;
        autoJoypad = 0;
    }
}

byte_t Joypad::readJOYSER0() {
    byte_t data;
    data  =  controller0Latch & 1;
    data |= (controller1Latch & 1) << 1;
    controller0Latch >>= 1;
    controller1Latch >>= 1;
    controller0Latch |= 0x8000;
    controller1Latch |= 0x8000;
    return data;
}

byte_t Joypad::readJOYSER1() {
    //TBI
    return 0;
}

byte_t Joypad::readHVBJOY() {
    //TODO: hblank and vblank flags, for now 0
    return autoJoypad;
}

byte_t Joypad::readJOY1L() {
    return (controller0Status & 0x00ff);
}

byte_t Joypad::readJOY1H() {
    return (controller0Status & 0xff00) >> 8;
}

byte_t Joypad::readJOY2L() {
    return (controller1Status & 0x00ff);
}

byte_t Joypad::readJOY2H() {
    return (controller1Status & 0xff00) >> 8;
}

void Joypad::readInputs(int controller){
    word status;
    if (controller == 0) status = controller0Status;
    else status = controller1Status;

    //B button
    if (GetAsyncKeyState(Z_KEY) >> 15) status |= 0x8000;
    else                               status &= 0x7fff;
    //A button
    if (GetAsyncKeyState(X_KEY) >> 15) status |= 0x0080;
    else                               status &= 0xff7f;
    //Y button
    if (GetAsyncKeyState(A_KEY) >> 15) status |= 0x4000;
    else                               status &= 0xbfff;
    //X button
    if (GetAsyncKeyState(S_KEY) >> 15) status |= 0x0040;
    else                               status &= 0xffbf;
    //SELECT button
    if (GetAsyncKeyState(VK_BACK) >> 15) status |= 0x2000;
    else                                 status &= 0xdfff;
    if (GetAsyncKeyState(VK_BACK) >> 15) {
        cout << "DEBUG" << endl;
    }
    //START button
    if (GetAsyncKeyState(VK_RETURN) >> 15) status |= 0x1000;
    else                                   status &= 0xefff;
    //UP button
    if (GetAsyncKeyState(VK_UP) >> 15) status |= 0x0800;
    else                               status &= 0xf7ff;
    //DOWN button
    if (GetAsyncKeyState(VK_DOWN) >> 15) status |= 0x0400;
    else                                 status &= 0xfbff;
    //LEFT button
    if (GetAsyncKeyState(VK_LEFT) >> 15) status |= 0x0200;
    else                                 status &= 0xfdff;
    //RIGHT button
    if (GetAsyncKeyState(VK_RIGHT) >> 15) status |= 0x0100;
    else                                  status &= 0xfeff;

    if (controller == 0) controller0Status = status;
    else controller1Status = status;
}