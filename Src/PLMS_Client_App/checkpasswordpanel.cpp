#include"checkpasswordpanel.hpp"
#include"dialog.hpp"
#include"../PLMS_Server_App/user.hpp"
#include"windowmacros.hpp"
#include"mainmacros.hpp"
#include<QKeyEvent>


CheckPasswordPanel::CheckPasswordPanel(Dialog* parent, User* user)
    : QFrame(parent), parent(parent), user(user),
      titleLabel(DIALOG_CHECK_PASSWORD_PANEL_TITLE_TEXT,this),
      password(DIALOG_CHECK_PASSWORD_PANEL_PASSWORD_LABEL_TEXT, this),
      passwordLE(this),
      acceptButton(DIALOG_CHECK_PASSWORD_ACCEPT_BUTTON_TEXT, this),
      cancelButton(DIALOG_CHECK_PASSWORD_CANCEL_BUTTON_TEXT, this)
{
    setStyleSheet("CheckPasswordPanel{background: qlineargradient(x1:0, y1:1, x2:1, y2:0, stop:0 rgba(235, 235,235, 255),stop: 0.63 rgba(200, 200, 200, 255), stop: 1 rgba(210,210,210,255)); border-radius: 10px;border: 2px ridge grey;}");
    create();
}

CheckPasswordPanel::~CheckPasswordPanel(){
    // Empty
}

void CheckPasswordPanel::create(){
    titleLabel.setGeometry(DIALOG_CHECK_PASSWORD_PANEL_CHECK_PASSWORD_TITLE_X,DIALOG_CHECK_PASSWORD_PANEL_CHECK_PASSWORD_TITLE_Y,DIALOG_CHECK_PASSWORD_PANEL_CHECK_PASSWORD_TITLE_WIDTH,DIALOG_CHECK_PASSWORD_PANEL_CHECK_PASSWORD_TITLE_HEIGHT);
    titleLabel.setStyleSheet(STYLESHEET_TITLE);
    password.setStyleSheet(STYLESHEET_DATA_LABEL);
    password.setGeometry(DIALOG_CHECK_PASSWORD_PANEL_PASSWORD_LABEL_X,DIALOG_CHECK_PASSWORD_PANEL_PASSWORD_LABEL_Y,DIALOG_CHECK_PASSWORD_PANEL_PASSWORD_LABEL_WIDTH,DIALOG_CHECK_PASSWORD_PANEL_PASSWORD_LABEL_HEIGHT);
    passwordLE.setGeometry(DIALOG_CHECK_PASSWORD_PANEL_PASSWORD_LE_X,DIALOG_CHECK_PASSWORD_PANEL_PASSWORD_LE_Y,DIALOG_CHECK_PASSWORD_PANEL_PASSWORD_LE_WIDTH,DIALOG_CHECK_PASSWORD_PANEL_PASSWORD_LE_HEIGHT);
    passwordLE.setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
    passwordLE.setEchoMode(QLineEdit::Password);
    acceptButton.setGeometry(DIALOG_CHECK_PASSWORD_PANEL_ACCEPT_BUTTON_X,DIALOG_CHECK_PASSWORD_PANEL_ACCEPT_BUTTON_Y,DIALOG_CHECK_PASSWORD_PANEL_ACCEPT_BUTTON_WIDTH,DIALOG_CHECK_PASSWORD_PANEL_ACCEPT_BUTTON_HEIGHT);
    cancelButton.setGeometry(DIALOG_CHECK_PASSWORD_PANEL_CANCEL_BUTTON_X,DIALOG_CHECK_PASSWORD_PANEL_CANCEL_BUTTON_Y,DIALOG_CHECK_PASSWORD_PANEL_CANCEL_BUTTON_WIDTH,DIALOG_CHECK_PASSWORD_PANEL_CANCEL_BUTTON_HEIGHT);
    titleLabel.setAlignment(Qt::AlignCenter);
    acceptButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    cancelButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    acceptButton.setAlignment(Qt::AlignCenter);
    cancelButton.setAlignment(Qt::AlignCenter);
    passwordLE.installEventFilter(parent);
    acceptButton.installEventFilter(parent);
    cancelButton.installEventFilter(parent);
}

bool CheckPasswordPanel::eventMatching(QObject *obj, QEvent *ev){
    switch(ev->type()){
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
    case QEvent::KeyPress:
    {
        if(passwordLEKeyPressed(static_cast<QKeyEvent*>(ev))){
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


bool CheckPasswordPanel::passwordLEKeyPressed(QKeyEvent* ev){
    uint len = passwordLE.text().length();
    if(len > 29){
        switch(ev->key()){
        case Qt::Key_Left:
            return false;
        case Qt::Key_Right:
            return false;
        case Qt::Key_Backspace:
            passwordLE.backspace();
            break;
        case Qt::Key_Delete:
            passwordLE.del();
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
            passwordLE.backspace();
            break;
        case Qt::Key_Delete:
            passwordLE.del();
            break;
        default:
            passwordLE.insert(ev->text());
            break;
        }
    }
    len = passwordLE.text().length();
    if(passwordLE.text().isEmpty() || len > 30)
        passwordLE.setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
    else
        passwordLE.setStyleSheet("");
    return true;
}

void CheckPasswordPanel::acceptButtonPressed(){
    if(user->getParam(USER_PASSWORD) == passwordLE.text()){
        parent->done(ACCEPT_RESULT);
    }else{
        Dialog dlg(QUESTION_DIALOG, QString("Błędne hasło"), QString("Hasło niepoprawne"), nullptr, QString("Ok"));
        dlg.exec();
    }
}

void CheckPasswordPanel::cancelButtonPressed(){
    parent->done(CANCEL_RESULT);
}


