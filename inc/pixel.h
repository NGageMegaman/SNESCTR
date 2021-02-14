#include "defines.h"
using namespace std;

class Pixel {
    public:
        Pixel();
        void setColor(word value);
        void setX(longw value);
        void setY(longw value);
        word getBGRColor();
        longw getRGBColor();
        longw getX();
        longw getY();
    private:
        word BGRColor;
        longw X, Y;
};