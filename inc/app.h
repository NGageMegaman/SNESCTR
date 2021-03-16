#include "defines.h"
#include <windows.h>

class App {
    protected:
        App();
        static App *app;
    public:
        static App *getInstance();
};