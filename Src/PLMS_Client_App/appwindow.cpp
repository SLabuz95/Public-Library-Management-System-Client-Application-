// ------------------ Includes ------------------------------------------
#include "appwindow.hpp"
#include"appwindowcentralpanel.hpp"
#include"appwindowloginpanel.hpp"
#include"appwindowregisterpanel.hpp"
#include"appwindowloggedinpanel.hpp"
#include"../PLMS_Server_App/user.hpp"
#include<QJsonObject>
#include "app.hpp" // Predefined in AppWindow Header

// ----------------------------------------------------------------------

AppWindow::AppWindow(App* parent)
    : QWidget(), parent(parent), menu(this), toolBar(this), promptPanel(this), statusBar(this), userBar(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectWidgets();
}

AppWindow::~AppWindow(){
    clearMemory();
}

App* AppWindow::getParent(){
    return parent;
}

AppWindowStat AppWindow::getLastAppWindowStat(){
    return *(appWindowStat + 1);
}

AppWindowStat AppWindow::getCurrentAppWindowStat(){
    return *appWindowStat;
}

void AppWindow::setAppWindowStat(AppWindowStat aws){
    if(aws == *appWindowStat && aws == APP_WINDOW_STAT_LOGGED_IN){
        createWidgets();
        createLayout();
        return;
    }
    if(aws != *appWindowStat){
        WINDOW_STATUS_SAVE(appWindowStat);
        *appWindowStat = aws;
        appWindowStatChanged = true;
        if(aws != APP_WINDOW_STAT_LOGGED_IN)
            parent->setActiveUser(nullptr);
    }
}

QStatusBar& AppWindow::getStatusBar(){
    return statusBar;
}

TabBar& AppWindow::getUserBar(){
    return userBar;
}

PromptPanel& AppWindow::getPromptPanel(){
    return promptPanel;
}

void AppWindow::runTimers(){
    // Empty
}

void AppWindow::init(){
    setWindowTitle(QString(APP_NAME) + QString(" ") + APP_VERSION);
    // _PH_ setWindowIcon(QIcon("Icons\\winIcon.png"));
}

void AppWindow::setWindow(){
    setMinimumSize(APP_WINDOW_DEFAULT_WIDTH, APP_WINDOW_DEFAULT_HEIGHT);
    setMaximumSize(APP_WINDOW_DEFAULT_WIDTH, APP_WINDOW_DEFAULT_HEIGHT);
    resize(APP_WINDOW_DEFAULT_WIDTH, APP_WINDOW_DEFAULT_HEIGHT);
    setStyleSheet("AppWindow{background: qlineargradient(x1:0, y1:1, x2:1, y2:0, stop:0 rgba(235, 235,235, 255),stop: 0.63 rgba(200, 200, 200, 255), stop: 1 rgba(210,210,210,255)); border-radius: 10px;}");

}

void AppWindow::createWidgets(){
    SET_PTR_DO(appWindowCentralPanel, nullptr);
    switch (getCurrentAppWindowStat()) {
    case APP_WINDOW_STAT_LOGIN:        
        SET_PTR_NDO(appWindowCentralPanel, new AppWindowLoginPanel(this));
        break;
    case APP_WINDOW_STAT_REGISTER:
        SET_PTR_NDO(appWindowCentralPanel, new AppWindowRegisterPanel(this));
        break;
    case APP_WINDOW_STAT_LOGGED_IN:
        SET_PTR_NDO(appWindowCentralPanel, new AppWindowLoggedInPanel(this, parent->getActiveUser()));
        break;
    }
    appWindowCentralPanel->show();
}

void AppWindow::createLayout(){
    // Menu
    menu.setGeometry(MENU_BAR_X, MENU_BAR_Y, MENU_BAR_WIDTH, MENU_BAR_HEIGHT);

    //ToolBar
    toolBar.setGeometry(TOOL_BAR_X, TOOL_BAR_Y, TOOL_BAR_WIDTH, TOOL_BAR_HEIGHT);

    // TabBar
    userBar.setGeometry(TABBAR_X, TABBAR_Y, TABBAR_WIDTH, TABBAR_HEIGHT);

    // Status Bar Start Layout
    statusBar.setGeometry(STATUS_BAR_X, STATUS_BAR_Y, STATUS_BAR_WIDTH, STATUS_BAR_HEIGHT);
    statusBar.showMessage(STATUS_BAR_READY_TEXT);

    // App Window Central Panel Layout
    appWindowCentralPanel->setGeometry(APP_WINDOW_CENTRAL_PANEL_X, APP_WINDOW_CENTRAL_PANEL_Y, APP_WINDOW_CENTRAL_PANEL_WIDTH, APP_WINDOW_CENTRAL_PANEL_HEIGHT);

    appWindowCentralPanel->lower();
}

void AppWindow::connectWidgets(){
    // Empty
}

void AppWindow::deleteWidgets(){
    SET_PTR_DO(appWindowCentralPanel, nullptr);
}

void AppWindow::clearMemory(){
    // Empty
}

void AppWindow::reload(){
    deleteWidgets();
    createWidgets();
    createLayout();
    connectWidgets();    
    if(getLastAppWindowStat() == APP_WINDOW_STAT_LOGGED_IN || getCurrentAppWindowStat() == APP_WINDOW_STAT_LOGGED_IN)
    {
        if(getLastAppWindowStat() == APP_WINDOW_STAT_LOGGED_IN)
            parent->setActiveUser(nullptr);
        userBar.reload();
    }
    appWindowStatChanged = false;
}

bool AppWindow::isAppWindowStatChanged(){
    return appWindowStatChanged;
}

AppWindowLoggedInPanel* AppWindow::getAppWindowLoggedInPanel(){
    return static_cast<AppWindowLoggedInPanel*>(appWindowCentralPanel);
}
