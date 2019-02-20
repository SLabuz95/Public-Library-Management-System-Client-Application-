#include"changepasswordpanel.hpp"
#include"dialog.hpp"
#include"../PLMS_Server_App/user.hpp"
#include"windowmacros.hpp"
#include"mainmacros.hpp"
#include"appwindow.hpp"
#include"promptpanel.hpp"
#include"server.hpp"
#include"app.hpp"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>

ChangePasswordPanel::ChangePasswordPanel(Dialog* parent, User* user)
    : QFrame(parent), parent(parent), user(user),
      title(DIALOG_CHANGE_PASSWORD_TITLE_LABEL_TEXT,this),
      oldPasswordLabel(DIALOG_CHANGE_PASSWORD_OLD_PASS_LABEL_TEXT, this),
      oldPasswordLE(this),
      newPasswordLabel(DIALOG_CHANGE_PASSWORD_NEW_PASS_LABEL_TEXT, this),
      newPasswordLE(this),
      acceptButton(DIALOG_CHANGE_PASSWORD_ACCEPT_BUTTON_TEXT, this),
      cancelButton(DIALOG_CHANGE_PASSWORD_CANCEL_BUTTON_TEXT, this)
{
    setStyleSheet("ChangePasswordPanel{background: qlineargradient(x1:0, y1:1, x2:1, y2:0, stop:0 rgba(235, 235,235, 255),stop: 0.63 rgba(200, 200, 200, 255), stop: 1 rgba(210,210,210,255)); border-radius: 10px;border: 2px ridge grey;}");
    create();
}

ChangePasswordPanel::~ChangePasswordPanel(){

}

void ChangePasswordPanel::create(){
    title.setGeometry(DIALOG_CHANGE_PASSWORD_PANEL_TITLE_LABEL_X, DIALOG_CHANGE_PASSWORD_PANEL_TITLE_LABEL_Y,DIALOG_CHANGE_PASSWORD_PANEL_TITLE_LABEL_WIDTH,DIALOG_CHANGE_PASSWORD_PANEL_TITLE_LABEL_HEIGHT);
    title.setStyleSheet(STYLESHEET_TITLE);
    title.setAlignment(Qt::AlignCenter);
    oldPasswordLabel.setGeometry(DIALOG_CHANGE_PASSWORD_PANEL_OLD_PASS_LABEL_X,DIALOG_CHANGE_PASSWORD_PANEL_OLD_PASS_LABEL_Y,DIALOG_CHANGE_PASSWORD_PANEL_OLD_PASS_LABEL_WIDTH,DIALOG_CHANGE_PASSWORD_PANEL_OLD_PASS_LABEL_HEIGHT);
    oldPasswordLE.setGeometry(DIALOG_CHANGE_PASSWORD_PANEL_OLD_PASS_LE_X,DIALOG_CHANGE_PASSWORD_PANEL_OLD_PASS_LE_Y,DIALOG_CHANGE_PASSWORD_PANEL_OLD_PASS_LE_WIDTH,DIALOG_CHANGE_PASSWORD_PANEL_OLD_PASS_LE_HEIGHT);
    oldPasswordLE.setEchoMode(QLineEdit::Password);
        newPasswordLabel.setGeometry(DIALOG_CHANGE_PASSWORD_PANEL_NEW_PASS_LABEL_X,DIALOG_CHANGE_PASSWORD_PANEL_NEW_PASS_LABEL_Y,DIALOG_CHANGE_PASSWORD_PANEL_NEW_PASS_LABEL_WIDTH,DIALOG_CHANGE_PASSWORD_PANEL_NEW_PASS_LABEL_HEIGHT);
    newPasswordLE.setGeometry(DIALOG_CHANGE_PASSWORD_PANEL_NEW_PASS_LE_X,DIALOG_CHANGE_PASSWORD_PANEL_NEW_PASS_LE_Y,DIALOG_CHANGE_PASSWORD_PANEL_NEW_PASS_LE_WIDTH,DIALOG_CHANGE_PASSWORD_PANEL_NEW_PASS_LE_HEIGHT);
    oldPasswordLE.setEchoMode(QLineEdit::Password);
    acceptButton.setGeometry(DIALOG_CHANGE_PASSWORD_PANEL_ACCEPT_BUTTON_X,DIALOG_CHANGE_PASSWORD_PANEL_ACCEPT_BUTTON_Y,DIALOG_CHANGE_PASSWORD_PANEL_ACCEPT_BUTTON_WIDTH,DIALOG_CHANGE_PASSWORD_PANEL_ACCEPT_BUTTON_HEIGHT);
    cancelButton.setGeometry(DIALOG_CHANGE_PASSWORD_PANEL_CANCEL_BUTTON_X,DIALOG_CHANGE_PASSWORD_PANEL_CANCEL_BUTTON_Y, DIALOG_CHANGE_PASSWORD_PANEL_CANCEL_BUTTON_WIDTH,DIALOG_CHANGE_PASSWORD_PANEL_CANCEL_BUTTON_HEIGHT);
    acceptButton.setAlignment(Qt::AlignCenter);
    cancelButton.setAlignment(Qt::AlignCenter);
    oldPasswordLabel.setStyleSheet(STYLESHEET_DATA_LABEL);
    newPasswordLabel.setStyleSheet(STYLESHEET_DATA_LABEL);
    oldPasswordLE.setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
    newPasswordLE.setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
    acceptButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    cancelButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    oldPasswordLE.installEventFilter(parent);
    newPasswordLE.installEventFilter(parent);
    acceptButton.installEventFilter(parent);
    cancelButton.installEventFilter(parent);
}

bool ChangePasswordPanel::eventMatching(QObject *obj, QEvent *ev){
    switch(ev->type()){
    case QEvent::KeyPress:
    {
        if(obj == &oldPasswordLE){
            if(standardLEKeyPressed(static_cast<QKeyEvent*>(ev), &oldPasswordLE))
                return true;
        }
        if(obj == &newPasswordLE){
            if(standardLEKeyPressed(static_cast<QKeyEvent*>(ev), &newPasswordLE))
                return true;
        }
    }
        break;
    case QEvent::MouseButtonRelease:
    {
        if(obj == &acceptButton){
            acceptButtonPressed();
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
        if(obj == &acceptButton){
            acceptButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
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
        if(obj == &acceptButton){
            acceptButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
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
    return false;
}

bool ChangePasswordPanel::standardLEKeyPressed(QKeyEvent *ev, QLineEdit *le){
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
    if(le->text().isEmpty() || len > 30){
        le->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
    }    else{
        le->setStyleSheet("");
    }
    return true;
}

void ChangePasswordPanel::acceptButtonPressed(){
    if(user && user->getParam(USER_PASSWORD) == oldPasswordLE.text()){
        AppWindow* appWindow = static_cast<AppWindow*>(parent->getParent());
        User* userEdit = new User();
        if(user)
        userEdit->setUserId(user->getUserId());
        userEdit->setParam(USER_PASSWORD, newPasswordLE.text());
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
                if(appWindow->getParent()->getServer().getServerReplyStatus()){
                    SET_PTR_DO(userEdit, nullptr);
                    return;
                }
            ServerReplyStatus srs = appWindow->getParent()->getServer().setLastRequest(COMMAND_TYPE_CLIENT_EDIT_TEXT, POST, jDoc);
            switch (srs) {
            case SERVER_NO_ERROR:
            {
                appWindow->getPromptPanel().setServerStatusConnection();
                QJsonObject obj = appWindow->getParent()->getServer().readAll();
                if(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT) != QJsonValue::Undefined){
                    switch(static_cast<ReturnErrorType>(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt())){
                    case RETURN_ERROR_NO_ERROR:
                    {
                        // ______________________________________________________________________________________________________
                         parent->done(ACCEPT_RESULT);
                        // ___________________________________________________________________
                    }
                        break;
                        // _PH_ Check other errors
                    default:
                        //  Prompt Server Error
                        appWindow->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - Zmiana hasła nieudana."));
                        break;
                    }
                }
                // _____________________________________________________________________________________________________________
               stop = true;
               appWindow->getParent()->getServer().clearStatus();
            }
                break;
            case SERVER_NETWORK_ERROR:
            {
                // __________________________________________________________________________________
                QNetworkReply::NetworkError error = appWindow->getParent()->getServer().getNetworkError();
                if(error == QNetworkReply::ConnectionRefusedError || error == QNetworkReply::TimeoutError){
                    appWindow->getPromptPanel().setServerStatusNoConnection();
                }
                // ____________________________________________________________________________________
                stop = true;
                appWindow->getParent()->getServer().clearStatus();
            }
                break;
            case SERVER_READY:
                stop = true;
                appWindow->getParent()->getServer().clearStatus();
                break;
            default:
                break;
            }
           }
        }
        SET_PTR_DO(userEdit, nullptr);
    }else{
        Dialog dlg(QUESTION_DIALOG, QString("Błędne hasło"), QString("Stare hasło jest niepoprawne."), nullptr, QString("Ok"));
        dlg.exec();
    }
}

void ChangePasswordPanel::cancelButtonPressed(){
    parent->done(CANCEL_RESULT);
}
