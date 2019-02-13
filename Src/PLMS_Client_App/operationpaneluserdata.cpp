#include"operationpaneluserdata.hpp"
#include<QLineEdit>
#include<QKeyEvent>
#include"appwindowloggedinpanel.hpp"
#include"app.hpp"
#include<QScrollBar>
#include"promptpanel.hpp"
#include"dialog.hpp"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include"../PLMS_Server_App/user.hpp"

OperationPanelUserData::OperationPanelUserData(AppWindowLoggedInPanel* parent)
    : LoggedInOperationPanel(parent),
      userDataTitleLabel(this),
      scrollArea(this),
      dataPanel(this, parent->getUserDataPtr(), DATA_MODE),
      bookPanelButton(this),
      changeDataButton(this),
      removeAccountButton(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationPanelUserData::~OperationPanelUserData(){
    disconnectAll();
    deleteWidgets();
}

void OperationPanelUserData::init(){
    // Empty
}

void OperationPanelUserData::setWindow(){
    // Empty
}

void OperationPanelUserData::createWidgets(){
    // Empty
}

void OperationPanelUserData::createLayout(){
    // Register Title Label
    userDataTitleLabel.setText(OPERATION_PANEL_USER_DATA_TITLE_TEXT);
    userDataTitleLabel.setGeometry(OPERATION_PANEL_USER_DATA_TITLE_X,OPERATION_PANEL_USER_DATA_TITLE_Y,OPERATION_PANEL_USER_DATA_TITLE_WIDTH,OPERATION_PANEL_USER_DATA_TITLE_HEIGHT);
    userDataTitleLabel.setAlignment(Qt::AlignCenter);
    userDataTitleLabel.setStyleSheet(STYLESHEET_TITLE);

    // User Data Panel
    dataPanel.setGeometry(OPERATION_PANEL_USER_DATA_PANEL_X,OPERATION_PANEL_USER_DATA_PANEL_Y,OPERATION_PANEL_USER_DATA_PANEL_WIDTH,OPERATION_PANEL_USER_DATA_PANEL_HEIGHT);

    // Scroll Area
    scrollArea.setStyleSheet("QScrollArea{background-color: transparent;}");
    scrollArea.verticalScrollBar()->setStyleSheet("QScrollBar::vertical{background: transparent; width: 5px;} QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical, QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical, QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{border: none; background: none; color: none;} QScrollBar::handle:vertical{background-color: white; border: 1px solid black;}");
    scrollArea.setFrameShape(QFrame::NoFrame);
    scrollArea.setWidget(&dataPanel);
    scrollArea.setGeometry(OPERATION_PANEL_USER_DATA_PANEL_X,OPERATION_PANEL_USER_DATA_PANEL_Y,OPERATION_PANEL_USER_DATA_PANEL_WIDTH,OPERATION_PANEL_USER_DATA_PANEL_HEIGHT);
    scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea.show();

    if(dataPanel.getMode() < DATA_MODE){
        // Book Panel Button Hide
        bookPanelButton.hide();
       // ChangeData Button
       changeDataButton.setGeometry(OPERATION_PANEL_ACCEPT_USER_DATA_EDIT_BUTTON_X,OPERATION_PANEL_ACCEPT_USER_DATA_EDIT_BUTTON_Y,OPERATION_PANEL_ACCEPT_USER_DATA_EDIT_BUTTON_WIDTH,OPERATION_PANEL_ACCEPT_USER_DATA_EDIT_BUTTON_HEIGHT);
       changeDataButton.setText(OPERATION_PANEL_USER_DATA_ACCEPT_BUTTON_TEXT);
        changeDataButton.setAlignment(Qt::AlignCenter);
        changeDataButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);

        // Remove Account Button
        removeAccountButton.setText(OPERATION_PANEL_USER_DATA_CANCEL_BUTTON_TEXT);
        removeAccountButton.setGeometry(OPERATION_PANEL_USER_DATA_EDIT_CANCEL_BUTTON_X,OPERATION_PANEL_USER_DATA_EDIT_CANCEL_BUTTON_Y,OPERATION_PANEL_USER_DATA_EDIT_CANCEL_BUTTON_WIDTH,OPERATION_PANEL_USER_DATA_EDIT_CANCEL_BUTTON_HEIGHT);
        removeAccountButton.setAlignment(Qt::AlignCenter);
        removeAccountButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    }else{

        // Book Panel Button
        bookPanelButton.setGeometry(OPERATION_PANEL_BOOK_PANEL_USER_DATA_BUTTON_X,OPERATION_PANEL_BOOK_PANEL_USER_DATA_BUTTON_Y,OPERATION_PANEL_BOOK_PANEL_USER_DATA_BUTTON_WIDTH,OPERATION_PANEL_BOOK_PANEL_USER_DATA_BUTTON_HEIGHT);
        bookPanelButton.setText(OPERATION_PANEL_BOOK_PANEL_USER_DATA_BUTTON_TEXT);
        bookPanelButton.setAlignment(Qt::AlignCenter);
        bookPanelButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
        bookPanelButton.show();


        // ChangeData Button
        changeDataButton.setGeometry(OPERATION_PANEL_CHANGE_DATA_USER_DATA_BUTTON_X,OPERATION_PANEL_CHANGE_DATA_USER_DATA_BUTTON_Y,OPERATION_PANEL_CHANGE_DATA_USER_DATA_BUTTON_WIDTH,OPERATION_PANEL_CHANGE_DATA_USER_DATA_BUTTON_HEIGHT);
        changeDataButton.setText(OPERATION_PANEL_CHANGE_DATA_USER_DATA_BUTTON_TEXT);
        changeDataButton.setAlignment(Qt::AlignCenter);
        changeDataButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);

        // Remove Account Button
        removeAccountButton.setText(OPERATION_PANEL_REMOVE_ACCOUNT_USER_DATA_BUTTON_TEXT);
        removeAccountButton.setGeometry(OPERATION_PANEL_USER_DATA_CANCEL_BUTTON_X,OPERATION_PANEL_USER_DATA_CANCEL_BUTTON_Y,OPERATION_PANEL_USER_DATA_CANCEL_BUTTON_WIDTH,OPERATION_PANEL_USER_DATA_CANCEL_BUTTON_HEIGHT);
        removeAccountButton.setAlignment(Qt::AlignCenter);
        removeAccountButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    }
}

void OperationPanelUserData::deleteWidgets(){
    // Empty
}

void OperationPanelUserData::connectAll(){
    // Book Panel Connect
    bookPanelButton.installEventFilter(this);

    // Register Button Connect
    changeDataButton.installEventFilter(this);

    // Cancel Button Connect
    removeAccountButton.installEventFilter(this);

}

void OperationPanelUserData::disconnectAll(){
    // Empty
}

void OperationPanelUserData::reload(){
    createLayout();
}

bool OperationPanelUserData::eventMatching(QObject* obj, QEvent* ev){
    switch (ev->type()) {
    case QEvent::MouseButtonRelease:
    {
        if(obj == &bookPanelButton){
            bookPanelButtonPressed();
            return true;
        }
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
        if(obj == &bookPanelButton){
            bookPanelButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
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
        if(obj == &bookPanelButton){
            bookPanelButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
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

void OperationPanelUserData::bookPanelButtonPressed(){
    if(dataPanel.getUser()){
        Dialog dlg(BOOK_PANEL, dataPanel.getUser(), parent);
        dlg.exec();
        reload();
    }else{
        Dialog dlg(QUESTION_DIALOG, QString("Błąd programu"), QString("Błąd pamięci programu"), nullptr, QString("Ok"));
        dlg.exec();
    }
}

void OperationPanelUserData::changeDataButtonPressed(){
    if(dataPanel.getMode() >= DATA_MODE){
        dataPanel.changeMode(EDITABLE_MODE);
        reload();
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
                            dataPanel.changeMode(DATA_MODE);
                            reload();
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

void OperationPanelUserData::removeAccountButtonPressed(){
    if(dataPanel.getMode() >= DATA_MODE){
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
                Dialog dlg(QUESTION_DIALOG, QString("Błąd programu"), QString("Błąd pamięci programu"), nullptr, QString("Ok"));
                dlg.exec();
                return;
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
                                parent->setAppWindowLoggedInStatus(parent->getLastAppWindowLoggedInStat(), true);

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
        dataPanel.changeMode(DATA_MODE);
        reload();
    }
}

