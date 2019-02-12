#include"bookpanel.hpp"
#include"dialog.hpp"
#include"operationpanelfilteredlist.hpp"
#include"../PLMS_Server_App/user.hpp"
#include"../PLMS_Server_App/book.hpp"
#include"windowmacros.hpp"
#include"mainmacros.hpp"
#include"appwindow.hpp"
#include"promptpanel.hpp"
#include"server.hpp"
#include"app.hpp"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>

BookPanel::BookPanel(Dialog* parent, User* user)
    : QFrame(parent), parent(parent), user(user),
      usersBooksButton(DIALOG_BOOK_PANEL_USERS_BOOKS_BUTTON_TEXT, this),
      checkOutButton(DIALOG_BOOK_PANEL_CHECK_OUT_BUTTON_TEXT, this),
      closeButton(DIALOG_BOOK_PANEL_CLOSE_BUTTON_TEXT, this)
{
    setStyleSheet("BookPanel{background: qlineargradient(x1:0, y1:1, x2:1, y2:0, stop:0 rgba(235, 235,235, 255),stop: 0.63 rgba(200, 200, 200, 255), stop: 1 rgba(210,210,210,255)); border-radius: 10px;border: 2px ridge grey;}");
    create();
}

BookPanel::~BookPanel(){
   SET_PTR_DOA(savedBooks.books, nullptr);
   SET_PTR_DOA(savedBookFilters.bookFilters, nullptr);
}

void BookPanel::create(){
    SET_PTR_DO(filteredList, new OperationPanelFilteredList(this, static_cast<AppWindowLoggedInPanel*>(parent->getParent())));
    usersBooksButton.setGeometry(DIALOG_BOOK_PANEL_USERS_BOOKS_BUTTON_X,DIALOG_BOOK_PANEL_USERS_BOOKS_BUTTON_Y,DIALOG_BOOK_PANEL_USERS_BOOKS_BUTTON_WIDTH,DIALOG_BOOK_PANEL_USERS_BOOKS_BUTTON_HEIGHT);
    checkOutButton.setGeometry(DIALOG_BOOK_PANEL_CHECK_OUT_BUTTON_X,DIALOG_BOOK_PANEL_CHECK_OUT_BUTTON_Y,DIALOG_BOOK_PANEL_CHECK_OUT_BUTTON_WIDTH,DIALOG_BOOK_PANEL_CHECK_OUT_BUTTON_HEIGHT);
    filteredList->setGeometry(DIALOG_BOOK_PANEL_FILTERED_LIST_X,DIALOG_BOOK_PANEL_FILTERED_LIST_Y,DIALOG_BOOK_PANEL_FILTERED_LIST_WIDTH,DIALOG_BOOK_PANEL_FILTERED_LIST_HEIGHT);
    filteredList->show();
    usersBooksButton.setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_HIGHLIGHT);
    checkOutButton.setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_LOWLIGHT);
    closeButton.setGeometry(DIALOG_BOOK_PANEL_CLOSE_BUTTON_X,DIALOG_BOOK_PANEL_CLOSE_BUTTON_Y,DIALOG_BOOK_PANEL_CLOSE_BUTTON_WIDTH,DIALOG_BOOK_PANEL_CLOSE_BUTTON_HEIGHT);
    closeButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    usersBooksButton.setAlignment(Qt::AlignCenter);
    checkOutButton.setAlignment(Qt::AlignCenter);
    closeButton.setAlignment(Qt::AlignCenter);
    usersBooksButton.installEventFilter(parent);
    checkOutButton.installEventFilter(parent);
    closeButton.installEventFilter(parent);
}

bool BookPanel::eventMatching(QObject *obj, QEvent *ev){
    switch(ev->type()){
    case QEvent::MouseButtonRelease:
    {
        if(obj == &usersBooksButton){
            usersBooksButtonPressed();
            return true;
        }
        if(obj == &checkOutButton){
            checkOutButtonPressed();
            return true;
        }
        if(obj == &closeButton){
            closeButtonPressed();
            return true;
        }
    }
        break;
    case QEvent::Enter:
    {
        if(obj == &closeButton){
            closeButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &closeButton){
            closeButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
        }
    }
        break;
    default:
        break;
    }
    return false;
}


void BookPanel::usersBooksButtonPressed(){
    if(!usersBooksStat){
        usersBooksStat = true;
        usersBooksButton.setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_HIGHLIGHT);
        checkOutButton.setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_LOWLIGHT);
        filteredList->reload(false);
    }
}

void BookPanel::checkOutButtonPressed(){
    if(usersBooksStat){
        if(user->getNumbOfBookId() < 5){
        usersBooksStat = false;
        usersBooksButton.setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_LOWLIGHT);
        checkOutButton.setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_HIGHLIGHT);
        filteredList->reload(false);
        }else{
            Dialog dlg(QUESTION_DIALOG, QString("Limit książek"), QString("Czytelnik może wypożyczyc maksymalnie 5 książek."), nullptr, QString("Ok"));
            dlg.exec();
        }
    }
}

void BookPanel::closeButtonPressed(){
    parent->done(CANCEL_RESULT);
}

BooksLoggedInSave* BookPanel::getSavedBooks(){
    return &savedBooks;
}

BookFiltersLoggedInSave* BookPanel::getSavedBookFilters(){
    return &savedBookFilters;
}

void BookPanel::readDataFromServer(){
    // Prepare ReadFilesRules

            QString command;
            QJsonArray filtersArray;
            QJsonObject tempObj;
            QJsonObject msgObj;
            AppWindowLoggedInPanel* appWindow = static_cast<AppWindowLoggedInPanel*>(parent->getParent());
            if(usersBooksStat)
            {
                if(user->getNumbOfBookId() == 0){
                    savedBooks.nextIdBook = 0;
                    SET_PTR_DOA(savedBooks.books, nullptr);
                    savedBooks.numbOfBooks = 0;
                    savedBooks.bookCurrentPage = 0;
                    return;
                }
                tempObj.insert(READ_FILE_RULES_FILTER_PARAM_TEXT, QString::number(USER_ID));
                tempObj.insert(READ_FILE_RULES_FILTER_VALUE_TEXT, QString::number(user->getUserId()));
                filtersArray.append(tempObj);
            }else{
                tempObj.insert(READ_FILE_RULES_FILTER_PARAM_TEXT, QString::number(BOOK_STATUS));
                tempObj.insert(READ_FILE_RULES_FILTER_VALUE_TEXT, QString::number(BOOK_STATUS_FREE));
                filtersArray.append(tempObj);
            }
            for(uint i = 0; i < savedBookFilters.numbOfFilters; i++){
                tempObj = QJsonObject();
                tempObj.insert(READ_FILE_RULES_FILTER_PARAM_TEXT, QString::number((savedBookFilters.bookFilters + i)->param));
                tempObj.insert(READ_FILE_RULES_FILTER_VALUE_TEXT, (savedBookFilters.bookFilters + i)->filterStr);
                filtersArray.append(tempObj);
            }
                tempObj = QJsonObject();
                tempObj.insert(READ_FILE_RULES_FILTER_TEXT, filtersArray);
                tempObj.insert(READ_FILE_RULES_FILE_TYPE_TEXT, QString::number(FILE_TYPE_BOOKS_FILE));
                if(savedBooks.nextIdBook != 0)
                    tempObj.insert(READ_FILE_RULES_START_ID_TEXT, QString::number(savedBooks.nextIdBook));
                tempObj.insert(READ_FILE_RULES_MAX_READ_TEXT, QString::number(20));
                msgObj.insert(READ_FILE_RULES_JSON_KEY_TEXT, tempObj);

            command = COMMAND_TYPE_BOOK_READ_TEXT;
            // Send to server
            QJsonDocument jDoc(msgObj);
            bool stop = false;
            while(!stop){
            ServerReplyStatus srs = appWindow->getParent()->getParent()->getServer().setLastRequest(command, POST, jDoc);
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
                        if(obj.value(READ_FILE_RULES_NEXT_POSSIBLE_READ_ID) != QJsonValue::Undefined){
                               savedBooks.nextIdBook = obj.value(READ_FILE_RULES_NEXT_POSSIBLE_READ_ID).toString().toULongLong();
                            }else{
                                savedBooks.nextIdBook = 0;
                            }
                            if(obj.value(BOOK_JSON_KEY_TEXT) != QJsonValue::Undefined){
                                QJsonArray retArray = obj.value(BOOK_JSON_KEY_TEXT).toArray();
                                uint len = retArray.count();
                                if(len > 0){
                                    SET_PTR_DOA(savedBooks.books, new Book[len]);
                                }
                                else{
                                    SET_PTR_DOA(savedBooks.books, nullptr);
                                }
                                savedBooks.numbOfBooks = len;
                                for(uint i = 0; i < len; i++){
                                    QJsonObject retObj = retArray.at(i).toObject();
                                    (savedBooks.books + i)->readJson(retObj);
                                }
                            }else{
                                //  Prompt Server Error
                                appWindow->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera - Odczyt danych nieudany."));
                            }

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
}

void BookPanel::reload(bool reloadDynamic){
    filteredList->reload(reloadDynamic);
}

Dialog* BookPanel::getParent(){
    return parent;
}

User* BookPanel::getUser(){
    return user;
}
