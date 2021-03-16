#include "pixel.h"
using namespace std;

Pixel::Pixel() {
    BGRColor = 0;
}

void Pixel::setColor(word value) {
    BGRColor = value;
}

void Pixel::setPriority(byte_t value) {
    priority = value;
}

word Pixel::getBGRColor() {
    return BGRColor;
}

byte_t Pixel::getPriority() {
    return priority;
}

//longw Pixel::getBGRColor32b() {
//    byte_t R =  (BGRColor & 0x001f)        << 3;
//    byte_t G = ((BGRColor & 0x03e0) >> 5 ) << 3;
//    byte_t B = ((BGRColor & 0x7c00) >> 10) << 3;
//    return ((B << 16) | (G << 8) | R);
//}

longw Pixel::getRGBColor() {
    byte_t R =  (BGRColor & 0x001f)        << 3;
    byte_t G = ((BGRColor & 0x03e0) >> 5 ) << 3;
    byte_t B = ((BGRColor & 0x7c00) >> 10) << 3;
    return ((R << 16) | (G << 8) | B);
}