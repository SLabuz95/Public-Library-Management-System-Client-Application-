#include"commentlistelement.hpp"
#include"commentlist.hpp"
#include"../PLMS_Server_App/book.hpp"
#include"../PLMS_Server_App/bookcomment.hpp"
#include"../PLMS_Server_App/user.hpp"
#include<QEvent>
#include<QLabel>
#include"dialog.hpp"
#include"operationlistelement.hpp"
#include"operationlist.hpp"
#include"filteredlist.hpp"
#include"operationpanelfilteredlist.hpp"
#include"appwindowloggedinpanel.hpp"
#include"appwindow.hpp"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include"promptpanel.hpp"
#include"server.hpp"
#include"app.hpp"

CommentListElement::CommentListElement(CommentList *parent, Book* book, uint commentIndex)
    : QFrame (parent), parent(parent), commentLabel(this), deleteButton(this), book(book){
    init(*book, commentIndex);
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

CommentListElement::~CommentListElement(){
    disconnectAll();
    deleteWidgets();
}

void CommentListElement::init(Book &book, uint index){
    userId = (*(book.getBookComments() + index)).userId;
    generateText((*(book.getBookComments() + index)).content);
}

void CommentListElement::setWindow(){
    setStyleSheet("CommentListElement{background-color: rgba(245, 245, 245, 0.5); border: 1px solid rgba(230,230,230, 0.8); border-radius: 3px;}");
    resize(COMMENT_ELEMENT_WIDTH,commentLabel.height() + 2 * OPERATION_ELEMENT_VERTICAL_SIDE_OFFSET);
}

void CommentListElement::createWidgets(){
    // Brak
}

void CommentListElement::createLayout(){
    User *user = parent->getParent()->getParent()->getParent()->getParent()->getParent()->getUser();
    if(userId != user->getUserId() && user->getUserPermissions() == USER_PERMISSIONS_READER)
        deleteButton.hide();
    commentLabel.move(OPERATION_ELEMENT_HORIZONTAL_SIDE_OFFSET,OPERATION_ELEMENT_VERTICAL_SIDE_OFFSET);
    deleteButton.setPixmap(PROMPT_PANEL_CLOSE_BUTTON_PIXMAP);
    deleteButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    deleteButton.setGeometry(COMMENT_ELEMENT_WIDTH - OPERATION_ELEMENT_BUTTON_WIDTH - OPERATION_ELEMENT_HORIZONTAL_SIDE_OFFSET, OPERATION_ELEMENT_VERTICAL_SIDE_OFFSET, OPERATION_ELEMENT_BUTTON_WIDTH, OPERATION_ELEMENT_BUTTON_HEIGHT);
    deleteButton.setScaledContents(true);
}

void CommentListElement::deleteWidgets(){
    // Brak
}

void CommentListElement::connectAll(){
    deleteButton.installEventFilter(parent);
}

void CommentListElement::disconnectAll(){
    // Brak
}

void CommentListElement::generateText(QString &str){
    uint newHeight = commentLabel.fontMetrics().boundingRect(0,0, COMMENT_ELEMENT_WIDTH - OPERATION_ELEMENT_BUTTON_WIDTH - 2 * OPERATION_ELEMENT_HORIZONTAL_SIDE_OFFSET, 1200, Qt::TextWordWrap, str).height();
    commentLabel.resize(COMMENT_ELEMENT_WIDTH - OPERATION_ELEMENT_BUTTON_WIDTH - 2 * OPERATION_ELEMENT_HORIZONTAL_SIDE_OFFSET, (newHeight < PROMPT_ELEMENT_BUTTON_HEIGHT + 2)? PROMPT_ELEMENT_BUTTON_HEIGHT + 2 : newHeight);
    commentLabel.setText(str);
}

void CommentListElement::reload(){
    disconnectAll();
    deleteWidgets();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

bool CommentListElement::eventMatching(QObject *obj, QEvent *ev){
    switch(ev->type()){
    case QEvent::MouseButtonRelease:
        if(obj == &deleteButton){
            deleteButtonPressed();
            return true;
        }
        break;
    case QEvent::Enter:
    {
        if(obj == &deleteButton){
            deleteButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &deleteButton){
            deleteButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
    }
        break;
    default:
        break;
    }
    return false;
}

void CommentListElement::deleteButtonPressed(){
// Try to delete from server
    // Try to remove comment
    AppWindow *appWin = parent->getParent()->getParent()->getParent()->getParent()->getParent()->getParent();
    Dialog dlg(QUESTION_DIALOG, QString("Usuwanie komentarza"), QString("Jesteś pewny, że chcesz usunąć komentarz?"), nullptr, QString("Tak"), QString("Nie"));
    switch(dlg.exec()){
    case FIRST_OPTION_RESULT:
    {
        // Try to remove Comment
        Book *bookCom = new Book();
        bookCom->setBookId(book->getBookId());
        bookCom->addComment(userId, QString());
                // Create Json User
                QJsonArray jA;
                QJsonObject userObj;
                bookCom->writeJson(userObj);
                jA.append(userObj);
                userObj = QJsonObject();
                userObj.insert(BOOK_JSON_KEY_TEXT, jA);
                QJsonDocument jDoc(userObj);
                bool stop = false;
                while(!stop){
                    if(appWin->getParent()->getServer().getServerReplyStatus())
                        return;
                ServerReplyStatus srs = appWin->getParent()->getServer().setLastRequest(COMMAND_TYPE_BOOK_COMMENT_REMOVE_TEXT, POST, jDoc);
                switch (srs) {
                case SERVER_NO_ERROR:
                {
                    appWin->getPromptPanel().setServerStatusConnection();
                    QJsonObject obj = appWin->getParent()->getServer().readAll();
                    if(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT) != QJsonValue::Undefined){
                        switch(static_cast<ReturnErrorType>(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt())){
                        case RETURN_ERROR_NO_ERROR:
                        {
                            // ______________________________________________________________________________________________________
                            book->merge(*bookCom);
                            parent->removeElement(this);

                            // __________________________________________________________________
                        }
                            break;
                            // _PH_ Check other errors
                            default:
                            //  Prompt Server Error
                            appWin->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - Tworzenie konta nieudane."));
                            break;
                        }
                    }
                    // _____________________________________________________________________________________________________________
                   stop = true;
                   appWin->getParent()->getServer().clearStatus();
                }
                    break;
                case SERVER_NETWORK_ERROR:
                {
                    // __________________________________________________________________________________
                    QNetworkReply::NetworkError error =appWin->getParent()->getServer().getNetworkError();
                    if(error == QNetworkReply::ConnectionRefusedError || error == QNetworkReply::TimeoutError){
                        appWin->getPromptPanel().setServerStatusNoConnection();
                    }
                    // ____________________________________________________________________________________
                    stop = true;
                    appWin->getParent()->getServer().clearStatus();
                }
                    break;
                case SERVER_READY:
                    stop = true;
                    appWin->getParent()->getServer().clearStatus();
                    break;
                default:
                    break;
                }
               }
                SET_PTR_DO(bookCom, nullptr);
    }
        break;
    case SECOND_OPTION_RESULT:
    {
        return;
    }
    default:
        break;
    }
}
