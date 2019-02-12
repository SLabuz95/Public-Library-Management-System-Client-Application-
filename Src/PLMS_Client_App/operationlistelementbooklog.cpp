#include"operationlistelementbooklog.hpp"
#include"operationlist.hpp"
#include<QEvent>
#include<QLabel>
#include"../PLMS_Server_App/booklog.hpp"

OperationListElementBookLog::OperationListElementBookLog(OperationList *parent, BookLog* bookLog)
    : OperationListElement(parent), bookLog(bookLog){
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationListElementBookLog::~OperationListElementBookLog(){
    disconnectAll();
    deleteWidgets();
}

void OperationListElementBookLog::init(){
    generateText();
}

void OperationListElementBookLog::setWindow(){
    setStyleSheet("OperationListElementBookLog{background-color: rgba(245, 245, 245, 0.5); border: 1px solid rgba(230,230,230, 0.8); border-radius: 3px;}");
    resize(OPERATION_ELEMENT_WIDTH,generalInfoLabel.height() + 2 *OPERATION_ELEMENT_VERTICAL_OFFSET );
   }

void OperationListElementBookLog::createWidgets(){
    // Brak
}

void OperationListElementBookLog::createLayout(){
    // Brak    
}

void OperationListElementBookLog::deleteWidgets(){
    // Brak
}

void OperationListElementBookLog::connectAll(){
    // Brak
}

void OperationListElementBookLog::disconnectAll(){
    // Brak
}

void OperationListElementBookLog::generateText(){
    QString action = QString("Działanie: ");
    switch (bookLog->getAction()) {
    case BOOK_LOG_ACTION_LOGIN:
    action.append("Logowanie");
        break;
    case BOOK_LOG_ACTION_ADD_USER:
    action.append("Dodanie użytkownika");
        break;
    case BOOK_LOG_ACTION_REGISTER_USER:
    action.append("Rejestracja");
        break;
    case BOOK_LOG_ACTION_REMOVE_USER:
    action.append("Usunięcie użytkownika");
        break;
    case BOOK_LOG_ACTION_LOGOUT:
    action.append("Wylogowanie");
        break;
    case BOOK_LOG_ACTION_ADD_BOOK:
    action.append("Dodanie książki");
        break;
    case BOOK_LOG_ACTION_REMOVE_BOOK:
        action.append("Usunięcie książki");
        break;
    case BOOK_LOG_ACTION_RESERVE_BOOK:
    action.append("Rezerwacja książki");
        break;
    case BOOK_LOG_ACTION_CHECK_OUT_BOOK:
    action.append("Wypożyczenie książki");
        break;
    case BOOK_LOG_ACTION_EXPIRED_BOOK:
        action.append("Wygaśnięcie książki");
        break;
    case BOOK_LOG_ACTION_RETURN_BOOK:
    action.append("Oddanie książki");
        break;
    case BOOK_LOG_ACTION_ADD_EDIT_COMMENT:
    action.append("Dodanie/edycja komentarza");
        break;
    case BOOK_LOG_ACTION_REMOVE_COMMENT:
    action.append("Usunięcie komentarza");
        break;
    default:
        break;
    }
    QString perm = QString("Uprawnienia: ");
    switch (bookLog->getUserPermissions()) {
    case USER_PERMISSIONS_ADMIN:
        perm.append("Administrator");
        break;
    case USER_PERMISSIONS_READER:
        perm.append("Czytelnik");
        break;
    case USER_PERMISSIONS_LIBRARIAN:
        perm.append("Bibliotekarz");
        break;
    }
    QString addition;
    if(bookLog->getBookId() != 0){
        addition = QString("\nIndeks książki: ") + bookLog->getParam(BOOK_LOG_BOOK_ID);
        if(!bookLog->getDateTimeOptional().isNull())
            switch (bookLog->getAction()) {
            case BOOK_LOG_ACTION_RESERVE_BOOK:
                addition.append(QString("\nZarezerwowane do: ") + bookLog->getDateTimeOptional().toString(OPTIONAL_DATE_TIME_FORMAT));
                break;
            case BOOK_LOG_ACTION_CHECK_OUT_BOOK:
                addition.append(QString("\nWypożyczona do: ") + bookLog->getDateTimeOptional().toString(OPTIONAL_DATE_TIME_FORMAT));
                break;
            case BOOK_LOG_ACTION_EXPIRED_BOOK:
                addition.append(QString("\nKsiążka wygasła dnia: ") + bookLog->getDateTimeOptional().toString(OPTIONAL_DATE_TIME_FORMAT));
                break;
            default:
                break;
            }
        if(bookLog->getUserId() != 0){
            switch (bookLog->getAction()) {
            case BOOK_LOG_ACTION_ADD_EDIT_COMMENT:
                addition.append(QString("\nKomentarz użytkownika #") + bookLog->getParam(BOOK_LOG_USER_ID_COMMENT) + QString("został dodany/edytowany o treści:\n") + bookLog->getParam(BOOK_LOG_COMMENT_CONTENT));
                break;
            case BOOK_LOG_ACTION_REMOVE_COMMENT:
                addition.append(QString("\nKomentarz użytkownika #") + bookLog->getParam(BOOK_LOG_USER_ID_COMMENT) + QString("został usunięty o treści:\n") + bookLog->getParam(BOOK_LOG_COMMENT_CONTENT));
                break;
            default:
                break;
            }
        }
    }
    QString text = TEXT_GENERATOR_ELEMENT_BOOK_LOG;
    uint newHeight = generalInfoLabel.fontMetrics().boundingRect(0,0, OPERATION_ELEMENT_GENERAL_INFO_LABEL_WIDTH , 1200, Qt::TextWordWrap, text).height();
        generalInfoLabel.resize(OPERATION_ELEMENT_GENERAL_INFO_LABEL_WIDTH, (newHeight < OPERATION_ELEMENT_BUTTON_HEIGHT)? OPERATION_ELEMENT_BUTTON_HEIGHT + 2 : newHeight);
        generalInfoLabel.setText(text);
    }

void OperationListElementBookLog::reload(){
    disconnectAll();
    deleteWidgets();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

bool OperationListElementBookLog::eventMatching(QObject *obj, QEvent *ev){    
    return false;
}

