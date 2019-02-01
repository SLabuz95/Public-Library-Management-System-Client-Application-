// ------------------ Includes ------------------------------------------
#include "appwindow.hpp"
#include"appwindowcentralpanel.hpp"
#include"appwindowloginpanel.hpp"
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
    // _PH_ To Implement
}

void AppWindow::init(){
    setWindowTitle(QString(APP_NAME) + QString(" ") + APP_VERSION);
    // _PH_ setWindowIcon(QIcon("Icons\\winIcon.png"));
}

void AppWindow::setWindow(){
    setMinimumSize(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);
    setMaximumSize(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);
    setStyleSheet("AppWindow{background: qlineargradient(x1:0, y1:1, x2:1, y2:0, stop:0 rgba(235, 235,235, 255),stop: 0.63 rgba(200, 200, 200, 255), stop: 1 rgba(210,210,210,255)); border-radius: 10px;}");
}

void AppWindow::createWidgets(){
    // _PH_ To Implement
    switch (getCurrentAppWindowStat()) {
    case APP_WINDOW_STAT_LOGIN:
        if(appWindowCentralPanel)
            SET_PTR_DO(appWindowCentralPanel, nullptr);
        SET_PTR_NDO(appWindowCentralPanel, new AppWindowLoginPanel(this));
        break;
    case APP_WINDOW_STAT_REGISTER:
        break;
    case APP_WINDOW_STAT_LOGGED_IN:
        break;
    }
}

void AppWindow::createLayout(){
    // Status Bar Start Layout
    statusBar.setGeometry(STATUS_BAR_X, STATUS_BAR_Y, STATUS_BAR_WIDTH, STATUS_BAR_HEIGHT);
    statusBar.showMessage(STATUS_BAR_READY_TEXT);

    // App Window Central Panel Layout
    appWindowCentralPanel->setGeometry(APP_WINDOW_CENTRAL_PANEL_X, APP_WINDOW_CENTRAL_PANEL_Y, APP_WINDOW_CENTRAL_PANEL_WIDTH, APP_WINDOW_CENTRAL_PANEL_HEIGHT);
}

void AppWindow::connectWidgets(){
    // _PH_ To Implement
}

void AppWindow::deleteWidgets(){
    // _PH_ (Delete only pointers (not element like parent))
    SET_PTR_DO(appWindowCentralPanel, nullptr);
}

void AppWindow::clearMemory(){
    // _PH_ To Implement
}

void AppWindow::reload(){
    deleteWidgets();
    createWidgets();
    createLayout();
    connectWidgets();
}
