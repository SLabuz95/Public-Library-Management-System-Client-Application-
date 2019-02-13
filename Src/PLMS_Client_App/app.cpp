// ---------------------- Includes ------------------------------------------------
#include "app.hpp"
#include <QTextCodec>
#include<QProcess>
#include"dialog.hpp"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include"appwindowloggedinpanel.hpp"

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

    mainAppTimer.setInterval(MAIN_APP_TIMER_INTERVAL);
    mainAppTimer.installEventFilter(this);

    show();
    runTimers();
}

App::~App(){
    clearMemory();
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


bool App::eventFilter(QObject *obj, QEvent *ev){
    switch(ev->type()){
    case QEvent::Timer:
    {
        if(obj == &mainAppTimer)
            timerFunction();
    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, ev);
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
    mainAppTimer.start();
}

void App::addUser(User* user){

    User** temp = new User*[numbOfUsers+1];
    for(uint i = 0; i < numbOfUsers; i++)
        *(temp + i) = *(users + i);
    delete []users;
    users = temp;
    (*(users + numbOfUsers)) = user;
    numbOfUsers++;
    appWindow.getUserBar().reload();
}


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
                SET_PTR_DOA(users, temp);
            }else{
                SET_PTR_DO(*users, nullptr);
                SET_PTR_DOA(users, nullptr);
            }
            numbOfUsers--;
        }
    }
    appWindow.getUserBar().reload();
}

void App::clearMemory(){
    for(uint i = 0; i < numbOfUsers; i++){
        SET_PTR_DO((*(users + i)), nullptr);
    }

    SET_PTR_DOA(users, nullptr);
}

unsigned long long App::strLenForFile(QString &str){
    unsigned long long counter = 0;
    QByteArray data = str.toUtf8();
    ushort i = 1;
    char tempChar = '\0';
    QTextStream textStr(data);
    while(!textStr.atEnd())
    {
        textStr.device()->getChar(&tempChar);
        if(tempChar > 0){
            if(tempChar == '\n')
                counter += 2;
            else
                counter++;
        }else{
        if(tempChar > -96){
            textStr.device()->getChar(&tempChar);
            i++;
        }else{
            if(tempChar > -112)
            {
                for( ; i < 4; i++)
                {
                    textStr.device()->getChar(&tempChar);
                }
            }else{
                if(tempChar > -120){
                    for( ; i < 5; i++){
                        textStr.device()->getChar(&tempChar);
                     }
                }else{
                    if(tempChar > -124){
                        for( ; i < 6; i++){
                            textStr.device()->getChar(&tempChar);
                        }
                    }else{
                        for( ; i < 7; i++){
                            textStr.device()->getChar(&tempChar);
                         }
                    }
                }
            }
        }
        counter += i;
        i = 1;
   }
 }
    return counter;
}

void App::timerFunction(){
    // Check window state changed flags
    mainAppTimer.stop();
    sendActivityPtr++;
    if(appWindow.getCurrentAppWindowStat() == APP_WINDOW_STAT_LOGGED_IN && appWindow.getAppWindowLoggedInPanel()->isLoggedInStatusChanged())
        appWindow.getAppWindowLoggedInPanel()->reload();
    if(appWindow.isAppWindowStatChanged()){
        appWindow.reload();
    }    
    if(sendActivityPtr > SEND_ACTIVITY_PTR){
        sendActivityUpdate();
        sendActivityPtr = 0;
    }
    mainAppTimer.start();
}

void App::logoutUser(User **user, uint numbOfLogoutUsers){
    // Server Logout
    {
        QJsonArray jA;
        QJsonObject userObj;
        for(uint i = 0; i < numbOfLogoutUsers; i++)
            jA.append((*(user + i))->getParam(USER_ID));
        userObj.insert(USER_PARAMETERS_USER_ID, jA);
        QJsonDocument jDoc(userObj);
        bool stop = false;
        while(!stop){
            if(server.getServerReplyStatus())
                return;
        ServerReplyStatus srs = server.setLastRequest(COMMAND_TYPE_CLIENT_LOGOUT_TEXT, POST, jDoc);
        switch (srs) {
        case SERVER_NO_ERROR:
        {
            appWindow.getPromptPanel().setServerStatusConnection();
            QJsonObject obj = server.readAll();
            if(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT) != QJsonValue::Undefined){
                switch(static_cast<ReturnErrorType>(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt())){
                case RETURN_ERROR_NO_ERROR:
                break;
                    // _PH_ Check other errors
                default:
                 break;
                }
            }
            // _____________________________________________________________________________________________________________
           stop = true;
           server.clearStatus();
        }
            break;
        case SERVER_NETWORK_ERROR:
        {
            // __________________________________________________________________________________
            QNetworkReply::NetworkError error = server.getNetworkError();
            if(error == QNetworkReply::ConnectionRefusedError || error == QNetworkReply::TimeoutError){
                appWindow.getPromptPanel().setServerStatusNoConnection();
            }
            // ____________________________________________________________________________________
            stop = true;
            server.clearStatus();
        }
            break;
        case SERVER_READY:
            stop = true;
            server.clearStatus();
            break;
        default:
            break;
        }
       }
    }
    // Logout Application
    for(uint i = 0; i < numbOfLogoutUsers; i++){
        if(activeUser == (*(user + i))){
            appWindow.setAppWindowStat(APP_WINDOW_STAT_LOGIN);
            SET_PTR_NDO(activeUser, nullptr);
        }
        removeUser((*(user + i)));
    }
}

void App::sendActivityUpdate(){
    // Server Logout
    {
        QJsonArray jA;
        QJsonObject userObj;
        for(uint i = 0 ; i < numbOfUsers; i++)
        {
            jA.append((*(users + i))->getParam(USER_ID));
        }
        userObj.insert(USER_PARAMETERS_USER_ID, jA);
        QJsonDocument jDoc(userObj);
        bool stop = false;
        while(!stop){
            if(server.getServerReplyStatus())
                return;
        ServerReplyStatus srs = server.setLastRequest(COMMAND_TYPE_CLIENT_ACTIVITY_TEXT, POST, jDoc);
        switch (srs) {
        case SERVER_NO_ERROR:
        {
            appWindow.getPromptPanel().setServerStatusConnection();
            QJsonObject obj = server.readAll();
            if(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT) != QJsonValue::Undefined){
                switch(static_cast<ReturnErrorType>(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt())){
                case RETURN_ERROR_NO_ERROR:
                break;
                    // _PH_ Check other errors
                default:
                 break;
                }
            }
            // _____________________________________________________________________________________________________________
           stop = true;
           server.clearStatus();
        }
            break;
        case SERVER_NETWORK_ERROR:
        {
            // __________________________________________________________________________________
            QNetworkReply::NetworkError error = server.getNetworkError();
            if(error == QNetworkReply::ConnectionRefusedError || error == QNetworkReply::TimeoutError){
                appWindow.getPromptPanel().setServerStatusNoConnection();
            }
            // ____________________________________________________________________________________
            stop = true;
            server.clearStatus();
        }
            break;
        case SERVER_READY:
            stop = true;
            server.clearStatus();
            break;
        default:
            break;
        }
       }
    }
}

