#include"operationlistelementlibrary.hpp"
#include"operationlist.hpp"
#include<QEvent>
#include<QLabel>
#include"commentlist.hpp"
#include"filteredlist.hpp"
#include"../PLMS_Server_App/book.hpp"
#include"../PLMS_Server_App/user.hpp"
#include"dialog.hpp"
#include"operationpanelfilteredlist.hpp"
#include"appwindowloggedinpanel.hpp"
#include"appwindow.hpp"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include"promptpanel.hpp"
#include"server.hpp"
#include"app.hpp"

OperationListElementLibrary::OperationListElementLibrary(OperationList *parent, Book* book)
    : OperationListElement(parent), book(book), reserveBookButton(this), commentsButton(this), addCommentButton(this){
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationListElementLibrary::~OperationListElementLibrary(){
    disconnectAll();
    deleteWidgets();
}

void OperationListElementLibrary::init(){
    generateText();
    reserveBookButton.setText("Zarezerwuj");
    addCommentButton.setText("Skomentuj");
    commentsButton.setText(QString("Komentarze(") + QString::number(book->getNumbOfBookComments()) + QString(")"));
    reserveBookButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    addCommentButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    commentsButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    if(book->getBookStatus() == BOOK_STATUS_FREE){
        addCommentButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(3), OPERATION_ELEMENT_BUTTON_HEIGHT);
        commentsButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(3), OPERATION_ELEMENT_BUTTON_HEIGHT);
        reserveBookButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(3), OPERATION_ELEMENT_BUTTON_HEIGHT);
    }else{
        addCommentButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(2), OPERATION_ELEMENT_BUTTON_HEIGHT);
        commentsButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(2), OPERATION_ELEMENT_BUTTON_HEIGHT);
    }
    addCommentButton.setAlignment(Qt::AlignCenter);
    commentsButton.setAlignment(Qt::AlignCenter);
    reserveBookButton.setAlignment(Qt::AlignCenter);
}

void OperationListElementLibrary::setWindow(){
    if(commentList && book->getNumbOfBookComments() == 0){
        SET_PTR_DO(commentList, nullptr);
    }
    resize(OPERATION_ELEMENT_WIDTH,generalInfoLabel.height() + 3 *OPERATION_ELEMENT_VERTICAL_OFFSET + OPERATION_ELEMENT_BUTTON_HEIGHT + ((commentList)? commentList->height() + OPERATION_ELEMENT_VERTICAL_OFFSET : 0));
}

void OperationListElementLibrary::createWidgets(){
    // Brak
}

void OperationListElementLibrary::createLayout(){
    commentsButton.setText(QString("Komentarze(") + QString::number(book->getNumbOfBookComments()) + QString(")"));
    if(book->getBookStatus() == BOOK_STATUS_FREE){
            reserveBookButton.move(OPERATION_ELEMENT_BUTTON_WIDTH + OPERATION_ELEMENT_HORIZONTAL_OFFSET, generalInfoLabel.height() + 2* OPERATION_ELEMENT_VERTICAL_OFFSET);
            addCommentButton.move(OPERATION_ELEMENT_BUTTON_WIDTH + OPERATION_ELEMENT_HORIZONTAL_OFFSET * 2 + addCommentButton.width() , reserveBookButton.y());
            commentsButton.move(OPERATION_ELEMENT_BUTTON_WIDTH +  OPERATION_ELEMENT_HORIZONTAL_OFFSET * 3 + addCommentButton.width() + commentsButton.width(), addCommentButton.y());
            reserveBookButton.show();
        }else{
            reserveBookButton.hide();
            addCommentButton.move(2*OPERATION_ELEMENT_BUTTON_WIDTH , generalInfoLabel.height() + 2 * OPERATION_ELEMENT_VERTICAL_OFFSET);
            commentsButton.move(3*OPERATION_ELEMENT_BUTTON_WIDTH + addCommentButton.width() , addCommentButton.y());
        }
        if(commentList){
            commentList->move(0, generalInfoLabel.height() + 3 * OPERATION_ELEMENT_VERTICAL_OFFSET + OPERATION_ELEMENT_BUTTON_HEIGHT);
            commentList->show();
        }
        addCommentButton.show();
        commentsButton.show();
        parent->reallocate(true);
}


void OperationListElementLibrary::deleteWidgets(){
    SET_PTR_DO(commentList, nullptr);
}

void OperationListElementLibrary::connectAll(){
    reserveBookButton.installEventFilter(parent->getParent());
    commentsButton.installEventFilter(parent->getParent());
    addCommentButton.installEventFilter(parent->getParent());

}

void OperationListElementLibrary::disconnectAll(){
    // Brak
}

void OperationListElementLibrary::generateText(){
    QString bookType = QString("\nGatunek: ");
    switch (book->getBookType()) {
    case BOOK_CRIME:
        bookType.append("Kryminał");
        break;
    case BOOK_DRAMA:
        bookType.append("Dramat");
        break;
    case BOOK_GUIDE:
        bookType.append("Przewodnik");
        break;
    case BOOK_SATIR:
        bookType.append("Satyra");
        break;
    case BOOK_HORROR:
        bookType.append("Groza");
        break;
    case BOOK_POETRY:
        bookType.append("Poezja");
        break;
    case BOOK_FANTASY:
        bookType.append("Fantastyka");
        break;
    case BOOK_HISTORY:
        bookType.append("Historyczna");
        break;
    case BOOK_JOURNAL:
        bookType.append("Czasopismo");
        break;
    case BOOK_ROMANCE:
        bookType.append("Romans");
        break;
    case BOOK_SCIENCE:
        bookType.append("Nauka");
        break;
    case BOOK_THRILLER:
        bookType.append("Thriller");
        break;
    case BOOK_BIOGRAPHY:
        bookType.append("Biografia");
        break;
    case BOOK_COMIC_BOOK:
        bookType.append("Komiks");
        break;
    case BOOK_DICTIONARY:
        bookType.append("Słownik");
        break;
    case BOOK_FAIRY_TALE:
        bookType.append("Bajka");
        break;
    case BOOK_ENCYCLOPEDIA:
        bookType.append("Encyklopedia");
        break;
    case BOOK_AUTOBIOGRAPHY:
        bookType.append("Autobiografia");
        break;
    case BOOK_SCIENCE_FICTION:
        bookType.append("Fantastyka naukowa");
        break;
    case BOOK_CHILDREN_LITERATURE:
        bookType.append("Literatura dziecięca");
        break;
    default:
        break;
    }
    QString additionalText = QString("\nStatus książki: ");
    switch(book->getBookStatus()){
    case BOOK_STATUS_FREE:
        additionalText.append("Dostępna");
        break;
    case BOOK_STATUS_RESERVED:
        additionalText.append("Zarezerwowana");
        break;
    case BOOK_STATUS_EXPIRED:
    case BOOK_STATUS_CHECKED_OUT:
        additionalText.append("Wypożyczona");
        break;
    default:
        break;
    }
    QString text = TEXT_GENERATOR_ELEMENT_LIBRARY;
    uint newHeight = generalInfoLabel.fontMetrics().boundingRect(0,0, OPERATION_ELEMENT_GENERAL_INFO_LABEL_WIDTH, 1200, Qt::TextWordWrap, text).height();
        generalInfoLabel.resize(OPERATION_ELEMENT_GENERAL_INFO_LABEL_WIDTH, (newHeight < OPERATION_ELEMENT_BUTTON_HEIGHT)? OPERATION_ELEMENT_BUTTON_HEIGHT  +2 : newHeight);
        generalInfoLabel.setText(text);
    }

void OperationListElementLibrary::reload(bool reloadLayout)
{
    if(reloadLayout){
        setWindow();
        createWidgets();
        createLayout();
    }else{
    disconnectAll();
    deleteWidgets();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    }
}

bool OperationListElementLibrary::eventMatching(QObject *obj, QEvent *ev){
    switch(ev->type()){
        case QEvent::MouseButtonRelease:
        if(obj == &reserveBookButton){
            reserveBookButtonPressed();
            return true;
        }
        if(obj == &commentsButton){
            commentsButtonPressed();
            return true;
        }
        if(obj == &addCommentButton){
            addCommentButtonPressed();
            return true;
        }
            break;
    case QEvent::Enter:
    {
        if(obj == &reserveBookButton){
            reserveBookButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
        if(obj == &commentsButton){
            commentsButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
        if(obj == &addCommentButton){
            addCommentButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &reserveBookButton){
            reserveBookButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
        if(obj == &commentsButton){
            commentsButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
        if(obj == &addCommentButton){
            addCommentButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
    }
        break;
        default:
            break;

    }
    return false;
}


void OperationListElementLibrary::reserveBookButtonPressed(){    
    AppWindowLoggedInPanel* appWindow = static_cast<AppWindowLoggedInPanel*>(parent->getParent()->getParent()->getParent());
    if(appWindow->getUser()->getNumbOfBookId() < 5){
        parent->nextPageAvailable = false;
        Book bookSend;
    // Try to remove account
        bookSend.setBookId(book->getBookId());
        bookSend.setParam(BOOK_USER_ID, appWindow->getUser()->getParam(USER_ID));
    // Try to remove account
     // Create Json User
            QJsonArray jA;
            QJsonObject bookObj;
            bookSend.writeJson(bookObj);
            jA.append(bookObj);
            bookObj.insert(BOOK_JSON_KEY_TEXT, jA);
            QJsonDocument jDoc(bookObj);
            bool stop = false;
            while(!stop){
                if(appWindow->getParent()->getParent()->getServer().getServerReplyStatus())
                    return;
            ServerReplyStatus srs = appWindow->getParent()->getParent()->getServer().setLastRequest(COMMAND_TYPE_BOOK_RESERVE_TEXT, POST, jDoc);
            switch (srs) {
            case SERVER_NO_ERROR:
            {
                appWindow->getParent()->getPromptPanel().setServerStatusConnection();
                QJsonObject obj = appWindow->getParent()->getParent()->getServer().readAll();
                if(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT) != QJsonValue::Undefined){
                    switch(static_cast<ReturnErrorType>(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt())){
                    case RETURN_ERROR_NO_ERROR:
                    {
                        // ______________________________________________________________________________________________________
                        book->merge(bookSend);
                        User tempUser;
                        User* user = appWindow->getUser();
                        tempUser.setUserId(user->getUserId());
                        tempUser.setParam(USER_BOOK_ID, book->getParam(BOOK_ID));
                        user->merge(tempUser);
                        // __________________________________________________________________
                    }
                        break;
                        // _PH_ Check other errors
                        default:
                        //  Prompt Server Error
                        appWindow->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - Rezerwacja książki nieudana."));
                        break;
                    }
                }
                // _____________________________________________________________________________________________________________
               stop = true;
               appWindow->getParent()->getParent()->getServer().clearStatus();
            }
                break;
            case SERVER_NETWORK_ERROR:
            {
                // __________________________________________________________________________________
                QNetworkReply::NetworkError error = appWindow->getParent()->getParent()->getServer().getNetworkError();
                if(error == QNetworkReply::ConnectionRefusedError || error == QNetworkReply::TimeoutError){
                    appWindow->getParent()->getPromptPanel().setServerStatusNoConnection();
                }
                // ____________________________________________________________________________________
                stop = true;
                appWindow->getParent()->getParent()->getServer().clearStatus();
            }
                break;
            case SERVER_READY:
                stop = true;
                appWindow->getParent()->getParent()->getServer().clearStatus();
                break;
            default:
                break;
            }
           }
    parent->getParent()->reload(false);
    }else{
        appWindow->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Osiągnięto limit wypożyczonych/zarezerwowanych książek"));
    }

}

void OperationListElementLibrary::commentsButtonPressed(){
    if(commentList){
        SET_PTR_DO(commentList, nullptr);
    }else{
        if(book->getNumbOfBookComments() > 0){
            SET_PTR_DO(commentList, new CommentList(book, this));
        }else{
            return;
        }
    }
    reload(true);
    parent->reallocate(true);
}

void OperationListElementLibrary::addCommentButtonPressed(){
    Dialog dlg(ADD_COMMENT, book, parent->getParent()->getParent()->getParent()->getUser()->getUserId(), parent->getParent()->getParent()->getParent()->getParent());
    dlg.exec();
    SET_PTR_DO(commentList, new CommentList(book, this));
    reload(true);
    parent->reallocate(true);
}

Book* OperationListElementLibrary::getBook(){
    return book;
}
