#include"appwindowregisterpanel.hpp"
#include<QLineEdit>
#include<QKeyEvent>
#include"appwindow.hpp"
#include"app.hpp"
#include<QScrollBar>
#include"dialog.hpp"
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include"server.hpp"
#include"../PLMS_Server_App/user.hpp"

AppWindowRegisterPanel::AppWindowRegisterPanel(AppWindow* parent)
    : AppWindowCentralPanel(parent),
      registerTitleLabel(this),      
      scrollArea(this),
      dataPanel(this, nullptr, REGISTER_MODE),
      registerButton(this),
      cancelButton(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

AppWindowRegisterPanel::~AppWindowRegisterPanel(){
    disconnectAll();
    deleteWidgets();
}

void AppWindowRegisterPanel::init(){
    // Empty
}

void AppWindowRegisterPanel::setWindow(){
    // Empty
}

void AppWindowRegisterPanel::createWidgets(){
    // Empty
}

void AppWindowRegisterPanel::createLayout(){
    // Register Title Label
    registerTitleLabel.setText(APP_WINDOW_REGISTER_PANEL_REGISTER_TITLE_TEXT);
    registerTitleLabel.setGeometry(APP_WINDOW_REGISTER_PANEL_REGISTER_TITLE_X, APP_WINDOW_REGISTER_PANEL_REGISTER_TITLE_Y, APP_WINDOW_REGISTER_PANEL_REGISTER_TITLE_WIDTH, APP_WINDOW_REGISTER_PANEL_REGISTER_TITLE_HEIGHT);
    registerTitleLabel.setStyleSheet(STYLESHEET_TITLE);
    registerTitleLabel.setAlignment(Qt::AlignCenter);

    // User Data Panel
    dataPanel.setGeometry(APP_WINDOW_REGISTER_PANEL_USER_DATA_PANEL_X, APP_WINDOW_REGISTER_PANEL_USER_DATA_PANEL_Y, APP_WINDOW_REGISTER_PANEL_USER_DATA_PANEL_WIDTH, APP_WINDOW_REGISTER_PANEL_USER_DATA_PANEL_HEIGHT);

    // Scroll Area
    scrollArea.setStyleSheet("background-color: transparent");
    scrollArea.verticalScrollBar()->setStyleSheet("QScrollBar::vertical{background: transparent; width: 5px;} QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical, QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical, QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{border: none; background: none; color: none;} QScrollBar::handle:vertical{background-color: white; border: 1px solid black;}");
    scrollArea.setFrameShape(QFrame::NoFrame);
    scrollArea.setWidget(&dataPanel);
    scrollArea.setGeometry(APP_WINDOW_REGISTER_PANEL_USER_DATA_PANEL_X, APP_WINDOW_REGISTER_PANEL_USER_DATA_PANEL_Y, APP_WINDOW_REGISTER_PANEL_USER_DATA_PANEL_WIDTH, APP_WINDOW_REGISTER_PANEL_USER_DATA_PANEL_HEIGHT);
    scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea.show();
    // Register Button
    registerButton.setGeometry(APP_WINDOW_REGISTER_PANEL_REGISTER_BUTTON_X, APP_WINDOW_REGISTER_PANEL_REGISTER_BUTTON_Y, APP_WINDOW_REGISTER_PANEL_REGISTER_BUTTON_WIDTH, APP_WINDOW_REGISTER_PANEL_REGISTER_BUTTON_HEIGHT);
    registerButton.setText(APP_WINDOW_REGISTER_PANEL_REGISTER_BUTTON_TEXT);
    registerButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    registerButton.setAlignment(Qt::AlignCenter);

    // Cancel Button
    cancelButton.setText(APP_WINDOW_REGISTER_PANEL_CANCEL_BUTTON_TEXT);
    cancelButton.setGeometry(APP_WINDOW_REGISTER_PANEL_CANCEL_BUTTON_X, APP_WINDOW_REGISTER_PANEL_CANCEL_BUTTON_Y, APP_WINDOW_REGISTER_PANEL_CANCEL_BUTTON_WIDTH, APP_WINDOW_REGISTER_PANEL_CANCEL_BUTTON_HEIGHT);
    cancelButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    cancelButton.setAlignment(Qt::AlignCenter);
}

void AppWindowRegisterPanel::deleteWidgets(){
    // Empty
}

void AppWindowRegisterPanel::connectAll(){
    // Register Button Connect
    registerButton.installEventFilter(this);

    // Cancel Button Connect
    cancelButton.installEventFilter(this);

}

void AppWindowRegisterPanel::disconnectAll(){
    // Empty
}

void AppWindowRegisterPanel::reload(){
    createLayout();
}

bool AppWindowRegisterPanel::eventMatching(QObject* obj, QEvent* ev){
    switch (ev->type()) {
    case QEvent::MouseButtonRelease:
    {
        if(obj == &registerButton){
            registerButtonPressed();
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
        if(obj == &registerButton){
            registerButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
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
        if(obj == &registerButton){
            registerButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
        if(obj == &cancelButton){
            cancelButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, ev);
}

void AppWindowRegisterPanel::registerButtonPressed(){
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
                if(parent->getParent()->getServer().getServerReplyStatus())
                    return;
            ServerReplyStatus srs = parent->getParent()->getServer().setLastRequest(COMMAND_TYPE_CLIENT_REGISTER_TEXT, POST, jDoc);
            switch (srs) {
            case SERVER_NO_ERROR:
            {
                parent->getPromptPanel().setServerStatusConnection();
                QJsonObject obj = parent->getParent()->getServer().readAll();
                if(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT) != QJsonValue::Undefined){
                    switch(static_cast<ReturnErrorType>(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt())){
                    case RETURN_ERROR_NO_ERROR:
                    {
                        // ______________________________________________________________________________________________________
                        if(obj.value(USER_JSON_KEY_TEXT) != QJsonValue::Undefined){
                            QJsonArray rjA = obj.value(USER_JSON_KEY_TEXT).toArray();
                            if(rjA.count() != 1){
                                //  Prompt Server Error
                                parent->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Podany użytkownik już istnieje."));
                            }else{
                                User* user = new User(rjA.at(0).toObject());
                                if(user->getUserId() != 0 && user->checkUserParameters()){
                                    parent->getParent()->addUser(user);
                                    parent->getParent()->setActiveUser(user);
                                    // Move to Logged In Stat
                                    parent->setAppWindowStat(APP_WINDOW_STAT_LOGGED_IN);
                                }else{
                                    SET_PTR_DO(user, nullptr);
                                    parent->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd przetwarzania danych - Tworzenie konta nieudane."));
                                }

                            }
                            // ______________________________________________________________________________________________________
                        }else{
                            //  Prompt Server Error
                            parent->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera - Tworzenie konta nieudane."));
                        }
                    }
                        break;
                        // _PH_ Check other errors
                    case RETURN_ERROR_USER_FOUND:
                    {
                        parent->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Podany użytkownik już istnieje."));
                    }
                        break;
                    default:
                        //  Prompt Server Error
                        parent->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - Tworzenie konta nieudane."));
                        break;
                    }
                }
                // _____________________________________________________________________________________________________________
               stop = true;
               parent->getParent()->getServer().clearStatus();
            }
                break;
            case SERVER_NETWORK_ERROR:
            {
                // __________________________________________________________________________________
                QNetworkReply::NetworkError error = parent->getParent()->getServer().getNetworkError();
                if(error == QNetworkReply::ConnectionRefusedError || error == QNetworkReply::TimeoutError){
                    parent->getPromptPanel().setServerStatusNoConnection();
                }
                // ____________________________________________________________________________________
                stop = true;
                parent->getParent()->getServer().clearStatus();
            }
                break;
            case SERVER_READY:
                stop = true;
                parent->getParent()->getServer().clearStatus();
                break;
            default:
                break;
            }
           }
        }
        SET_PTR_DO(userReg, nullptr);
    }
}

void AppWindowRegisterPanel::cancelButtonPressed(){
    parent->setAppWindowStat(APP_WINDOW_STAT_LOGIN);
}

