#include"loggedinoperationpanel.hpp"
#include"appwindowloggedinpanel.hpp"
#include"server.hpp"
#include"app.hpp"
#include"appwindow.hpp"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include"bookpanel.hpp"
#include"../PLMS_Server_App/user.hpp"
#include"../PLMS_Server_App/book.hpp"
#include"../PLMS_Server_App/readfilerules.hpp"

LoggedInOperationPanel::LoggedInOperationPanel(AppWindowLoggedInPanel *parent)
    : QFrame(parent), parent(parent){
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    setStyleSheet("LoggedInOperationPanel{background-color: transparent;}");
}

LoggedInOperationPanel::LoggedInOperationPanel(BookPanel *parent, AppWindowLoggedInPanel* appWindowParent)
    : QFrame(parent), parent(appWindowParent){
    setStyleSheet("LoggedInOperationPanel{background-color: transparent;}");
}

LoggedInOperationPanel::~LoggedInOperationPanel(){
    disconnectAll();
    deleteWidgets();
}

void LoggedInOperationPanel::init(){
    // Empty
}

void LoggedInOperationPanel::setWindow(){
    setGeometry(OPERATION_PANEL_X, OPERATION_PANEL_Y, OPERATION_PANEL_WIDTH, OPERATION_PANEL_HEIGHT);
}

void LoggedInOperationPanel::createWidgets(){
    // Empty
}

void LoggedInOperationPanel::createLayout(){
    // Empty
}

void LoggedInOperationPanel::deleteWidgets(){
    // EMPTY
}

void LoggedInOperationPanel::connectAll(){
    // Empty
}

void LoggedInOperationPanel::disconnectAll(){
    // Empty
}

AppWindowLoggedInPanel* LoggedInOperationPanel::getParent(){
    return parent;
}

bool LoggedInOperationPanel::eventFilter(QObject *obj, QEvent *ev){
    return eventMatching(obj, ev);
}
