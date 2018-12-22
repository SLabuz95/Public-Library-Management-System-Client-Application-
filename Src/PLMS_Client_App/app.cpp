// ---------------------- Includes ------------------------------------------------
#include "app.hpp"
#include <QTextCodec>
#include<QProcess>
// --------------------------------------------------------------------------------

App::App(int argc, char** argv)
    : QApplication(argc, argv), appWindow(this)/*, _PH_ server( _arguments_ )*/
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    if(!isOneInstanceOfProgram()){
        closeApp = true;
        return;
    }
    show();
    runTimers();
}

App::~App(){
    // _PH_ SET_PTR_DO(user, nullptr);
}

AppWindow& App::getAppWindow(){
    return appWindow;
}

// _PH_
/*
Server& App::getServer(){
    return server;
}
*/

// _PH_
/*
User* App::getUser(){
    return user;
}
*/

// _PH_
/*
void App::setUser(User *set){
    SET_PTR_DO(user, set);
}
*/

bool App::isCloseApp(){
    return closeApp;
}

bool App::isOneInstanceOfProgram(){
    QProcess process;
    process.setReadChannel(QProcess::StandardOutput);
    process.setReadChannelMode(QProcess::MergedChannels);
    process.start("wmic.exe process where name='APP_NAME.exe' get processid");
    process.waitForStarted(1000);
    process.waitForFinished(-1);
    QString str = process.readAll();
    bool numb = false;
    uint len = (uint)str.length();
    short i = 0;
    for(uint j = 0; j < len; j++){
        if(str.at(j) >= 0x30 && str.at(j) <= 0x39){
            if(!numb){
                i++;
                if(i == 2){
                    exit(0);
                    return false;
                }
            }
            numb = true;
        }
        if(str.at(j) == '\n'){
            numb = false;
        }
    }
    return true;
}

void App::show(){
    appWindow.show();
}

void App::runTimers(){
    appWindow.runTimers();
}
