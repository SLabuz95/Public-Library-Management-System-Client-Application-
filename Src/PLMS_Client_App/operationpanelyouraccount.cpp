#include"operationpanelyouraccount.hpp"
#include<QLineEdit>
#include<QKeyEvent>
#include"appwindowloggedinpanel.hpp"
#include"app.hpp"
#include<QScrollBar>
#include"dialog.hpp"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include"server.hpp"
#include"promptpanel.hpp"
#include"appwindow.hpp"
#include"../PLMS_Server_App/user.hpp"

OperationPanelYourAccount::OperationPanelYourAccount(AppWindowLoggedInPanel* parent)
    : LoggedInOperationPanel(parent),
      yourAccountTitleLabel(this),
      scrollArea(this),
      dataPanel(this, parent->getUser(), DATA_MODE),
      changeDataButton(this),
      removeAccountButton(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationPanelYourAccount::~OperationPanelYourAccount(){
    disconnectAll();
    deleteWidgets();
}

void OperationPanelYourAccount::init(){
    // Empty
}

void OperationPanelYourAccount::setWindow(){
    // Empty
}

void OperationPanelYourAccount::createWidgets(){
    // Empty
}

void OperationPanelYourAccount::createLayout(){
    // Register Title Label
    yourAccountTitleLabel.setText(OPERATION_PANEL_YOUR_ACCOUNT_TITLE);
    yourAccountTitleLabel.setGeometry(OPERATION_PANEL_YOUR_ACCOUNT_TITLE_X,OPERATION_PANEL_YOUR_ACCOUNT_TITLE_Y,OPERATION_PANEL_YOUR_ACCOUNT_TITLE_WIDTH,OPERATION_PANEL_YOUR_ACCOUNT_TITLE_HEIGHT);
    yourAccountTitleLabel.setStyleSheet(STYLESHEET_TITLE);
    yourAccountTitleLabel.setAlignment(Qt::AlignCenter);

    // User Data Panel
    dataPanel.setGeometry(OPERATION_PANEL_YOUR_ACCOUNT_USER_DATA_PANEL_X,OPERATION_PANEL_YOUR_ACCOUNT_USER_DATA_PANEL_Y,OPERATION_PANEL_YOUR_ACCOUNT_USER_DATA_PANEL_WIDTH,OPERATION_PANEL_YOUR_ACCOUNT_USER_DATA_PANEL_HEIGHT);

    // Scroll Area
    scrollArea.setStyleSheet("QScrollArea{background-color: transparent;}");
    scrollArea.verticalScrollBar()->setStyleSheet("QScrollBar::vertical{background: transparent; width: 5px;} QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical, QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical, QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{border: none; background: none; color: none;} QScrollBar::handle:vertical{background-color: white; border: 1px solid black;}");
    scrollArea.setFrameShape(QFrame::NoFrame);
    scrollArea.setWidget(&dataPanel);
    scrollArea.setGeometry(OPERATION_PANEL_YOUR_ACCOUNT_USER_DATA_PANEL_X,OPERATION_PANEL_YOUR_ACCOUNT_USER_DATA_PANEL_Y,OPERATION_PANEL_YOUR_ACCOUNT_USER_DATA_PANEL_WIDTH,OPERATION_PANEL_YOUR_ACCOUNT_USER_DATA_PANEL_HEIGHT);
    scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea.show();

    // Register Button
    changeDataButton.setGeometry(OPERATION_PANEL_CHANGE_DATA_YOUR_ACCOUNT_BUTTON_X,OPERATION_PANEL_CHANGE_DATA_YOUR_ACCOUNT_BUTTON_Y,OPERATION_PANEL_CHANGE_DATA_YOUR_ACCOUNT_BUTTON_WIDTH,OPERATION_PANEL_CHANGE_DATA_YOUR_ACCOUNT_BUTTON_HEIGHT);
    changeDataButton.setText(OPERATION_PANEL_YOUR_ACCOUNT_CHANGE_DATA_BUTTON_TEXT);
    changeDataButton.setAlignment(Qt::AlignCenter);
    changeDataButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);

    // Cancel Button
    removeAccountButton.setText(OPERATION_PANEL_YOUR_ACCOUNT_REMOVE_ACCOUNT_BUTTON_TEXT);
    removeAccountButton.setGeometry(OPERATION_PANEL_YOUR_ACCOUNT_CANCEL_BUTTON_X,OPERATION_PANEL_YOUR_ACCOUNT_CANCEL_BUTTON_Y,OPERATION_PANEL_YOUR_ACCOUNT_CANCEL_BUTTON_WIDTH,OPERATION_PANEL_YOUR_ACCOUNT_CANCEL_BUTTON_HEIGHT);
    removeAccountButton.setAlignment(Qt::AlignCenter);
    removeAccountButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
}

void OperationPanelYourAccount::deleteWidgets(){
    // Empty
}

void OperationPanelYourAccount::connectAll(){
    // Register Button Connect
    changeDataButton.installEventFilter(this);

    // Cancel Button Connect
    removeAccountButton.installEventFilter(this);

}

void OperationPanelYourAccount::disconnectAll(){
    // Empty
}

void OperationPanelYourAccount::reload(){
    createLayout();
}

bool OperationPanelYourAccount::eventMatching(QObject* obj, QEvent* ev){
    switch (ev->type()) {
    case QEvent::MouseButtonRelease:
    {
        if(obj == &changeDataButton){
            changeDataButtonPressed();
            return true;
        }
        if(obj == &removeAccountButton){
            removeAccountButtonPressed();
            return true;
        }        
    }
        break;
    case QEvent::Enter:
    {
        if(obj == &changeDataButton){
            changeDataButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
        if(obj == &removeAccountButton){
            removeAccountButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &changeDataButton){
            changeDataButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
        if(obj == &removeAccountButton){
            removeAccountButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, ev);
}

void OperationPanelYourAccount::changeDataButtonPressed(){
    if(dataPanel.getMode() >= DATA_MODE){
        changeDataButton.setText(OPERATION_PANEL_YOUR_ACCOUNT_ACCEPT_BUTTON_TEXT);
        removeAccountButton.setText(OPERATION_PANEL_YOUR_ACCOUNT_CANCEL_BUTTON_TEXT);
        dataPanel.changeMode(EDITABLE_MODE);
    }else{
        // Try to change data on server
        if(!dataPanel.checkData()){
            Dialog dlg(QUESTION_DIALOG, QString("Błąd danych"), QString("Niepoprawnie wypełniony formularz."), nullptr, QString("Ok"));
            dlg.exec();
            return;
        }else{
            // Try to Edit Data
            User* userEdit = dataPanel.getTempUser();
            // Create Json User
            {
                QJsonArray jA;
                QJsonObject userObj;
                userEdit->writeJson(userObj);
                jA.append(userObj);
                userObj = QJsonObject();
                userObj.insert(USER_JSON_KEY_TEXT, jA);
                QJsonDocument jDoc(userObj);
                bool stop = false;
                while(!stop){
                    if(parent->getParent()->getParent()->getServer().getServerReplyStatus())
                        return;
                ServerReplyStatus srs = parent->getParent()->getParent()->getServer().setLastRequest(COMMAND_TYPE_CLIENT_EDIT_TEXT, POST, jDoc);
                switch (srs) {
                case SERVER_NO_ERROR:
                {
                    parent->getParent()->getPromptPanel().setServerStatusConnection();
                    QJsonObject obj = parent->getParent()->getParent()->getServer().readAll();
                    if(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT) != QJsonValue::Undefined){
                        switch(static_cast<ReturnErrorType>(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt())){
                        case RETURN_ERROR_NO_ERROR:
                        {
                            // ______________________________________________________________________________________________________
                            parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_WARNING, QString("Edycja danych udana."));
                            if(dataPanel.getUser())
                                dataPanel.getUser()->merge(*userEdit);
                            // Reload
                            changeDataButton.setText(OPERATION_PANEL_YOUR_ACCOUNT_CHANGE_DATA_BUTTON_TEXT);
                            removeAccountButton.setText(OPERATION_PANEL_YOUR_ACCOUNT_REMOVE_ACCOUNT_BUTTON_TEXT);
                            dataPanel.changeMode(DATA_MODE);
                            // __________________________________________________________________
                        }
                            break;
                            // _PH_ Check other errors
                        case RETURN_ERROR_USER_FOUND:{
                            parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Podany użytkownik już istnieje."));
                       }
                            break;
                        default:
                            //  Prompt Server Error
                            parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - Tworzenie konta nieudane."));
                            break;
                        }
                    }
                    // _____________________________________________________________________________________________________________
                   stop = true;
                   parent->getParent()->getParent()->getServer().clearStatus();
                }
                    break;
                case SERVER_NETWORK_ERROR:
                {
                    // __________________________________________________________________________________
                    QNetworkReply::NetworkError error = parent->getParent()->getParent()->getServer().getNetworkError();
                    if(error == QNetworkReply::ConnectionRefusedError || error == QNetworkReply::TimeoutError){
                        parent->getParent()->getPromptPanel().setServerStatusNoConnection();
                    }
                    // ____________________________________________________________________________________
                    stop = true;
                    parent->getParent()->getParent()->getServer().clearStatus();
                }
                    break;
                case SERVER_READY:
                    stop = true;
                    parent->getParent()->getParent()->getServer().clearStatus();
                    break;
                default:
                    break;
                }
               }
            }
            SET_PTR_DO(userEdit, nullptr);
        }
    }
}

void OperationPanelYourAccount::removeAccountButtonPressed(){
    if(dataPanel.getMode() == DATA_MODE){
        // Try to remove account
        Dialog dlg(QUESTION_DIALOG, QString("Usuwanie konta"), QString("Jesteś pewny, że chcesz usunąć konto?"), nullptr, QString("Tak"), QString("Nie"));
        switch(dlg.exec()){
        case FIRST_OPTION_RESULT:
        {
            // Try to remove account
            User *userRem = nullptr;
            if(dataPanel.getUser())
                userRem = dataPanel.getUser();
            else {
                userRem = new User();
            }
                // Create Json User
                    QJsonArray jA;
                    QJsonObject userObj;
                    userRem->writeJson(userObj);
                    jA.append(userObj);
                    userObj = QJsonObject();
                    userObj.insert(USER_JSON_KEY_TEXT, jA);
                    QJsonDocument jDoc(userObj);
                    bool stop = false;
                    while(!stop){
                        if(parent->getParent()->getParent()->getServer().getServerReplyStatus())
                            return;
                    ServerReplyStatus srs = parent->getParent()->getParent()->getServer().setLastRequest(COMMAND_TYPE_CLIENT_REMOVE_TEXT, POST, jDoc);
                    switch (srs) {
                    case SERVER_NO_ERROR:
                    {
                        parent->getParent()->getPromptPanel().setServerStatusConnection();
                        QJsonObject obj = parent->getParent()->getParent()->getServer().readAll();
                        if(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT) != QJsonValue::Undefined){
                            switch(static_cast<ReturnErrorType>(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt())){
                            case RETURN_ERROR_NO_ERROR:
                            {
                                // ______________________________________________________________________________________________________
                                parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_WARNING, QString("Usuwanie konta udane."));
                                // Logout Application
                                parent->getParent()->setAppWindowStat(APP_WINDOW_STAT_LOGIN);
                                parent->getParent()->getParent()->setActiveUser(nullptr);
                                parent->getParent()->getParent()->removeUser(userRem);
                                userRem = nullptr;
                                // __________________________________________________________________
                            }
                                break;
                                // _PH_ Check other errors
                                default:
                                //  Prompt Server Error
                                parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - Tworzenie konta nieudane."));
                                break;
                            }
                        }
                        // _____________________________________________________________________________________________________________
                       stop = true;
                       parent->getParent()->getParent()->getServer().clearStatus();
                    }
                        break;
                    case SERVER_NETWORK_ERROR:
                    {
                        // __________________________________________________________________________________
                        QNetworkReply::NetworkError error = parent->getParent()->getParent()->getServer().getNetworkError();
                        if(error == QNetworkReply::ConnectionRefusedError || error == QNetworkReply::TimeoutError){
                            parent->getParent()->getPromptPanel().setServerStatusNoConnection();
                        }
                        // ____________________________________________________________________________________
                        stop = true;
                        parent->getParent()->getParent()->getServer().clearStatus();
                    }
                        break;
                    case SERVER_READY:
                        stop = true;
                        parent->getParent()->getParent()->getServer().clearStatus();
                        break;
                    default:
                        break;
                    }
                   }
                SET_PTR_DO(userRem, nullptr);
        }
            break;
        case SECOND_OPTION_RESULT:
        {
            return;
        }
        default:
            break;
        }
    }else{
        changeDataButton.setText(OPERATION_PANEL_YOUR_ACCOUNT_CHANGE_DATA_BUTTON_TEXT);
        removeAccountButton.setText(OPERATION_PANEL_YOUR_ACCOUNT_REMOVE_ACCOUNT_BUTTON_TEXT);
        dataPanel.changeMode(DATA_MODE);
    }
}

