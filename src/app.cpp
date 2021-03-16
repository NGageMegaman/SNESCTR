#include "app.h"
using namespace std;

App::App() {
}

App *App::app = nullptr;

App *App::getInstance() {
    if (app == nullptr) {
        app = new App();
    }
    return app;
}
