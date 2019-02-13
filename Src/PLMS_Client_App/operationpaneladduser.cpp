#include"operationpaneladduser.hpp"
#include<QLineEdit>
#include<QKeyEvent>
#include"appwindowloggedinpanel.hpp"
#include"app.hpp"
#include<QScrollBar>
#include"dialog.hpp"
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include"../PLMS_Server_App/user.hpp"

OperationPanelAddUser::OperationPanelAddUser(AppWindowLoggedInPanel* parent)
    : LoggedInOperationPanel(parent),
      addUserTitleLabel(this),
      scrollArea(this),
      dataPanel(this, nullptr, (parent->getUser()->getUserPermissions() == USER_PERMISSIONS_ADMIN)? ADMIN_REGISTER_MODE : REGISTER_MODE),
      addButton(this),
      cancelButton(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationPanelAddUser::~OperationPanelAddUser(){
    disconnectAll();
    deleteWidgets();
}

void OperationPanelAddUser::init(){
    // Empty
}

void OperationPanelAddUser::setWindow(){
    // Empty
}

void OperationPanelAddUser::createWidgets(){
    // Empty
}

void OperationPanelAddUser::createLayout(){
    // Register Title Label
    addUserTitleLabel.setText(OPERATION_PANEL_ADD_USER_TITLE_TEXT);
    addUserTitleLabel.setGeometry(OPERATION_PANEL_ADD_USER_TITLE_X,OPERATION_PANEL_ADD_USER_TITLE_Y,OPERATION_PANEL_ADD_USER_TITLE_WIDTH,OPERATION_PANEL_ADD_USER_TITLE_HEIGHT);
    addUserTitleLabel.setAlignment(Qt::AlignCenter);
    addUserTitleLabel.setStyleSheet(STYLESHEET_TITLE);

    // User Data Panel
    dataPanel.setGeometry(OPERATION_PANEL_ADD_USER_DATA_PANEL_X,OPERATION_PANEL_ADD_USER_DATA_PANEL_Y,OPERATION_PANEL_ADD_USER_DATA_PANEL_WIDTH,OPERATION_PANEL_ADD_USER_DATA_PANEL_HEIGHT);

    // Scroll Area
    scrollArea.setStyleSheet("QScrollArea{background-color: transparent;}");
    scrollArea.verticalScrollBar()->setStyleSheet("QScrollBar::vertical{background: transparent; width: 5px;} QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical, QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical, QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{border: none; background: none; color: none;} QScrollBar::handle:vertical{background-color: white; border: 1px solid black;}");
    scrollArea.setFrameShape(QFrame::NoFrame);
    scrollArea.setWidget(&dataPanel);
    scrollArea.setGeometry(OPERATION_PANEL_ADD_USER_DATA_PANEL_X,OPERATION_PANEL_ADD_USER_DATA_PANEL_Y,OPERATION_PANEL_ADD_USER_DATA_PANEL_WIDTH,OPERATION_PANEL_ADD_USER_DATA_PANEL_HEIGHT);
    scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea.show();
    // Add Button
    addButton.setGeometry(OPERATION_PANEL_ADD_USER_BUTTON_X,OPERATION_PANEL_ADD_USER_BUTTON_Y,OPERATION_PANEL_ADD_USER_BUTTON_WIDTH,OPERATION_PANEL_ADD_USER_BUTTON_HEIGHT);
    addButton.setText(OPERATION_PANEL_ADD_USER_ADD_BUTTON_TEXT);
    addButton.setAlignment(Qt::AlignCenter);
    addButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);

    // Cancel Button
    cancelButton.setText(OPERATION_PANEL_ADD_USER_CANCEL_BUTTON_TEXT);
    cancelButton.setGeometry(OPERATION_PANEL_ADD_USER_CANCEL_BUTTON_X,OPERATION_PANEL_ADD_USER_CANCEL_BUTTON_Y,OPERATION_PANEL_ADD_USER_CANCEL_BUTTON_WIDTH,OPERATION_PANEL_ADD_USER_CANCEL_BUTTON_HEIGHT);
    cancelButton.setAlignment(Qt::AlignCenter);
    cancelButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);

}

void OperationPanelAddUser::deleteWidgets(){
    // Empty
}

void OperationPanelAddUser::connectAll(){
    // Register Button Connect
    addButton.installEventFilter(this);

    // Cancel Button Connect
    cancelButton.installEventFilter(this);

}

void OperationPanelAddUser::disconnectAll(){
    // Empty
}

void OperationPanelAddUser::reload(){
    createLayout();
}

bool OperationPanelAddUser::eventMatching(QObject* obj, QEvent* ev){
    switch (ev->type()) {
    case QEvent::MouseButtonRelease:
    {
        if(obj == &addButton){
            addButtonPressed();
            return true;
        }
        if(obj == &cancelButton){
            cancelButtonPressed();
            return true;
        }
    }
        break;
    case QEvent::Enter:
    {
        if(obj == &addButton){
            addButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
        if(obj == &cancelButton){
            cancelButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &addButton){
            addButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
        if(obj == &cancelButton){
            cancelButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, ev);
}

void OperationPanelAddUser::addButtonPressed(){
    if(!dataPanel.checkData()){
        Dialog dlg(QUESTION_DIALOG, QString("Błąd danych"), QString("Niepoprawnie wypełniony formularz."), nullptr, QString("Ok"));
        dlg.exec();
        return;
    }else{
        // Try to register
        User* userReg = dataPanel.getTempUser();
        // Create Json User
        {
            QJsonArray jA;
            QJsonObject userObj;
            userReg->writeJson(userObj);
            jA.append(userObj);
            userObj = QJsonObject();
            userObj.insert(USER_JSON_KEY_TEXT, jA);
            QJsonDocument jDoc(userObj);
            bool stop = false;
            while(!stop){
                if(parent->getParent()->getParent()->getServer().getServerReplyStatus())
                    return;
            ServerReplyStatus srs = parent->getParent()->getParent()->getServer().setLastRequest(COMMAND_TYPE_CLIENT_ADD_TEXT, POST, jDoc);
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
                        if(obj.value(USER_JSON_KEY_TEXT) != QJsonValue::Undefined){
                            QJsonArray rjA = obj.value(USER_JSON_KEY_TEXT).toArray();
                            if(rjA.count() != 1){
                                //  Prompt Server Error
                                parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Podany użytkownik już istnieje."));
                            }else{
                                User* user = new User(rjA.at(0).toObject());
                                if(user->getUserId() != 0 && user->checkUserParameters()){
                                    parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT, true);
                                }else{
                                    parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd przetwarzania danych - Tworzenie konta nieudane."));
                                }
                            }
                            // ______________________________________________________________________________________________________
                        }else{
                            //  Prompt Server Error
                            parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera - Tworzenie konta nieudane."));
                        }
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
        }
        SET_PTR_DO(userReg, nullptr);
    }
}

void OperationPanelAddUser::cancelButtonPressed(){
    parent->setAppWindowLoggedInStatus(parent->getLastAppWindowLoggedInStat(), true);
}

