#include"appwindowcentralpanel.hpp"
#include"appwindow.hpp"
#include"promptpanel.hpp"

AppWindowCentralPanel::AppWindowCentralPanel(AppWindow *parent)
    : QFrame(parent), parent(parent){
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    setStyleSheet("QWidget{background-color: rgba(245, 245, 245, 0.4);}");
}

AppWindowCentralPanel::~AppWindowCentralPanel(){
    disconnectAll();
    deleteWidgets();
}

void AppWindowCentralPanel::init(){
    // Empty
}

void AppWindowCentralPanel::setWindow(){
    resize(APP_WINDOW_CENTRAL_PANEL_WIDTH, APP_WINDOW_CENTRAL_PANEL_HEIGHT - parent->getPromptPanel().height());
}

void AppWindowCentralPanel::createWidgets(){
    // Empty
}

void AppWindowCentralPanel::createLayout(){
    // Empty
}

void AppWindowCentralPanel::deleteWidgets(){
    // EMPTY
}

void AppWindowCentralPanel::connectAll(){
    // Empty
}

void AppWindowCentralPanel::disconnectAll(){
    // Empty
}

AppWindow* AppWindowCentralPanel::getParent(){
    return parent;
}

