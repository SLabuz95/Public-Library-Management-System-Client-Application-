#include"menu.hpp"
#include"appwindow.hpp"
#include"app.hpp"
#include"../PLMS_Server_App/user.hpp"
#include<QEvent>
#include<QProcess>
#include"dialog.hpp"

Menu::Menu(AppWindow* parent)
    : QMenuBar(parent), parent(parent)
{
    init();
    setWindow();
    createMenu();
    connectMenu();
}

Menu::~Menu(){
    disconnectActions();
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
    // Empty
}

void Menu::createMenu(){
    createApplicationMenu();
    createHelpMenu();
}

void Menu::connectMenu(){
    connectActionsForApplicationMenu();
    connectActionsForHelpMenu();
}

void Menu::clearMemory(){

}


void Menu::disconnectActions(){
    disconnect(&loginActionAM, SIGNAL(triggered()), this, SLOT(loginActionAMTriggered()));
    disconnect(&registerActionAM, SIGNAL(triggered()), this, SLOT(registerActionAMTriggered()));
    disconnect(&quitActionAM, SIGNAL(triggered()), this, SLOT(quitActionAMTriggered()));
    disconnect(&appInfoActionHM, SIGNAL(triggered()), this, SLOT(appInfoActionHMTriggered()));
    disconnect(&authorsActionHM, SIGNAL(triggered()), this, SLOT(authorsActionHMTriggered()));
}

void Menu::loginActionAMTriggered(){    
    parent->setAppWindowStat(APP_WINDOW_STAT_LOGIN);
}

void Menu::registerActionAMTriggered(){
    parent->setAppWindowStat(APP_WINDOW_STAT_REGISTER);
}

void Menu::quitActionAMTriggered(){
    parent->close();
}

void Menu::appInfoActionHMTriggered(){
    Dialog dlg(QUESTION_DIALOG, QString("Informacje o programie"), QString("Program napisany w ramach zajęć projektowych \"Inżynieria oprogramowania II\" w Państwowej Wyższej Szkole Zawodowej w Tarnowie."), nullptr, QString("Zamknij"));
    dlg.exec();
}

void Menu::authorsActionHMTriggered(){
    Dialog dlg(QUESTION_DIALOG, QString("Autorzy"), QString("Sebastian Łabuz\nKamil Grygiel\nŁukasz Smoleń"), nullptr, QString("Zamknij"));
    dlg.exec();
}
