#include"appwindowloggedinpanel.hpp"
#include"appwindow.hpp"
#include"app.hpp"
#include"loggedincontrolpanel.hpp"
#include"operationpaneladdbook.hpp"
#include"operationpaneladduser.hpp"
#include"operationpanelbookdata.hpp"
#include"operationpanelfilteredlist.hpp"
#include"operationpaneluserdata.hpp"
#include"operationpanelyouraccount.hpp"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include"../PLMS_Server_App/user.hpp"
#include"../PLMS_Server_App/book.hpp"
#include"../PLMS_Server_App/booklog.hpp"

AppWindowLoggedInPanel::AppWindowLoggedInPanel(AppWindow* parent, User* user)
    : AppWindowCentralPanel(parent),      
      user(user),
      controlPanel(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

AppWindowLoggedInPanel::~AppWindowLoggedInPanel(){
    disconnectAll();
    deleteWidgets();
}

void AppWindowLoggedInPanel::init(){

}

void AppWindowLoggedInPanel::setWindow(){
    // Empty
}

void AppWindowLoggedInPanel::createWidgets(){
    // Empty
    if(user){
        switch(user->getUserPermissions()){
        case USER_PERMISSIONS_READER:
        {
            switch (static_cast<LoggedInControlPanelReaderFunc>(controlPanel.getActiveIndex())) {
            case LOGGED_IN_PANEL_READER_YOUR_ACCOUNT:
                SET_PTR_DO(operationPanel, new OperationPanelYourAccount(this));
                break;
            case LOGGED_IN_PANEL_READER_LIBRARY:
                SET_PTR_DO(operationPanel, new OperationPanelFilteredList(this));
                break;
            case LOGGED_IN_PANEL_READER_YOUR_BOOKS:
                SET_PTR_DO(operationPanel, new OperationPanelFilteredList(this));
                break;
            default:
                break;
            }
        }
            break;
        case USER_PERMISSIONS_LIBRARIAN:
        {
            switch (static_cast<LoggedInControlPanelLibrarianFunc>(controlPanel.getActiveIndex())) {
            case LOGGED_IN_PANEL_LIBRARIAN_YOUR_ACCOUNT:
                SET_PTR_DO(operationPanel, new OperationPanelYourAccount(this));
                break;
            case LOGGED_IN_PANEL_LIBRARIAN_BOOKS:
                SET_PTR_DO(operationPanel, new OperationPanelFilteredList(this));
                break;
            case LOGGED_IN_PANEL_LIBRARIAN_READERS:
                SET_PTR_DO(operationPanel, new OperationPanelFilteredList(this));
                break;
            case LOGGED_IN_PANEL_LIBRARIAN_ADD_BOOK:
                SET_PTR_DO(operationPanel, new OperationPanelAddBook(this));
                break;
            case LOGGED_IN_PANEL_LIBRARIAN_ADD_USER:
                SET_PTR_DO(operationPanel, new OperationPanelAddUser(this));
                break;
            case LOGGED_IN_PANEL_LIBRARIAN_LOG_LIST:
                SET_PTR_DO(operationPanel, new OperationPanelFilteredList(this));
                break;
            default:
                switch (getCurrentAppWindowLoggedInStat()) {
                    case LOGGED_IN_PANEL_BOOK_DATA_STAT:
                        SET_PTR_DO(operationPanel, new OperationPanelBookData(this));
                    break;
                    case LOGGED_IN_PANEL_USER_DATA_STAT:
                        SET_PTR_DO(operationPanel, new OperationPanelUserData(this));
                    break;
                default:
                    break;
                }
                break;
            }
        }
            break;
        case USER_PERMISSIONS_ADMIN:
        {
            switch (static_cast<LoggedInPanelAdminFunc>(controlPanel.getActiveIndex())) {
            case LOGGED_IN_PANEL_ADMIN_YOUR_ACCOUNT:
                SET_PTR_DO(operationPanel, new OperationPanelYourAccount(this));
                break;
            case LOGGED_IN_PANEL_ADMIN_BOOKS:
                SET_PTR_DO(operationPanel, new OperationPanelFilteredList(this));
                break;
            case LOGGED_IN_PANEL_ADMIN_USERS:
                SET_PTR_DO(operationPanel, new OperationPanelFilteredList(this));
                break;
            case LOGGED_IN_PANEL_ADMIN_ADD_BOOK:
                SET_PTR_DO(operationPanel, new OperationPanelAddBook(this));
                break;
            case LOGGED_IN_PANEL_ADMIN_ADD_USER:
                SET_PTR_DO(operationPanel, new OperationPanelAddUser(this));
                break;
            case LOGGED_IN_PANEL_ADMIN_LOG_LIST:
                SET_PTR_DO(operationPanel, new OperationPanelFilteredList(this));
                break;
            default:
                switch(getCurrentAppWindowLoggedInStat()) {
                    case LOGGED_IN_PANEL_BOOK_DATA_STAT:
                        SET_PTR_DO(operationPanel, new OperationPanelBookData(this));
                    break;
                    case LOGGED_IN_PANEL_USER_DATA_STAT:
                        SET_PTR_DO(operationPanel, new OperationPanelUserData(this));
                    break;
                default:
                    break;
                }
                break;
            }
        }
            break;
        default:
            break;
        }
        operationPanel->show();
        // Clear UserDataPtr and BookDataPtr
        SET_PTR_NDO(userDataPtr, nullptr);
        SET_PTR_NDO(bookDataPtr, nullptr);
    }
}

void AppWindowLoggedInPanel::createLayout(){
    // Control Panel
    controlPanel.setGeometry(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_X, APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_Y, APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_WIDTH, APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_HEIGHT);

    // Operation Panel
    operationPanel->setGeometry(OPERATION_PANEL_X, OPERATION_PANEL_Y, OPERATION_PANEL_WIDTH, OPERATION_PANEL_HEIGHT);

}

void AppWindowLoggedInPanel::deleteWidgets(){
    SET_PTR_DO(operationPanel, nullptr);
}

void AppWindowLoggedInPanel::connectAll(){
    // Empty
}

void AppWindowLoggedInPanel::disconnectAll(){
    // Empty
}

void AppWindowLoggedInPanel::reload(){
    loggedInStatusChanged = false;
    deleteWidgets();
    createWidgets();
    createLayout();
    connectAll();    
}

bool AppWindowLoggedInPanel::eventMatching(QObject* obj, QEvent* ev){
    if(controlPanel.eventMatching(obj, ev))
        return true;
    if(operationPanel && operationPanel->eventMatching(obj, ev))
        return true;
    return QObject::eventFilter(obj, ev);
}

User* AppWindowLoggedInPanel::getUser(){
    return user;
}

bool AppWindowLoggedInPanel::eventFilter(QObject *obj, QEvent *ev){
    return eventMatching(obj, ev);
}

AppWindowLoggedInStatus AppWindowLoggedInPanel::getLastAppWindowLoggedInStat(){
    return (*(loggedInStatus + 1));
}

AppWindowLoggedInStatus AppWindowLoggedInPanel::getCurrentAppWindowLoggedInStat(){
    return *loggedInStatus;
}

void AppWindowLoggedInPanel::setAppWindowLoggedInStatus(AppWindowLoggedInStatus awlis, bool doReload){
    if(awlis != *loggedInStatus){
        WINDOW_STATUS_SAVE(loggedInStatus);
        *loggedInStatus = awlis;
        if(doReload){
            switch(user->getUserPermissions()){
            case USER_PERMISSIONS_ADMIN:
                switch(awlis){
                case LOGGED_IN_PANEL_BOOKS_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_BOOKS);
                    break;
                case LOGGED_IN_PANEL_USERS_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_USERS);
                    break;
                case LOGGED_IN_PANEL_ADD_BOOK_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_ADD_BOOK);
                    break;
                case LOGGED_IN_PANEL_ADD_USER_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_ADD_USER);
                    break;
                case LOGGED_IN_PANEL_BOOK_LOG_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_LOG_LIST);
                    break;
                case LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_YOUR_ACCOUNT);
                    break;
                default:
                    controlPanel.setActiveIndex(NUMB_OF_LOGGED_IN_PANEL_ADMIN_FUNC);
                    break;

                }
                break;
            case USER_PERMISSIONS_READER:
                switch(awlis){
                case LOGGED_IN_PANEL_LIBRARY_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_READER_LIBRARY);
                    break;
                case LOGGED_IN_PANEL_MY_BOOKS_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_READER_YOUR_BOOKS);
                    break;
                case LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_READER_YOUR_ACCOUNT);
                    break;
                default:
                    controlPanel.setActiveIndex(NUMB_OF_LOGGED_IN_PANEL_ADMIN_FUNC);
                    break;
                }
                break;
            case USER_PERMISSIONS_LIBRARIAN:
                switch(awlis){
                case LOGGED_IN_PANEL_BOOKS_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_BOOKS);
                    break;
                case LOGGED_IN_PANEL_READERS_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_READERS);
                    break;
                case LOGGED_IN_PANEL_ADD_BOOK_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_ADD_BOOK);
                    break;
                case LOGGED_IN_PANEL_ADD_USER_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_ADD_USER);
                    break;
                case LOGGED_IN_PANEL_BOOK_LOG_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_LOG_LIST);
                    break;
                case LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT:
                    controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_YOUR_ACCOUNT);
                    break;
                default:
                    controlPanel.setActiveIndex(NUMB_OF_LOGGED_IN_PANEL_LIBRARIAN_FUNC);
                    break;

                }
                break;
            default:
                break;
            }
            loggedInStatusChanged = true;
        }
    }
}

void AppWindowLoggedInPanel::setAppWindowLoggedInStatus(AppWindowLoggedInStatus awlis, User* userDataPtrF){
    if(awlis != *loggedInStatus){
        WINDOW_STATUS_SAVE(loggedInStatus);
        *loggedInStatus = awlis;
        userDataPtr = userDataPtrF;
        switch(user->getUserPermissions()){
        case USER_PERMISSIONS_ADMIN:
            switch(awlis){
            case LOGGED_IN_PANEL_BOOKS_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_BOOKS);
                break;
            case LOGGED_IN_PANEL_USERS_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_USERS);
                break;
            case LOGGED_IN_PANEL_ADD_BOOK_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_ADD_BOOK);
                break;
            case LOGGED_IN_PANEL_ADD_USER_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_ADD_USER);
                break;
            case LOGGED_IN_PANEL_BOOK_LOG_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_LOG_LIST);
                break;
            case LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_YOUR_ACCOUNT);
                break;
            default:
                controlPanel.setActiveIndex(NUMB_OF_LOGGED_IN_PANEL_ADMIN_FUNC);
                break;

            }
            break;
        case USER_PERMISSIONS_READER:
            switch(awlis){
            case LOGGED_IN_PANEL_LIBRARY_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_READER_LIBRARY);
                break;
            case LOGGED_IN_PANEL_MY_BOOKS_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_READER_YOUR_BOOKS);
                break;
            case LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_READER_YOUR_ACCOUNT);
                break;
            default:
                controlPanel.setActiveIndex(NUMB_OF_LOGGED_IN_PANEL_ADMIN_FUNC);
                break;
            }
            break;
        case USER_PERMISSIONS_LIBRARIAN:
            switch(awlis){
            case LOGGED_IN_PANEL_BOOKS_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_BOOKS);
                break;
            case LOGGED_IN_PANEL_READERS_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_READERS);
                break;
            case LOGGED_IN_PANEL_ADD_BOOK_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_ADD_BOOK);
                break;
            case LOGGED_IN_PANEL_ADD_USER_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_ADD_USER);
                break;
            case LOGGED_IN_PANEL_BOOK_LOG_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_LOG_LIST);
                break;
            case LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_YOUR_ACCOUNT);
                break;
            default:
                controlPanel.setActiveIndex(NUMB_OF_LOGGED_IN_PANEL_LIBRARIAN_FUNC);
                break;

            }
            break;
        default:
            break;
        }
        loggedInStatusChanged = true;
    }
}

void AppWindowLoggedInPanel::setAppWindowLoggedInStatus(AppWindowLoggedInStatus awlis, Book* bookDataPtrF){
    if(awlis != *loggedInStatus){
        WINDOW_STATUS_SAVE(loggedInStatus);
        *loggedInStatus = awlis;
        bookDataPtr = bookDataPtrF;        
        switch(user->getUserPermissions()){
        case USER_PERMISSIONS_ADMIN:
            switch(awlis){
            case LOGGED_IN_PANEL_BOOKS_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_BOOKS);
                break;
            case LOGGED_IN_PANEL_USERS_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_USERS);
                break;
            case LOGGED_IN_PANEL_ADD_BOOK_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_ADD_BOOK);
                break;
            case LOGGED_IN_PANEL_ADD_USER_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_ADD_USER);
                break;
            case LOGGED_IN_PANEL_BOOK_LOG_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_LOG_LIST);
                break;
            case LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_ADMIN_YOUR_ACCOUNT);
                break;
            default:
                controlPanel.setActiveIndex(NUMB_OF_LOGGED_IN_PANEL_ADMIN_FUNC);
                break;

            }
            break;
        case USER_PERMISSIONS_READER:
            switch(awlis){
            case LOGGED_IN_PANEL_LIBRARY_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_READER_LIBRARY);
                break;
            case LOGGED_IN_PANEL_MY_BOOKS_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_READER_YOUR_BOOKS);
                break;
            case LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_READER_YOUR_ACCOUNT);
                break;
            default:
                controlPanel.setActiveIndex(NUMB_OF_LOGGED_IN_PANEL_ADMIN_FUNC);
                break;
            }
            break;
        case USER_PERMISSIONS_LIBRARIAN:
            switch(awlis){
            case LOGGED_IN_PANEL_BOOKS_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_BOOKS);
                break;
            case LOGGED_IN_PANEL_READERS_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_READERS);
                break;
            case LOGGED_IN_PANEL_ADD_BOOK_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_ADD_BOOK);
                break;
            case LOGGED_IN_PANEL_ADD_USER_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_ADD_USER);
                break;
            case LOGGED_IN_PANEL_BOOK_LOG_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_LOG_LIST);
                break;
            case LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT:
                controlPanel.setActiveIndex(LOGGED_IN_PANEL_LIBRARIAN_YOUR_ACCOUNT);
                break;
            default:
                controlPanel.setActiveIndex(NUMB_OF_LOGGED_IN_PANEL_LIBRARIAN_FUNC);
                break;
            }
            break;
        default:
            break;
        }
        loggedInStatusChanged = true;
    }
}

BooksLoggedInSave* AppWindowLoggedInPanel::getSavedBooks(){
    return &savedBooks;
}

BookLogsLoggedInSave* AppWindowLoggedInPanel::getSavedBookLogs(){
    return &savedBookLogs;
}

UsersLoggedInSave* AppWindowLoggedInPanel::getSavedUsers(){
    return &savedUsers;
}

UserFiltersLoggedInSave* AppWindowLoggedInPanel::getSavedUserFilters(){
    return &savedUserFilters;
}

BookFiltersLoggedInSave* AppWindowLoggedInPanel::getSavedBookFilters(){
    return &savedBookFilters;
}

BookLogFiltersLoggedInSave* AppWindowLoggedInPanel::getSavedBookLogFilters(){
    return &savedBookLogFilters;
}

User* AppWindowLoggedInPanel::getUserDataPtr(){
    return userDataPtr;
}

Book* AppWindowLoggedInPanel::getBookDataPtr(){
    return bookDataPtr;
}

void AppWindowLoggedInPanel::readDataFromServer(){

    bool getPreviousPage = false;
    // Prepare ReadFilesRules
    do{
    QString command;
    QJsonArray filtersArray;
    QJsonObject tempObj;
    QJsonObject msgObj;
    switch(getCurrentAppWindowLoggedInStat()){
    case LOGGED_IN_PANEL_MY_BOOKS_STAT:
        tempObj.insert(READ_FILE_RULES_FILTER_PARAM_TEXT, QString::number(BOOK_USER_ID));
        tempObj.insert(READ_FILE_RULES_FILTER_VALUE_TEXT, QString::number(user->getUserId()));
        filtersArray.append(tempObj);
    case LOGGED_IN_PANEL_LIBRARY_STAT:
    case LOGGED_IN_PANEL_BOOKS_STAT:
    {
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
        else {
            tempObj.insert(READ_FILE_RULES_SKIP_NUMB, QString::number(savedBooks.bookCurrentPage * 20));
        }
        tempObj.insert(READ_FILE_RULES_MAX_READ_TEXT, QString::number(20));
        msgObj.insert(READ_FILE_RULES_JSON_KEY_TEXT, tempObj);
        command = COMMAND_TYPE_BOOK_READ_TEXT;
    }
        break;
    case LOGGED_IN_PANEL_READERS_STAT:
        tempObj.insert(READ_FILE_RULES_FILTER_PARAM_TEXT, QString::number(USER_PERMISSIONS));
        tempObj.insert(READ_FILE_RULES_FILTER_VALUE_TEXT, QString::number(USER_PERMISSIONS_READER));
        filtersArray.append(tempObj);
        [[clang::fallthrough]];
    case LOGGED_IN_PANEL_USERS_STAT:
    {
        for(uint i = 0; i < savedUserFilters.numbOfFilters; i++){
            tempObj = QJsonObject();
            tempObj.insert(READ_FILE_RULES_FILTER_PARAM_TEXT, QString::number((savedUserFilters.userFilters + i)->param));
            tempObj.insert(READ_FILE_RULES_FILTER_VALUE_TEXT, (savedUserFilters.userFilters + i)->filterStr);
            filtersArray.append(tempObj);
        }
            tempObj = QJsonObject();
            tempObj.insert(READ_FILE_RULES_FILTER_TEXT, filtersArray);
            tempObj.insert(READ_FILE_RULES_FILE_TYPE_TEXT, QString::number(FILE_TYPE_CLIENTS_FILE));
            if(savedUsers.nextIdUser != 0)
                tempObj.insert(READ_FILE_RULES_START_ID_TEXT, QString::number(savedUsers.nextIdUser));
            else {
                tempObj.insert(READ_FILE_RULES_SKIP_NUMB, QString::number(savedUsers.userCurrentPage * 20));
            }
            tempObj.insert(READ_FILE_RULES_MAX_READ_TEXT, QString::number(20));
            msgObj.insert(READ_FILE_RULES_JSON_KEY_TEXT, tempObj);
            command = COMMAND_TYPE_CLIENT_READ_TEXT;
    }
        break;
    case LOGGED_IN_PANEL_BOOK_LOG_STAT:
    {
        if(user->getUserPermissions() != USER_PERMISSIONS_ADMIN){
        tempObj.insert(READ_FILE_RULES_FILTER_PARAM_TEXT, QString::number(BOOK_LOG_USER_PERMISSIONS));
        tempObj.insert(READ_FILE_RULES_FILTER_VALUE_TEXT, QString::number(USER_PERMISSIONS_READER));
        filtersArray.append(tempObj);
        tempObj = QJsonObject();
        tempObj.insert(READ_FILE_RULES_FILTER_PARAM_TEXT, QString::number(BOOK_LOG_USER_PERMISSIONS));
        tempObj.insert(READ_FILE_RULES_FILTER_VALUE_TEXT, QString::number(USER_PERMISSIONS_LIBRARIAN));
        filtersArray.append(tempObj);
        }
        for(uint i = 0; i < savedBookLogFilters.numbOfFilters; i++){
            tempObj = QJsonObject();
            tempObj.insert(READ_FILE_RULES_FILTER_PARAM_TEXT, QString::number((savedBookLogFilters.bookLogFilters + i)->param));
            tempObj.insert(READ_FILE_RULES_FILTER_VALUE_TEXT, (savedBookLogFilters.bookLogFilters + i)->filterStr);
            filtersArray.append(tempObj);
        }
            tempObj = QJsonObject();
            tempObj.insert(READ_FILE_RULES_FILTER_TEXT, filtersArray);
            tempObj.insert(READ_FILE_RULES_FILE_TYPE_TEXT, QString::number(FILE_TYPE_BOOK_LOG_FILE));
            tempObj.insert(READ_FILE_RULES_SKIP_NUMB, QString::number(savedBookLogs.bookLogCurrentPage * 20));
            tempObj.insert(READ_FILE_RULES_MAX_READ_TEXT, QString::number(20));
            msgObj.insert(READ_FILE_RULES_JSON_KEY_TEXT, tempObj);
            command = COMMAND_TYPE_BOOK_LOG_READ_TEXT;
    }
        break;
    default:
        return;
    }
    // Send to server
    QJsonDocument jDoc(msgObj);
    bool stop = false;
    while(!stop){
        if(parent->getParent()->getServer().getServerReplyStatus())
            return;
    ServerReplyStatus srs = parent->getParent()->getServer().setLastRequest(command, POST, jDoc);
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
                switch(getCurrentAppWindowLoggedInStat()){
                case LOGGED_IN_PANEL_LIBRARY_STAT:
                case LOGGED_IN_PANEL_BOOKS_STAT:
                case LOGGED_IN_PANEL_MY_BOOKS_STAT:
                    {
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
                            getPreviousPage = false;
                        }else{
                            SET_PTR_DOA(savedBooks.books, nullptr);
                            if(savedBooks.bookCurrentPage > 0){
                                savedBooks.bookCurrentPage--;
                                getPreviousPage = true;
                            }
                        }
                        savedBooks.numbOfBooks = len;
                        for(uint i = 0; i < len; i++){
                            QJsonObject retObj = retArray.at(i).toObject();
                            (savedBooks.books + i)->readJson(retObj);
                        }
                    }else{
                        //  Prompt Server Error
                        parent->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera - Odczyt danych nieudany."));
                    }
                    }
                    break;
                case LOGGED_IN_PANEL_USERS_STAT:
                case LOGGED_IN_PANEL_READERS_STAT:
                {
                    if(obj.value(READ_FILE_RULES_NEXT_POSSIBLE_READ_ID) != QJsonValue::Undefined){
                       savedUsers.nextIdUser = obj.value(READ_FILE_RULES_NEXT_POSSIBLE_READ_ID).toString().toULongLong();
                    }else{
                        savedUsers.nextIdUser = 0;
                    }
                    if(obj.value(USER_JSON_KEY_TEXT) != QJsonValue::Undefined){
                        QJsonArray retArray = obj.value(USER_JSON_KEY_TEXT).toArray();
                        uint len = retArray.count();
                        if(len > 0){
                            SET_PTR_DOA(savedUsers.users, new User[len]);
                            getPreviousPage = false;
                        }
                        else{
                            SET_PTR_DOA(savedUsers.users, nullptr);
                            if(savedUsers.userCurrentPage > 0){
                                savedUsers.userCurrentPage--;
                                getPreviousPage = true;
                            }
                        }
                        savedUsers.numbOfUsers = len;
                        for(uint i = 0; i < len; i++){
                            QJsonObject retObj = retArray.at(i).toObject();
                            (savedUsers.users + i)->readJson(retObj);
                        }
                    }else{
                        //  Prompt Server Error
                        parent->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera - Odczyt danych nieudany."));
                    }
                }
                    break;
                case LOGGED_IN_PANEL_BOOK_LOG_STAT:
                {
                    if(obj.value(READ_FILE_RULES_NEXT_POSSIBLE_READ_ID) != QJsonValue::Undefined){
                       savedBookLogs.nextBookLog = true;
                    }else{
                        savedBookLogs.nextBookLog = false;
                    }
                    if(obj.value(BOOK_LOG_JSON_KEY_TEXT) != QJsonValue::Undefined){
                        QJsonArray retArray = obj.value(BOOK_LOG_JSON_KEY_TEXT).toArray();
                        uint len = retArray.count();
                        if(len > 0){
                            SET_PTR_DOA(savedBookLogs.bookLogs, new BookLog[len]);
                            getPreviousPage = false;
                        }
                        else{
                            SET_PTR_DOA(savedBookLogs.bookLogs, nullptr);
                            if(savedBookLogs.bookLogCurrentPage > 0){
                                savedBookLogs.bookLogCurrentPage--;
                                getPreviousPage = true;
                            }
                        }
                        savedBookLogs.numbOfBookLogs = len;
                        for(uint i = 0; i < len; i++){
                            QJsonObject retObj = retArray.at(i).toObject();
                            (savedBookLogs.bookLogs + i)->readJson(retObj);
                        }
                    }else{
                        //  Prompt Server Error
                        parent->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera - Odczyt danych nieudany."));
                    }
                }
                    break;
                default:
                    break;
                }
            }
                break;
                // _PH_ Check other errors
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
  }while(getPreviousPage);

}

bool AppWindowLoggedInPanel::isLoggedInStatusChanged(){
    return loggedInStatusChanged;
}
