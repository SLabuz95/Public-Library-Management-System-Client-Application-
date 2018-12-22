#include "app.hpp"

int main(int argc, char** argv){
    App *app = new App(argc, argv);
    if(app->isCloseApp())
        return 0;
    return app->exec();
}
