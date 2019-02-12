#include"appwindowcentralpanel.hpp"
#include"appwindow.hpp"
#include"promptpanel.hpp"

AppWindowCentralPanel::AppWindowCentralPanel(AppWindow *parent)
    : QFrame(parent), parent(parent)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    setStyleSheet("AppWindowCentralPanel{background: transparent;}");
}

AppWindowCentralPanel::~AppWindowCentralPanel(){
    disconnectAll();
    deleteWidgets();
}

void AppWindowCentralPanel::init(){
    // Empty
}

void AppWindowCentralPanel::setWindow(){

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

bool AppWindowCentralPanel::eventFilter(QObject *obj, QEvent *ev){
    return eventMatching(obj, ev);
}
