#include"appwindowloginpanel.hpp"
#include<QLineEdit>
#include<QKeyEvent>
#include"appwindow.hpp"
#include"app.hpp"
#include"dialog.hpp"
#include"server.hpp"
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include"promptpanel.hpp"
#include"../PLMS_Server_App/user.hpp"

AppWindowLoginPanel::AppWindowLoginPanel(AppWindow* parent)
    : AppWindowCentralPanel(parent),
      loginTitleLabel(this),
      loginNameLabel(this),
      loginNameField(true, nullptr, false, this, QString(), false),
      loginPasswordLabel(this),
      loginPasswordField(true, nullptr, false, this, QString(), false),
      passwordHiddenCB(this),
      loginButton(this),
      registerButton(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

AppWindowLoginPanel::~AppWindowLoginPanel(){
    disconnectAll();
    deleteWidgets();
}

void AppWindowLoginPanel::init(){
    passwordHiddenCB.setChecked(true);
}

void AppWindowLoginPanel::setWindow(){
    // Empty
}

void AppWindowLoginPanel::createWidgets(){
    // Empty
}

void AppWindowLoginPanel::createLayout(){
    // Login Title Label Layout
    loginTitleLabel.setText(APP_WINDOW_LOGIN_PANEL_LOGIN_TITLE_TEXT);
    loginTitleLabel.setGeometry(APP_WINDOW_LOGIN_PANEL_LOGIN_TITLE_X, APP_WINDOW_LOGIN_PANEL_LOGIN_TITLE_Y, APP_WINDOW_LOGIN_PANEL_LOGIN_TITLE_WIDTH, APP_WINDOW_LOGIN_PANEL_LOGIN_TITLE_HEIGHT);
    loginTitleLabel.setStyleSheet(STYLESHEET_TITLE);
    loginTitleLabel.setAlignment(Qt::AlignCenter);

    // Login Name Label Layout
    loginNameLabel.setText(APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_TEXT);
    loginNameLabel.setGeometry(APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_LABEL_X, APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_LABEL_Y, APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_LABEL_WIDTH, APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_LABEL_HEIGHT);
    loginNameLabel.setStyleSheet(STYLESHEET_DATA_LABEL);

    // Login Name Field Layout
    loginNameField.setGeometry(APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_FIELD_X, APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_FIELD_Y, APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_FIELD_WIDTH, APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_FIELD_HEIGHT);
    loginNameField.getDataUTextEdit()->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);

    // Login Password Label Layout
    loginPasswordLabel.setText(APP_WINDOW_LOGIN_PANEL_LOGIN_PASSWORD_TEXT);
    loginPasswordLabel.setGeometry(APP_WINDOW_LOGIN_PANEL_PASSWORD_LABEL_X, APP_WINDOW_LOGIN_PANEL_PASSWORD_LABEL_Y, APP_WINDOW_LOGIN_PANEL_PASSWORD_LABEL_WIDTH, APP_WINDOW_LOGIN_PANEL_PASSWORD_LABEL_HEIGHT);
    loginPasswordLabel.setStyleSheet(STYLESHEET_DATA_LABEL);

    // Login Password Field Layout
    loginPasswordField.setGeometry(APP_WINDOW_LOGIN_PANEL_PASSWORD_FIELD_X, APP_WINDOW_LOGIN_PANEL_PASSWORD_FIELD_Y, APP_WINDOW_LOGIN_PANEL_PASSWORD_FIELD_WIDTH, APP_WINDOW_LOGIN_PANEL_PASSWORD_FIELD_HEIGHT);
    loginPasswordField.getDataUTextEdit()->setEchoMode(QLineEdit::Password);
    loginPasswordField.getDataUTextEdit()->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);

    // Login Password Hidden CheckBox
    passwordHiddenCB.setText(APP_WINDOW_LOGIN_PANEL_LOGIN_PASSWORD_HIDDEN_TEXT);
    passwordHiddenCB.setGeometry(APP_WINDOW_LOGIN_PANEL_PASSWORD_HIDDEN_CHECKBOX_X, APP_WINDOW_LOGIN_PANEL_PASSWORD_HIDDEN_CHECKBOX_Y, APP_WINDOW_LOGIN_PANEL_PASSWORD_HIDDEN_CHECKBOX_WIDTH, APP_WINDOW_LOGIN_PANEL_PASSWORD_HIDDEN_CHECKBOX_HEIGHT);
    passwordHiddenCB.setChecked(true);
    passwordHiddenCB.setStyleSheet(STYLESHEET_DATA_LABEL);

    // Login Button Text
    loginButton.setText(APP_WINDOW_LOGIN_PANEL_LOGIN_BUTTON_TEXT);
    loginButton.setGeometry(APP_WINDOW_LOGIN_PANEL_LOGIN_BUTTON_X, APP_WINDOW_LOGIN_PANEL_LOGIN_BUTTON_Y, APP_WINDOW_LOGIN_PANEL_LOGIN_BUTTON_WIDTH, APP_WINDOW_LOGIN_PANEL_LOGIN_BUTTON_HEIGHT);
    loginButton.setAlignment(Qt::AlignCenter);
    loginButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);

    // Register Button Text
    registerButton.setText(APP_WINDOW_LOGIN_PANEL_REGISTER_BUTTON_TEXT);
    registerButton.setGeometry(APP_WINDOW_LOGIN_PANEL_REGISTER_BUTTON_X, APP_WINDOW_LOGIN_PANEL_REGISTER_BUTTON_Y, APP_WINDOW_LOGIN_PANEL_REGISTER_BUTTON_WIDTH, APP_WINDOW_LOGIN_PANEL_REGISTER_BUTTON_HEIGHT);
    registerButton.setAlignment(Qt::AlignCenter);
    registerButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
}

void AppWindowLoginPanel::deleteWidgets(){
    // Empty
}

void AppWindowLoginPanel::connectAll(){
    // Login Name Field Connect
    loginNameField.installEventFilter(this);

    // Login Password Field Connect
    loginPasswordField.installEventFilter(this);

    // Password Hidden Check Box Connect
    passwordHiddenCB.installEventFilter(this);

    // Login Button Connect
    loginButton.installEventFilter(this);

    // Register Button Connect
    registerButton.installEventFilter(this);
}

void AppWindowLoginPanel::disconnectAll(){
    // Empty
}

void AppWindowLoginPanel::loginButtonPressed(){
    QString login = loginNameField.getDataUTextEdit()->text();
    QString password = loginPasswordField.getDataUTextEdit()->text();
    if(!login.isEmpty() && !password.isEmpty()){
        // Check there is logged in user, then check user's password
        User** users = parent->getParent()->getUsers();
        uint numbOfUsers = parent->getParent()->getNumbOfUsers();
        for(uint i = 0; i< numbOfUsers; i++)
            if((*(users + i))->getUserName() == login){
                if((*(users + i))->getParam(USER_PASSWORD) == password){
                    parent->getParent()->setActiveUser(*(users + i));
                    parent->setAppWindowStat(APP_WINDOW_STAT_LOGGED_IN);
                }else{
                    Dialog dlg(QUESTION_DIALOG, QString("Błąd logowania"), QString("Hasło jest nieprawidłowe"), nullptr, QString("Ok"));
                    dlg.exec();
                }
                return;
            }
        // There is no user with user name
        // Create Json User
        {
            QJsonArray jA;
            QJsonObject userObj;
            userObj.insert(USER_PARAMETERS_USER_NAME, login);
            userObj.insert(USER_PARAMETERS_USER_PASSWORD, password);
            jA.append(userObj);
            userObj = QJsonObject();
            userObj.insert(USER_JSON_KEY_TEXT, jA);
            QJsonDocument jDoc(userObj);
            bool stop = false;
            while(!stop){
                if(parent->getParent()->getServer().getServerReplyStatus())
                    return;
            ServerReplyStatus srs = parent->getParent()->getServer().setLastRequest(COMMAND_TYPE_CLIENT_LOGIN_TEXT, POST, jDoc);
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
                                Dialog dlg(QUESTION_DIALOG, QString("Błąd logowania"), QString("Błędne dane logowania - brak użykownika lub błędne hasło."), nullptr, QString("Ok"));
                                dlg.exec();
                            }else{
                                User* user = new User(rjA.at(0).toObject());
                                if(user->getUserId() != 0 && user->checkUserParameters()){
                                    parent->getParent()->addUser(user);
                                    parent->getParent()->setActiveUser(user);
                                    // Move to Logged In Stat
                                    parent->setAppWindowStat(APP_WINDOW_STAT_LOGGED_IN);
                                }else{
                                    SET_PTR_DO(user, nullptr);
                                    parent->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd przetwarzania danych - logowanie nieudane."));
                                 }
                            }
                            // ______________________________________________________________________________________________________
                        }else{
                            //  Prompt Server Error
                            parent->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera - logowanie nieudane."));
                        }
                    }
                        break;
                        // _PH_ Check other errors
                    case RETURN_ERROR_USER_NOT_FOUND:
                        {
                            Dialog dlg(QUESTION_DIALOG, QString("Błąd logowania"), QString("Błędne dane logowania."), nullptr, QString("Ok"));
                            dlg.exec();
                        }
                        break;
                    default:
                        //  Prompt Server Error
                        parent->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - logowanie nieudane."));
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
    }
}

void AppWindowLoginPanel::registerButtonPressed(){
    parent->setAppWindowStat(APP_WINDOW_STAT_REGISTER);
}

void AppWindowLoginPanel::passwordHiddenCBPressed(){
    passwordHiddenCB.setChecked(!passwordHiddenCB.isChecked());
    if(passwordHiddenCB.isChecked()){
        // Go to hide password state
        loginPasswordField.getDataUTextEdit()->setEchoMode(QLineEdit::Password);
    }else{
        // Go to no hide password state
        loginPasswordField.getDataUTextEdit()->setEchoMode(QLineEdit::Normal);
    }
}

bool AppWindowLoginPanel::loginNameFieldKeyPressed(QKeyEvent* ev){
    QLineEdit* le = loginNameField.getDataUTextEdit();
    uint len = le->text().length();
    if(len > 29){
        switch(ev->key()){
        case Qt::Key_Left:
            return false;
        case Qt::Key_Right:
            return false;
        case Qt::Key_Backspace:
            le->backspace();
            break;
        case Qt::Key_Delete:
            le->del();
            break;
        default:
            return true;
        }
    }
    else{
        switch(ev->key()){
        case Qt::Key_Left:
            return false;
        case Qt::Key_Right:
            return false;
        case Qt::Key_Enter:
            return true;
        case Qt::Key_Tab:
            return true;
        case Qt::Key_Slash:
            return true;
        case Qt::Key_Backslash:
            return true;
        case Qt::Key_Return:
            return true;
        case Qt::Key_Colon:
            return true;
        case Qt::Key_Asterisk:
            return true;
        case Qt::Key_Less:
            return true;
        case Qt::Key_Greater:
            return true;
        case Qt::Key_QuoteDbl:
            return true;
        case Qt::Key_Question:
            return true;
        case Qt::Key_Bar:
            return true;
        case Qt::Key_Alt:
            return true;
        case Qt::Key_Shift:
            return true;
        case Qt::Key_Space:
            return true;
        case Qt::Key_Control:
            return true;
        case Qt::Key_Backspace:
            le->backspace();
            break;
        case Qt::Key_Delete:
            le->del();
            break;
        default:
            le->insert(ev->text());
            break;
        }
    }
    len = le->text().length();
    if(le->text().isEmpty() || len > 30)
        le->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
    else
        le->setStyleSheet("");
    return true;
}

bool AppWindowLoginPanel::loginPasswordKeyPressed(QKeyEvent* ev){
    QLineEdit* le = loginPasswordField.getDataUTextEdit();
    uint len = le->text().length();
    if(len > 29){
        switch(ev->key()){
        case Qt::Key_Left:
            return false;
        case Qt::Key_Right:
            return false;
        case Qt::Key_Backspace:
            le->backspace();
            break;
        case Qt::Key_Delete:
            le->del();
            break;
        default:
            return true;
        }
    }
    else{
        switch(ev->key()){
        case Qt::Key_Left:
            return false;
        case Qt::Key_Right:
            return false;
        case Qt::Key_Enter:
            return true;
        case Qt::Key_Tab:
            return true;
        case Qt::Key_Slash:
            return true;
        case Qt::Key_Backslash:
            return true;
        case Qt::Key_Return:
            return true;
        case Qt::Key_Colon:
            return true;
        case Qt::Key_Asterisk:
            return true;
        case Qt::Key_Less:
            return true;
        case Qt::Key_Greater:
            return true;
        case Qt::Key_QuoteDbl:
            return true;
        case Qt::Key_Question:
            return true;
        case Qt::Key_Bar:
            return true;
        case Qt::Key_Alt:
            return true;
        case Qt::Key_Shift:
            return true;
        case Qt::Key_Control:
            return true;
        case Qt::Key_Space:
            return true;
        case Qt::Key_Backspace:
            le->backspace();
            break;
        case Qt::Key_Delete:
            le->del();
            break;
        default:
            le->insert(ev->text());
            break;
        }
    }    
    len = le->text().length();
    if(le->text().isEmpty() || len > 30)
        le->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
    else
        le->setStyleSheet("");
    return true;
}

void AppWindowLoginPanel::reload(){
    createLayout();
}

bool AppWindowLoginPanel::eventMatching(QObject* obj, QEvent* ev){
    switch (ev->type()) {
    case QEvent::MouseButtonRelease:
    {
        if(obj == &loginButton){
            loginButtonPressed();
            return true;
        }
        if(obj == &registerButton){
            registerButtonPressed();
            return true;
        }
        if(obj == &passwordHiddenCB){
            passwordHiddenCBPressed();
            return true;
        }
    }
        break;
    case QEvent::KeyPress:
    {
        if(obj == loginNameField.getDataUTextEdit()){
            if(loginNameFieldKeyPressed(static_cast<QKeyEvent*>(ev)))
                return true;
        }
        if(obj == loginPasswordField.getDataUTextEdit()){
            if(loginPasswordKeyPressed(static_cast<QKeyEvent*>(ev)))
                return true;
        }
    }
        break;
    case QEvent::Enter:
    {
        if(obj == &loginButton){
            loginButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
        if(obj == &registerButton){
            registerButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &loginButton){
            loginButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
        if(obj == &registerButton){
            registerButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, ev);
}


