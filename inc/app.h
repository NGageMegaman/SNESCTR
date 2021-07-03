#include "defines.h"

class App {
    protected:
        App();
        static App *app;
    public:
        static App *getInstance();
};