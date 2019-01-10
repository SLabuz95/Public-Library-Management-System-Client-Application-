// ---------------------- Includes ------------------------------------------------
#include "app.hpp"
#include <QTextCodec>
#include<QProcess>
#include"../PLMS_Server_App/user.hpp"
// --------------------------------------------------------------------------------

App::App(int argc, char** argv)
    : QApplication(argc, argv), appWindow(this), server( this )
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

Server& App::getServer(){
    return server;
}


User** App::getUsers(){
    return users;
}

uint App::getNumbOfUsers(){
    return numbOfUsers;
}

User* App::getActiveUser(){
    return activeUser;
}

void App::setActiveUser(User *set){
    SET_PTR_NDO(activeUser, set);
}

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
// _PH_ TEST
void App::addUser(QString userName){
    User** temp = new User*[numbOfUsers+1];
    for(uint i = 0; i < numbOfUsers; i++)
        *(temp + i) = *(users + i);
    delete []users;
    users = temp;
    //*(users + numbOfUsers++) = new User(userName);
    //appWindow.getUserBar().reload();
}
//

void App::removeUser(User *removePTR){
    for(uint i = 0; i < numbOfUsers; i++){
        if((*(users + i)) == removePTR){
            if(numbOfUsers > 1){
                User** temp = new User*[numbOfUsers - 1];
                for(uint j = 0; j < numbOfUsers; j++){
                    if(j < i){
                        *(temp + j) = *(users + j);
                    }else{
                        if(i == j){
                            SET_PTR_DO((*(users + i)), nullptr);
                        }else{
                            *(temp + j - 1) = (*(users + j));
                        }
                    }
                }
                delete []users;
                users = temp;
            }else{
                SET_PTR_DO(*users, nullptr);
                delete []users;
                SET_PTR_NDO(users, nullptr);
            }
            numbOfUsers--;
        }
    }
}

void App::clearMemory(){
    for(uint i = 0; i < numbOfUsers; i++){
        SET_PTR_DO((*(users + i)), nullptr);
        delete []users;
        SET_PTR_NDO(users, nullptr);
    }
}
