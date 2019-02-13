#include"operationlistelementbookpanelusersbooks.hpp"
#include"operationlist.hpp"
#include<QEvent>
#include<QLabel>
#include"commentlist.hpp"
#include"../PLMS_Server_App/book.hpp"
#include"filteredlist.hpp"
#include"../PLMS_Server_App/user.hpp"
#include"dialog.hpp"
#include"operationpanelfilteredlist.hpp"
#include"appwindowloggedinpanel.hpp"
#include"bookpanel.hpp"
#include"appwindow.hpp"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include"promptpanel.hpp"
#include"server.hpp"
#include"app.hpp"


OperationListElementBookPanelUsersBooks::OperationListElementBookPanelUsersBooks(OperationList *parent, Book* book)
    : OperationListElement(parent), book(book), actionButton(this){
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationListElementBookPanelUsersBooks::~OperationListElementBookPanelUsersBooks(){
    disconnectAll();
    deleteWidgets();
}

void OperationListElementBookPanelUsersBooks::init(){
    generateText();
    switch(book->getBookStatus()){
    case BOOK_STATUS_RESERVED:
    case BOOK_STATUS_FREE:
        actionButton.setText("Wypożycz");
        break;
    case BOOK_STATUS_EXPIRED:
    case BOOK_STATUS_CHECKED_OUT:
        actionButton.setText("Zwróć");
        break;
    default:
        break;
    }
    actionButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    actionButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(1), OPERATION_ELEMENT_BUTTON_HEIGHT);
    actionButton.setAlignment(Qt::AlignCenter);
}

void OperationListElementBookPanelUsersBooks::setWindow(){
   resize(OPERATION_ELEMENT_WIDTH,generalInfoLabel.height() + 3 *OPERATION_ELEMENT_VERTICAL_OFFSET + OPERATION_ELEMENT_BUTTON_HEIGHT);
}

void OperationListElementBookPanelUsersBooks::createWidgets(){
    // Brak
}

void OperationListElementBookPanelUsersBooks::createLayout(){
    // Brak
    actionButton.move(OPERATION_ELEMENT_BUTTON_WIDTH + OPERATION_ELEMENT_HORIZONTAL_OFFSET  , generalInfoLabel.height() + 2 * OPERATION_ELEMENT_VERTICAL_OFFSET );
    actionButton.show();
    }

void OperationListElementBookPanelUsersBooks::deleteWidgets(){

}

void OperationListElementBookPanelUsersBooks::connectAll(){
    actionButton.installEventFilter(parent->getParent());
}

void OperationListElementBookPanelUsersBooks::disconnectAll(){
    // Brak
}

void OperationListElementBookPanelUsersBooks::generateText(){
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
    case BOOK_STATUS_CHECKED_OUT:
        additionalText.append("Wypożyczona");
        break;
    case BOOK_STATUS_EXPIRED:
        additionalText.append("Do oddania");
        break;
    default:
        break;
    }

    switch(book->getBookStatus()){
    case BOOK_STATUS_RESERVED:
        additionalText.append(QString("\nRezerwacja wygasa: ") + book->getParam(BOOK_DATE));
        break;
    case BOOK_STATUS_CHECKED_OUT:
        additionalText.append(QString("\nNależy oddać do: ") + book->getParam(BOOK_DATE));
        break;
    case BOOK_STATUS_EXPIRED:
        additionalText.append(QString("\nWygasła z dniem: ") + book->getParam(BOOK_DATE));
        break;
    default:
        break;
    }
    QString text = TEXT_GENERATOR_ELEMENT_BOOKS;
    uint newHeight = generalInfoLabel.fontMetrics().boundingRect(0,0, OPERATION_ELEMENT_GENERAL_INFO_LABEL_WIDTH - 10 - 10, 1200, Qt::TextWordWrap, text).height();
        generalInfoLabel.resize(OPERATION_ELEMENT_GENERAL_INFO_LABEL_WIDTH - 10 - 10, (newHeight < OPERATION_ELEMENT_BUTTON_HEIGHT)? OPERATION_ELEMENT_BUTTON_HEIGHT + 2 : newHeight);
        generalInfoLabel.setText(text);
    }

void OperationListElementBookPanelUsersBooks::reload(bool reloadLayout)
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

bool OperationListElementBookPanelUsersBooks::eventMatching(QObject *obj, QEvent *ev){
    switch(ev->type()){
        case QEvent::MouseButtonRelease:
        if(obj == &actionButton){
            actionButtonPressed();
            return true;
        }
        break;
    case QEvent::Enter:
    {
        if(obj == &actionButton){
            actionButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &actionButton){
            actionButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
    }
        break;
        default:
            break;

    }
    return false;
}

void OperationListElementBookPanelUsersBooks::actionButtonPressed(){
    BookPanel* bookPanel =  parent->getParent()->getParent()->getBookPanelParent();
    AppWindowLoggedInPanel* appWindow = static_cast<AppWindowLoggedInPanel*>( bookPanel->getParent()->getParent());
    Book bookSend;
    QString cmd;
    BookStatus lastState= book->getBookStatus();
    switch (book->getBookStatus()) {
    case BOOK_STATUS_FREE:
    case BOOK_STATUS_RESERVED:
    {
        // Try to remove account
        bookSend.setBookId(book->getBookId());
        if(book->getBookStatus() == BOOK_STATUS_FREE){
            bookSend.setParam(BOOK_USER_ID, bookPanel->getUser()->getParam(USER_ID));
        }
        cmd = COMMAND_TYPE_BOOK_CHECK_OUT_TEXT;
    }
        break;
    case BOOK_STATUS_CHECKED_OUT:
    case BOOK_STATUS_EXPIRED:
    {
            // Try to remove account
            bookSend.setBookId(book->getBookId());
            bookSend.setParam(BOOK_USER_ID, bookPanel->getUser()->getParam(USER_ID));
            cmd = COMMAND_TYPE_BOOK_RETURN_TEXT;
    }
        break;
    default:
            return;
    }
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
            ServerReplyStatus srs = appWindow->getParent()->getParent()->getServer().setLastRequest(cmd, POST, jDoc);
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
                        if(lastState != BOOK_STATUS_RESERVED){
                            User tempUser;
                            User* user = bookPanel->getUser();
                            tempUser.setUserId(user->getUserId());
                            tempUser.setParam(USER_BOOK_ID, book->getParam(BOOK_ID));
                            user->merge(tempUser);
                        }
                        // __________________________________________________________________
                    }
                        break;
                        // _PH_ Check other errors
                        default:
                        //  Prompt Server Error
                        appWindow->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - Tworzenie konta nieudane."));
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
}

Book* OperationListElementBookPanelUsersBooks::getBook(){
    return book;
}
