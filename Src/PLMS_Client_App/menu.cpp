#include"menu.hpp"
#include"appwindow.hpp"
#include<QEvent>
#include<QProcess>

Menu::Menu(AppWindow* parent)
    : QMenuBar(parent), parent(parent)
{
    init();
    setWindow();
    createMenu();
    connectMenu();
}

Menu::~Menu(){
    clearMemory();
}

AppWindow* Menu::getParent(){
    return parent;
}

void Menu::runTimers(){
    // Empty
}

void Menu::init(){
    // Empty
}

void Menu::setWindow(){
    setFixedHeight(MENU_BAR_HEIGHT);
}

void Menu::createMenu(){
    createApplicationMenu();
    createToolsMenu();
    toolsMenu.setDisabled(true);
    createHelpMenu();
}

void Menu::connectMenu(){
    connectActionsForApplicationMenu();
    connectActionsForToolsMenu();
    connectActionsForHelpMenu();
}

void Menu::reload(){
    switch(parent->getLastAppWindowStat()){
        case APP_WINDOW_STAT_LOGGED_IN:
            createActionsForToolsMenu();
            connectActionsForToolsMenu();
            toolsMenu.setEnabled(true);
            break;
        default:    // APP_WINDOW_STAT_REGISER + APP_WINDOW_STAT_LOGIN
            toolsMenu.setDisabled(true);
            deleteActionsForToolsMenu();
            break;
    }
}

void Menu::clearMemory(){
    SET_PTR_DO(yourAcountActionTM, nullptr);
    SET_PTR_DO(usersActionTM, nullptr);
    SET_PTR_DO(booksActionTM, nullptr);
    SET_PTR_DO(logoutActionTM, nullptr);
    SET_PTR_DO(libraryActionTM, nullptr);
}

void Menu::createActionsForToolsMenu(){
    // Prepare Actions -----------------------------------
    /* _PH_ switch( parent->( get Actual Window Stat Object ) -> (Get Actual Panel Stat) ){
        case ... :
        // Add actions to Tools Menu -------------------

        break;
        default:

        break;
     }
     */
}

void Menu::deleteActionsForToolsMenu(){
    removeAction(yourAcountActionTM);
    removeAction(usersActionTM);
    removeAction(booksActionTM);
    removeAction(logoutActionTM);
    removeAction(libraryActionTM);
    disconnect(&loginActionAM, SIGNAL(triggered()), this, SLOT(loginActionAMTriggered()));
    disconnect(&registerActionAM, SIGNAL(triggered()), this, SLOT(registerActionAMTriggered()));
    disconnect(&quitActionAM, SIGNAL(triggered()), this, SLOT(quitActionAMTriggered()));
    disconnect(&appInfoActionHM, SIGNAL(triggered()), this, SLOT(appInfoActionHMTriggered()));
    disconnect(&helpActionHM, SIGNAL(triggered()), this, SLOT(helpActionHMTriggered()));
    clearMemory();
}

void Menu::loginActionAMTriggered(){
    // _PH_
}

void Menu::registerActionAMTriggered(){
    // _PH_
}

void Menu::quitActionAMTriggered(){
    parent->close();
}

void Menu::yourAcountActionTMTriggered(){
    // _PH_
}

void Menu::usersActionTMTriggered(){
    // _PH_
}

void Menu::booksActionTMTriggered(){
    // _PH_
}

void Menu::logoutActionTMTriggered(){
    // _PH_
}

void Menu::libraryActionTMTriggered(){
    // _PH_
}

void Menu::appInfoActionHMTriggered(){
    // _PH_
}

void Menu::helpActionHMTriggered(){
    // _PH_
}