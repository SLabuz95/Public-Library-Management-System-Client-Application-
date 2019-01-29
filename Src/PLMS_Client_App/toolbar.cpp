#include"toolbar.hpp"
#include"appwindow.hpp"
#include<QEvent>
#include<QProcess>
// _PH_ Need For TEST OF USER TAB in LOGIN Action
#include"app.hpp"
#include<QNetworkRequest>
#include"../PLMS_Server_App/messagetype.hpp"
#include<QJsonDocument>
#include<QJsonObject>
#include"../PLMS_Server_App/user.hpp"
#include"../PLMS_Server_App/commandtype.hpp"
#include"dialog.hpp"

ToolBar::ToolBar(AppWindow* parent)
    : QToolBar(parent), parent(parent)
{
    init();
    setWindow();
    createToolBar();
}

ToolBar::~ToolBar(){
    disconnectToolBar();
    clearMemory();
}

AppWindow* ToolBar::getParent(){
    return parent;
}

void ToolBar::runTimers(){
    // Empty
}

void ToolBar::init(){
    // Empty
}

void ToolBar::setWindow(){
    setFixedHeight(TOOL_BAR_HEIGHT);
    move(0, MENU_BAR_HEIGHT);
}

void ToolBar::createToolBar(){
    createStaticActions();
    createDynamicActions();
}

void ToolBar::clearMemory(){
    SET_PTR_DO(yourAccountAction, nullptr);
    SET_PTR_DO(usersAction, nullptr);
    SET_PTR_DO(booksAction, nullptr);
    SET_PTR_DO(logoutAction, nullptr);
    SET_PTR_DO(libraryAction, nullptr);
}

void ToolBar::reload(){
    switch(parent->getCurrentAppWindowStat()){
        case APP_WINDOW_STAT_LOGGED_IN:
            createDynamicActions();
            break;
        default:    // APP_WINDOW_STAT_REGISER + APP_WINDOW_STAT_LOGIN

            break;
    }
}

void ToolBar::createDynamicActions(){
    // Delete dynamic actions
    deleteDynamicActions();

    // Prepare dynamic Actions -----------------------------------
    /* _PH_ switch( parent->( get Actual Window Stat Object ) -> (Get Actual Panel Stat) ){
        case ... :
        // Connect dynamic actions  -----------------------

        // Add dynamic actions to Tool Bar -------------------

        break;
        default:

        break;
     }
     */
}

void ToolBar::deleteDynamicActions(){
    // Disconnect Dynamic Actions
    disconnectDynamicActions();

    // Remove Dynamic Actions from ToolBar
    removeAction(yourAccountAction);
    removeAction(usersAction);
    removeAction(booksAction);
    removeAction(logoutAction);
    removeAction(libraryAction);

    // Clear Memory
    clearMemory();
}

void ToolBar::disconnectDynamicActions(){
    // Disconnect Dynamic Actions
    disconnect(yourAccountAction, SIGNAL(triggered()), this, SLOT(yourAccountActionTriggered()));
    disconnect(usersAction, SIGNAL(triggered()), this, SLOT(usersActionTriggered()));
    disconnect(booksAction, SIGNAL(triggered()), this, SLOT(booksActionTriggered()));
    disconnect(logoutAction, SIGNAL(triggered()), this, SLOT(logoutActionTriggered()));
    disconnect(libraryAction, SIGNAL(triggered()), this, SLOT(libraryActionTriggered()));

}

void ToolBar::disconnectToolBar(){
    disconnect(&loginAction, SIGNAL(triggered()), this, SLOT(loginActionTriggered()));
    disconnect(&registerAction, SIGNAL(triggered()), this, SLOT(registerActionTriggered()));
    disconnect(&helpAction, SIGNAL(triggered()), this, SLOT(helpActionTriggered()));
    disconnectDynamicActions();
}

void ToolBar::loginActionTriggered(){
    // _PH_ TEST FOR ADDING USERS TABS
    parent->getParent()->addUser(QString("Test ") + QString::number(parent->getParent()->getNumbOfUsers() + 1));
}

void ToolBar::registerActionTriggered(){
    // _PH_ TEST FOR ADDING USER BY REGISTER
    QJsonObject objUser;
    objUser.insert(USER_PARAMETERS_USER_ID, QString("0"));
    objUser.insert(USER_PARAMETERS_USER_NAME, QString("admin2"));
    objUser.insert(USER_PARAMETERS_USER_PASSWORD, QString("admin123"));
    objUser.insert(USER_PARAMETERS_USER_PESEL, QString("9510050454"));
    objUser.insert(USER_PARAMETERS_USER_FIRST_NAME, QString("Tomek"));
    objUser.insert(USER_PARAMETERS_USER_SURNAME, QString("Tomkowski456"));
    QJsonObject obj;
    obj.insert(USER_JSON_KEY_TEXT, objUser);
    QJsonDocument jsonDoc(obj);
    parent->getParent()->getServer().setLastRequest(QString(COMMAND_TYPE_CLIENT_REGISTER_TEXT), POST, jsonDoc);
    while(!parent->getParent()->getServer().isServerReplied());
    /*parent->getParent()->getServer().setLastRequest(new QNetworkRequest(), QString("play"), GET, jsonDoc);
    while(!parent->getParent()->getServer().isServerReplied());*/
}

void ToolBar::yourAccountActionTriggered(){
    // _PH_
}

void ToolBar::usersActionTriggered(){
    // _PH_
}

void ToolBar::booksActionTriggered(){
    // _PH_
}

void ToolBar::logoutActionTriggered(){
    // _PH_
}

void ToolBar::libraryActionTriggered(){
    // _PH_
}

void ToolBar::helpActionTriggered(){
    // _PH_ TEST
    QString str("Test\n");
    QString::iterator i = str.begin();
    uint c = 0;
    while(i != str.end()){
        c++;
        i++;
    }
    Dialog dlg(QUESTION_DIALOG, QString(), QString::number(c), nullptr, QString("Ok"));
    dlg.exec();

}
