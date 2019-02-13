#include"addcommentpanel.hpp"
#include"dialog.hpp"
#include"operationpanelfilteredlist.hpp"
#include"../PLMS_Server_App/book.hpp"
#include"../PLMS_Server_App/bookcomment.hpp"
#include"windowmacros.hpp"
#include"mainmacros.hpp"
#include"appwindow.hpp"
#include"promptpanel.hpp"
#include"server.hpp"
#include"app.hpp"
#include<QKeyEvent>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>

AddCommentPanel::AddCommentPanel(Dialog* parent, Book* book, unsigned long long userId)
    : QFrame(parent), parent(parent), book(book), userId(userId),
      titleLabel(this),
      commentEdit(this),
      acceptButton(DIALOG_ADD_COMMENT_ACCEPT_BUTTON_TEXT, this),
      cancelButton(DIALOG_ADD_COMMENT_CANCEL_BUTTON_TEXT, this)
{
    setStyleSheet("AddCommentPanel{background: qlineargradient(x1:0, y1:1, x2:1, y2:0, stop:0 rgba(235, 235,235, 255),stop: 0.63 rgba(200, 200, 200, 255), stop: 1 rgba(210,210,210,255)); border-radius: 10px;border: 2px ridge grey;}");
    create();
}

AddCommentPanel::~AddCommentPanel(){
    // Empty
}

void AddCommentPanel::create(){
    uint len = book->getNumbOfBookComments();
    for(uint i = 0; i < len; i++)
        if((book->getBookComments() + i)->userId == userId){
            commentEdit.setText((book->getBookComments() + i)->content);
            break;
        }
    if(!commentEdit.toPlainText().isEmpty()){
        titleLabel.setText(DIALOG_EDIT_COMMENT_PANEL_TITLE_TEXT);        
    }else{
        titleLabel.setText(DIALOG_ADD_COMMENT_PANEL_TITLE_TEXT);
    }
    titleLabel.setGeometry(DIALOG_ADD_COMMENT_PANEL_ADD_COMMENT_TITLE_X,DIALOG_ADD_COMMENT_PANEL_ADD_COMMENT_TITLE_Y,DIALOG_ADD_COMMENT_PANEL_ADD_COMMENT_TITLE_WIDTH,DIALOG_ADD_COMMENT_PANEL_ADD_COMMENT_TITLE_HEIGHT);
    titleLabel.setStyleSheet(STYLESHEET_TITLE);
    commentEdit.setGeometry(DIALOG_ADD_COMMENT_PANEL_COMMENT_EDIT_X,DIALOG_ADD_COMMENT_PANEL_COMMENT_EDIT_Y,DIALOG_ADD_COMMENT_PANEL_COMMENT_EDIT_WIDTH,DIALOG_ADD_COMMENT_PANEL_COMMENT_EDIT_HEIGHT);
    acceptButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    acceptButton.setGeometry(DIALOG_ADD_COMMENT_PANEL_ACCEPT_BUTTON_X,DIALOG_ADD_COMMENT_PANEL_ACCEPT_BUTTON_Y,DIALOG_ADD_COMMENT_PANEL_ACCEPT_BUTTON_WIDTH,DIALOG_ADD_COMMENT_PANEL_ACCEPT_BUTTON_HEIGHT);
    cancelButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    cancelButton.setGeometry(DIALOG_ADD_COMMENT_PANEL_CANCEL_BUTTON_X,DIALOG_ADD_COMMENT_PANEL_CANCEL_BUTTON_Y,DIALOG_ADD_COMMENT_PANEL_CANCEL_BUTTON_WIDTH,DIALOG_ADD_COMMENT_PANEL_CANCEL_BUTTON_HEIGHT);
    titleLabel.setAlignment(Qt::AlignCenter);
    acceptButton.setAlignment(Qt::AlignCenter);
    cancelButton.setAlignment(Qt::AlignCenter);
    commentEdit.installEventFilter(parent);
    acceptButton.installEventFilter(parent);
    cancelButton.installEventFilter(parent);
}

bool AddCommentPanel::eventMatching(QObject *obj, QEvent *ev){
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
        if(commentEditKeyPressed(static_cast<QKeyEvent*>(ev))){
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


bool AddCommentPanel::commentEditKeyPressed(QKeyEvent* ev){
    switch(ev->key()){
    case Qt::Key_Left:
        return false;
    case Qt::Key_Right:
        return false;
    case Qt::Key_QuoteDbl:
        return true;
    case Qt::Key_Alt:
        return true;
    case Qt::Key_Shift:
        return true;
    case Qt::Key_Control:
        return true;
    default:
        break;
    }
    if(commentEdit.toPlainText().length() > 300){
        return true;
    }else{
        return false;
    }
}

void AddCommentPanel::acceptButtonPressed(){
    if(commentEdit.toPlainText() == QString("\"D\"") || commentEdit.toPlainText().isEmpty()){
        Dialog dlg(QUESTION_DIALOG, QString("Niedozwolony format"), QString("Komentarz nie może byc pusty ani frazą \"D\""), nullptr, QString("Ok"));
        dlg.exec();
    }else{
        Book *tempBook = new Book();
        tempBook->setBookId(book->getBookId());
        tempBook->addComment(userId, commentEdit.toPlainText());
        // Try to send comment
        AppWindow* appWindow = static_cast<AppWindow*>(parent->getParent());
        QJsonArray jA;
        QJsonObject userObj;
        tempBook->writeJson(userObj);
        jA.append(userObj);
        userObj = QJsonObject();
        userObj.insert(BOOK_JSON_KEY_TEXT, jA);
        QJsonDocument jDoc(userObj);
        bool stop = false;
        while(!stop){
            if(appWindow->getParent()->getServer().getServerReplyStatus())
                return;
        ServerReplyStatus srs = appWindow->getParent()->getServer().setLastRequest(COMMAND_TYPE_BOOK_COMMENT_ADD_EDIT_TEXT, POST, jDoc);
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
                    book->merge(*tempBook);
                    SET_PTR_DO(tempBook, nullptr);
                    parent->done(ACCEPT_RESULT);
                    // ___________________________________________________________________
                }
                    break;
                    // _PH_ Check other errors
                case RETURN_ERROR_USER_FOUND:
                {
                    appWindow->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Podany użytkownik już istnieje."));
                }
                    break;
                default:
                    //  Prompt Server Error
                    appWindow->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - Tworzenie konta nieudane."));
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
        SET_PTR_DO(tempBook, nullptr);
    }
}

void AddCommentPanel::cancelButtonPressed(){
    parent->done(CANCEL_RESULT);
}


