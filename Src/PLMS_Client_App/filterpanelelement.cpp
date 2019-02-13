#include"filterpanelelement.hpp"
#include"filterpanel.hpp"
#include"filteredlist.hpp"
#include"operationpanelfilteredlist.hpp"
#include"appwindowloggedinpanel.hpp"
#include<QLineEdit>
#include<QKeyEvent>
#include<QAbstractItemView>
#include<QEvent>

enum BooksStateParamList{
    BOOKS_STATE_PARAM_LIST_BOOK_ID,
    BOOKS_STATE_PARAM_LIST_BOOK_STATUS,
    BOOKS_STATE_PARAM_LIST_BOOK_TYPE,
    BOOKS_STATE_PARAM_LIST_BOOK_TITLE,    
    BOOKS_STATE_PARAM_LIST_BOOK_PUBLISHER,
    BOOKS_STATE_PARAM_LIST_BOOK_EDITION,
    BOOKS_STATE_PARAM_LIST_BOOK_AUTHOR,
    NUMB_OF_BOOKS_STAT_PARAM_LIST
};

enum BookLogsStateParamList{
    BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PESEL,
    BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_FIRST_NAME,
    BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_SURNAME,
    BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION,
    BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION_DATE_TIME,
    BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_BOOK_ID,
    BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PERMISSIONS,
    NUMB_OF_BOOK_LOGS_STAT_PARAM_LIST
};

enum UserStateParamList{
    USER_STATE_PARAM_LIST_USER_NAME,
    USER_STATE_PARAM_LIST_FIRST_NAME,
    USER_STATE_PARAM_LIST_SECOND_NAME,
    USER_STATE_PARAM_LIST_SURNAME,
    USER_STATE_PARAM_LIST_PESEL,
    USER_STATE_PARAM_LIST_PERMISSIONS,
    NUMB_OF_USER_STATE_PARAM_LIST
};



FilterPanelElement::FilterPanelElement(FilterPanel *parent, uint number)
    : QFrame(parent), parent(parent), number(number), parametersList(this), deleteButton(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    setStyleSheet("FilterPanelElement{background-color: transparent;}");
}


FilterPanelElement::FilterPanelElement(FilterPanel *parent, uint number, BooksFileFilter* bookFileFilter)
    : QFrame(parent), parent(parent), number(number), parametersList(this), deleteButton(this)
{
    init(*bookFileFilter);
    setWindow();
    connectAll();
    setStyleSheet("FilterPanelElement{background-color: transparent;}");
}


FilterPanelElement::FilterPanelElement(FilterPanel *parent, uint number, ClientsFileFilter* clientsFileFilter)
    : QFrame(parent), parent(parent), number(number), parametersList(this), deleteButton(this)
{
    init(*clientsFileFilter);
    setWindow();
    connectAll();
    setStyleSheet("FilterPanelElement{background-color: transparent;}");
}

FilterPanelElement::FilterPanelElement(FilterPanel *parent, uint number, BookLogsFileFilter* bookLogsFileFilter)
    : QFrame(parent), parent(parent), number(number), parametersList(this), deleteButton(this)
{
    init(*bookLogsFileFilter);
    setWindow();
    connectAll();
    setStyleSheet("FilterPanelElement{background-color: transparent;}");
}

FilterPanelElement::~FilterPanelElement(){
    disconnectAll();
    deleteWidgets();
}

void FilterPanelElement::init(){
    switch(parent->getParent()->getFilterType()){
    case FILE_TYPE_BOOKS_FILE:
    {
        parametersList.addItem("Indeks");
        parametersList.addItem("Status");
        parametersList.addItem("Gatunek");
        parametersList.addItem("Tytuł");
        parametersList.addItem("Wydawca");
        parametersList.addItem("Wydanie");
        parametersList.addItem("Autor");
        parametersList.setCurrentIndex(0);

    }
        break;
    case FILE_TYPE_CLIENTS_FILE:
    {
        parametersList.addItem("Nazwa użytkownika");
        parametersList.addItem("Imie");
        parametersList.addItem("Drugie imie");
        parametersList.addItem("Nazwisko");
        parametersList.addItem("Pesel");
        if(static_cast<AppWindowLoggedInStatus>(parent->getParent()->getParent()->getParent()->getCurrentAppWindowLoggedInStat()) == LOGGED_IN_PANEL_USERS_STAT)
            parametersList.addItem("Uprawnienia");
        parametersList.setCurrentIndex(0);
    }
        break;
    case FILE_TYPE_BOOK_LOG_FILE:
    {
        parametersList.addItem("Pesel");
        parametersList.addItem("Imie");        
        parametersList.addItem("Nazwisko");        
        parametersList.addItem("Działanie");
        parametersList.addItem("Data i czas");
        parametersList.addItem("Indeks książki");
        if(static_cast<AppWindowLoggedInStatus>(parent->getParent()->getParent()->getParent()->getCurrentAppWindowLoggedInStat()) == LOGGED_IN_PANEL_USERS_STAT)
            parametersList.addItem("Uprawnienia");
        parametersList.setCurrentIndex(0);
    }
        break;
    default:
        break;
    }
    // Parameters List
    parametersList.setGeometry(FILTER_ELEMENT_PARAM_LIST_X,FILTER_ELEMENT_PARAM_LIST_Y,FILTER_ELEMENT_PARAM_LIST_WIDTH,FILTER_ELEMENT_PARAM_LIST_HEIGHT);

    // Delete Button
    deleteButton.setGeometry(FILTER_ELEMENT_REMOVE_BUTTON_X,FILTER_ELEMENT_REMOVE_BUTTON_Y,FILTER_ELEMENT_REMOVE_BUTTON_WIDTH,FILTER_ELEMENT_REMOVE_BUTTON_HEIGHT);
    deleteButton.setPixmap(FILTER_REMOVE_BUTTON_ICON);
    deleteButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    deleteButton.setScaledContents(true);

    parametersList.view()->installEventFilter(parent->getParent());
    deleteButton.installEventFilter(parent->getParent());
}

void FilterPanelElement::init(BooksFileFilter& booksFileFilter){

        parametersList.addItem("Indeks");
        parametersList.addItem("Status");
        parametersList.addItem("Gatunek");
        parametersList.addItem("Tytuł");
        parametersList.addItem("Wydawca");
        parametersList.addItem("Wydanie");
        parametersList.addItem("Autor");
        if(booksFileFilter.param == BOOK_ID){
            parametersList.setCurrentIndex(0);
        }else{
            parametersList.setCurrentIndex(booksFileFilter.param - 1);
        }

        createWidgets();
        createLayout();
        switch (static_cast<BooksStateParamList>(parametersList.currentIndex())) {
        case BOOKS_STATE_PARAM_LIST_BOOK_TYPE:
        case BOOKS_STATE_PARAM_LIST_BOOK_STATUS:
            choiceList->setCurrentIndex(booksFileFilter.filterStr.toUInt());
            break;
        case BOOKS_STATE_PARAM_LIST_BOOK_AUTHOR:
        case BOOKS_STATE_PARAM_LIST_BOOK_ID:
        case BOOKS_STATE_PARAM_LIST_BOOK_TITLE:
        case BOOKS_STATE_PARAM_LIST_BOOK_EDITION:
        case BOOKS_STATE_PARAM_LIST_BOOK_PUBLISHER:
            lineEdit->setText(booksFileFilter.filterStr);
            lineEdit->setStyleSheet("");
            lineEditOk = true;
            break;
        default:
            break;
        }
    // Parameters List
    parametersList.setGeometry(FILTER_ELEMENT_PARAM_LIST_X,FILTER_ELEMENT_PARAM_LIST_Y,FILTER_ELEMENT_PARAM_LIST_WIDTH,FILTER_ELEMENT_PARAM_LIST_HEIGHT);

    // Delete Button
    deleteButton.setGeometry(FILTER_ELEMENT_REMOVE_BUTTON_X,FILTER_ELEMENT_REMOVE_BUTTON_Y,FILTER_ELEMENT_REMOVE_BUTTON_WIDTH,FILTER_ELEMENT_REMOVE_BUTTON_HEIGHT);
    deleteButton.setPixmap(FILTER_REMOVE_BUTTON_ICON);
    deleteButton.setScaledContents(true);
    deleteButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);

    parametersList.view()->installEventFilter(parent->getParent());
    deleteButton.installEventFilter(parent->getParent());
}

void FilterPanelElement::init(ClientsFileFilter& clientsFileFilter){
    parametersList.addItem("Nazwa użytkownika");
        parametersList.addItem("Imie");
        parametersList.addItem("Drugie imie");
        parametersList.addItem("Nazwisko");
        parametersList.addItem("Pesel");
        if(static_cast<AppWindowLoggedInStatus>(parent->getParent()->getParent()->getParent()->getCurrentAppWindowLoggedInStat()) == LOGGED_IN_PANEL_USERS_STAT)
            parametersList.addItem("Uprawnienia");
        switch (clientsFileFilter.param) {
        case USER_NAME:
            parametersList.setCurrentIndex(0);
            break;
        case USER_FIRST_NAME:
        case USER_SURNAME:
        case USER_SECOND_NAME:
        case USER_PESEL:
            parametersList.setCurrentIndex(clientsFileFilter.param - 3);
            break;
        case USER_PERMISSIONS:
            parametersList.setCurrentIndex(5);
            break;
        default:
            break;
        }
        createWidgets();
        createLayout();
        switch (static_cast<UserStateParamList>(parametersList.currentIndex())) {
        case USER_STATE_PARAM_LIST_PERMISSIONS:
            choiceList->setCurrentIndex(clientsFileFilter.filterStr.toUInt());
            break;
        case USER_STATE_PARAM_LIST_PESEL:
        case USER_STATE_PARAM_LIST_SURNAME:
        case USER_STATE_PARAM_LIST_USER_NAME:
        case USER_STATE_PARAM_LIST_FIRST_NAME:
        case USER_STATE_PARAM_LIST_SECOND_NAME:
            lineEdit->setText(clientsFileFilter.filterStr);
            lineEdit->setStyleSheet("");
            lineEditOk = true;
            break;
        default:
            break;
        }
        // Parameters List
    parametersList.setGeometry(FILTER_ELEMENT_PARAM_LIST_X,FILTER_ELEMENT_PARAM_LIST_Y,FILTER_ELEMENT_PARAM_LIST_WIDTH,FILTER_ELEMENT_PARAM_LIST_HEIGHT);

    // Delete Button
    deleteButton.setGeometry(FILTER_ELEMENT_REMOVE_BUTTON_X,FILTER_ELEMENT_REMOVE_BUTTON_Y,FILTER_ELEMENT_REMOVE_BUTTON_WIDTH,FILTER_ELEMENT_REMOVE_BUTTON_HEIGHT);
    deleteButton.setPixmap(FILTER_REMOVE_BUTTON_ICON);
    deleteButton.setScaledContents(true);
    deleteButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);

    parametersList.view()->installEventFilter(parent->getParent());
    deleteButton.installEventFilter(parent->getParent());
}

void FilterPanelElement::init(BookLogsFileFilter& bookLogsFileFilter){
    parametersList.addItem("Pesel");
    parametersList.addItem("Imie");
    parametersList.addItem("Nazwisko");
    parametersList.addItem("Działanie");
    parametersList.addItem("Data i czas");
    parametersList.addItem("Indeks książki");
    if(static_cast<AppWindowLoggedInStatus>(parent->getParent()->getParent()->getParent()->getCurrentAppWindowLoggedInStat()) == LOGGED_IN_PANEL_USERS_STAT)
        parametersList.addItem("Uprawnienia");
    switch (bookLogsFileFilter.param) {
    case BOOK_LOG_USER_PESEL:
    case BOOK_LOG_USER_FIRST_NAME:
    case BOOK_LOG_USER_SURNAME:
        parametersList.setCurrentIndex(bookLogsFileFilter.param);
        break;
    case BOOK_LOG_USER_PERMISSIONS:
        parametersList.setCurrentIndex(6);
        break;
    case BOOK_LOG_ACTION:
    case BOOK_LOG_BOOK_ID:
    case BOOK_LOG_ACTION_DATE_TIME:
        parametersList.setCurrentIndex(bookLogsFileFilter.param - 1);
        break;
    default:
        break;
    }
        createWidgets();
        createLayout();
        switch (static_cast<BookLogsStateParamList>(parametersList.currentIndex())) {
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PERMISSIONS:
            choiceList->setCurrentIndex(bookLogsFileFilter.filterStr.toUInt());
            break;
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_BOOK_ID:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PESEL:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_SURNAME:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_FIRST_NAME:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION_DATE_TIME:
            lineEdit->setText(bookLogsFileFilter.filterStr);
            lineEditOk = true;
            lineEdit->setStyleSheet("");
            break;
        default:
            break;
        }
    // Parameters List
    parametersList.setGeometry(FILTER_ELEMENT_PARAM_LIST_X,FILTER_ELEMENT_PARAM_LIST_Y,FILTER_ELEMENT_PARAM_LIST_WIDTH,FILTER_ELEMENT_PARAM_LIST_HEIGHT);

    // Delete Button
    deleteButton.setGeometry(FILTER_ELEMENT_REMOVE_BUTTON_X,FILTER_ELEMENT_REMOVE_BUTTON_Y,FILTER_ELEMENT_REMOVE_BUTTON_WIDTH,FILTER_ELEMENT_REMOVE_BUTTON_HEIGHT);
    deleteButton.setPixmap(FILTER_REMOVE_BUTTON_ICON);
    deleteButton.setScaledContents(true);
    deleteButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);

    parametersList.view()->installEventFilter(parent->getParent());
    deleteButton.installEventFilter(parent->getParent());
}

void FilterPanelElement::setWindow(){
    resize(FILTER_ELEMENT_WIDTH, 2 * FILTER_ELEMENT_VERTICAL_OFFSET + FILTER_ELEMENT_BUTTON_HEIGHT);
}

void FilterPanelElement::createWidgets(){
    switch(parent->getParent()->getFilterType()){
    case FILE_TYPE_BOOKS_FILE:
    {
        switch (static_cast<BooksStateParamList>(parametersList.currentIndex())) {
        case BOOKS_STATE_PARAM_LIST_BOOK_TYPE:
        case BOOKS_STATE_PARAM_LIST_BOOK_STATUS:
            SET_PTR_DO(choiceList, new QComboBox(this));            
            break;
        case BOOKS_STATE_PARAM_LIST_BOOK_AUTHOR:
        case BOOKS_STATE_PARAM_LIST_BOOK_ID:
        case BOOKS_STATE_PARAM_LIST_BOOK_TITLE:
        case BOOKS_STATE_PARAM_LIST_BOOK_EDITION:
        case BOOKS_STATE_PARAM_LIST_BOOK_PUBLISHER:
            SET_PTR_DO(lineEdit, new QLineEdit(this));
            break;
        default:
            break;
        }
    }
        break;
    case FILE_TYPE_CLIENTS_FILE:
    {
        switch (static_cast<UserStateParamList>(parametersList.currentIndex())) {
        case USER_STATE_PARAM_LIST_PERMISSIONS:
            SET_PTR_DO(choiceList, new QComboBox(this));
            break;
        case USER_STATE_PARAM_LIST_PESEL:
        case USER_STATE_PARAM_LIST_SURNAME:
        case USER_STATE_PARAM_LIST_USER_NAME:
        case USER_STATE_PARAM_LIST_FIRST_NAME:
        case USER_STATE_PARAM_LIST_SECOND_NAME:
            SET_PTR_DO(lineEdit, new QLineEdit(this));
            break;
        default:
            break;
        }
    }
        break;
    case FILE_TYPE_BOOK_LOG_FILE:
    {
        switch (static_cast<BookLogsStateParamList>(parametersList.currentIndex())) {
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PERMISSIONS:
            SET_PTR_DO(choiceList, new QComboBox(this));
            break;
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_BOOK_ID:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PESEL:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_SURNAME:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_FIRST_NAME:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION_DATE_TIME:
            SET_PTR_DO(lineEdit, new QLineEdit(this));
            break;
        default:
            break;
        }
    }
        break;
    default:
        break;
    }
}

void FilterPanelElement::createLayout(){
    // Dynamic Elements
    switch(parent->getParent()->getFilterType()){
    case FILE_TYPE_BOOKS_FILE:
    {
        switch (static_cast<BooksStateParamList>(parametersList.currentIndex())) {
        case BOOKS_STATE_PARAM_LIST_BOOK_TYPE:
            choiceList->addItem("Autobiografia");
            choiceList->addItem("Biografia");
            choiceList->addItem("Słownik");
            choiceList->addItem("Encyklopedia");
            choiceList->addItem("Historyczna");
            choiceList->addItem("Czasopismo");
            choiceList->addItem("Przewodnik");
            choiceList->addItem("Nauka");
            choiceList->addItem("Kryminał");
            choiceList->addItem("Romans");
            choiceList->addItem("Fantastyka naukowa");
            choiceList->addItem("Dramat");
            choiceList->addItem("Bajka");
            choiceList->addItem("Fantastyka");
            choiceList->addItem("Poezja");
            choiceList->addItem("Satyra");
            choiceList->addItem("Komiks");
            choiceList->addItem("Groza");
            choiceList->addItem("Thriller");
            choiceList->addItem("Literatura dziecięca");
            choiceList->setCurrentIndex(0);
            choiceList->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
            break;
        case BOOKS_STATE_PARAM_LIST_BOOK_STATUS:
            choiceList->addItem("Dostępna");
            choiceList->addItem("Zarezerwowana");
            choiceList->addItem("Wypożyczona");
            choiceList->addItem("Do oddania");
            choiceList->setCurrentIndex(0);
            choiceList->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
            break;
        case BOOKS_STATE_PARAM_LIST_BOOK_AUTHOR:
        case BOOKS_STATE_PARAM_LIST_BOOK_ID:
        case BOOKS_STATE_PARAM_LIST_BOOK_TITLE:
        case BOOKS_STATE_PARAM_LIST_BOOK_EDITION:
        case BOOKS_STATE_PARAM_LIST_BOOK_PUBLISHER:
            lineEdit->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
            lineEdit->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
            break;
        default:
            break;
        }
    }
        break;
    case FILE_TYPE_CLIENTS_FILE:
    {
        switch (static_cast<UserStateParamList>(parametersList.currentIndex())) {
        case USER_STATE_PARAM_LIST_PERMISSIONS:
            choiceList->addItem("Czytelnik");
            choiceList->addItem("Bibliotekarz");
            choiceList->addItem("Administrator");
            choiceList->setCurrentIndex(0);
            choiceList->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
            break;
        case USER_STATE_PARAM_LIST_PESEL:
        case USER_STATE_PARAM_LIST_SURNAME:
        case USER_STATE_PARAM_LIST_USER_NAME:
        case USER_STATE_PARAM_LIST_FIRST_NAME:
        case USER_STATE_PARAM_LIST_SECOND_NAME:
            lineEdit->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
            lineEdit->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
            break;
        default:
            break;
        }
    }
        break;
    case FILE_TYPE_BOOK_LOG_FILE:
    {
        switch (static_cast<BookLogsStateParamList>(parametersList.currentIndex())) {
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION:
            choiceList->addItem("Logowanie");
            choiceList->addItem("Dodanie użytkownika");
            choiceList->addItem("Rejestracja");
            choiceList->addItem("Usunięcie użytkownika");
            choiceList->addItem("Wylogowanie");
            choiceList->addItem("Dodanie książki");
            choiceList->addItem("Rezerwacja książki");
            choiceList->addItem("Wypożyczenie książki");
            choiceList->addItem("Wygaśnięcie książki");
            choiceList->addItem("Oddanie książki");
            choiceList->addItem("Dodanie/edycja komentarza");
            choiceList->addItem("Usunięcie komentarza");
            choiceList->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
            break;
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PERMISSIONS:
            choiceList->addItem("Czytelnik");
            choiceList->addItem("Bibliotekarz");
            choiceList->addItem("Administrator");
            choiceList->setCurrentIndex(0);
            choiceList->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
            break;
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_BOOK_ID:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PESEL:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_SURNAME:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_FIRST_NAME:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION_DATE_TIME:
            lineEdit->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
            lineEdit->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
            break;
        default:
            break;
        }
    }
        break;
    default:
        break;
    }
}

void FilterPanelElement::deleteWidgets(){
    SET_PTR_DO(lineEdit, nullptr);
    SET_PTR_DO(choiceList, nullptr);
}

void FilterPanelElement::connectAll(){
    switch(parent->getParent()->getFilterType()){
    case FILE_TYPE_BOOKS_FILE:
    {
        switch (static_cast<BooksStateParamList>(parametersList.currentIndex())) {
        case BOOKS_STATE_PARAM_LIST_BOOK_TYPE:
        case BOOKS_STATE_PARAM_LIST_BOOK_STATUS:
            break;
        case BOOKS_STATE_PARAM_LIST_BOOK_AUTHOR:
        case BOOKS_STATE_PARAM_LIST_BOOK_ID:
        case BOOKS_STATE_PARAM_LIST_BOOK_TITLE:
        case BOOKS_STATE_PARAM_LIST_BOOK_EDITION:
        case BOOKS_STATE_PARAM_LIST_BOOK_PUBLISHER:
            lineEdit->installEventFilter(parent->getParent());
            break;
        default:
            break;
        }
    }
        break;
    case FILE_TYPE_CLIENTS_FILE:
    {
        switch (static_cast<UserStateParamList>(parametersList.currentIndex())) {
        case USER_STATE_PARAM_LIST_PERMISSIONS:
            break;
        case USER_STATE_PARAM_LIST_PESEL:
        case USER_STATE_PARAM_LIST_SURNAME:
        case USER_STATE_PARAM_LIST_USER_NAME:
        case USER_STATE_PARAM_LIST_FIRST_NAME:
        case USER_STATE_PARAM_LIST_SECOND_NAME:
            lineEdit->installEventFilter(parent->getParent());
            break;
        default:
            break;
        }
    }
        break;
    case FILE_TYPE_BOOK_LOG_FILE:
    {
        switch (static_cast<BookLogsStateParamList>(parametersList.currentIndex())) {
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PERMISSIONS:
            break;
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_BOOK_ID:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PESEL:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_SURNAME:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_FIRST_NAME:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION_DATE_TIME:
            lineEdit->installEventFilter(parent->getParent());
            break;
        default:
            break;
        }
    }
        break;
    default:
        break;
    }
}

void FilterPanelElement::disconnectAll(){
    // Empty
}

FilterPanel* FilterPanelElement::getParent(){
    return parent;
}

bool FilterPanelElement::eventMatching(QObject *obj, QEvent *ev){
    switch(ev->type()){
    case QEvent::MouseButtonRelease:
    {
        if(obj == &deleteButton){
            parent->removeElement(this);
            return true;
        }
    }
        break;
    case QEvent::KeyPress:
    {
        if(obj == lineEdit){
            if(lineEditKeyPressed(static_cast<QKeyEvent*>(ev))){
                return true;
            }
        }
    }
        break;
    case QEvent::Enter:
    {
        if(obj == &deleteButton){
            deleteButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            return false;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &deleteButton){
            deleteButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            return false;
        }
        if(obj == parametersList.view()){
            switch(parent->getParent()->getFilterType()){
            case FILE_TYPE_BOOKS_FILE:
            {
                switch (static_cast<BooksStateParamList>(parametersList.currentIndex())) {
                case BOOKS_STATE_PARAM_LIST_BOOK_TYPE:
                    if(!choiceList){
                        SET_PTR_DO(lineEdit, nullptr);
                        SET_PTR_DO(choiceList, new QComboBox(this));
                        choiceList->addItem("Autobiografia");
                        choiceList->addItem("Biografia");
                        choiceList->addItem("Słownik");
                        choiceList->addItem("Encyklopedia");
                        choiceList->addItem("Historyczna");
                        choiceList->addItem("Czasopismo");
                        choiceList->addItem("Przewodnik");
                        choiceList->addItem("Nauka");
                        choiceList->addItem("Kryminał");
                        choiceList->addItem("Romans");
                        choiceList->addItem("Fantastyka naukowa");
                        choiceList->addItem("Dramat");
                        choiceList->addItem("Bajka");
                        choiceList->addItem("Fantastyka");
                        choiceList->addItem("Poezja");
                        choiceList->addItem("Satyra");
                        choiceList->addItem("Komiks");
                        choiceList->addItem("Groza");
                        choiceList->addItem("Thriller");
                        choiceList->addItem("Literatura dziecięca");
                        choiceList->setCurrentIndex(0);
                        choiceList->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
                        choiceList->show();
                    }
                    break;
                case BOOKS_STATE_PARAM_LIST_BOOK_STATUS:
                    if(!choiceList){
                        SET_PTR_DO(lineEdit, nullptr);
                        SET_PTR_DO(choiceList, new QComboBox(this));
                        choiceList->addItem("Dostępna");
                        choiceList->addItem("Zarezerwowana");
                        choiceList->addItem("Wypożyczona");
                        choiceList->addItem("Do oddania");
                        choiceList->setCurrentIndex(0);
                        choiceList->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
                        choiceList->show();
                    }
                    break;
                case BOOKS_STATE_PARAM_LIST_BOOK_AUTHOR:
                case BOOKS_STATE_PARAM_LIST_BOOK_ID:
                case BOOKS_STATE_PARAM_LIST_BOOK_TITLE:
                case BOOKS_STATE_PARAM_LIST_BOOK_EDITION:
                case BOOKS_STATE_PARAM_LIST_BOOK_PUBLISHER:
                    if(!lineEdit){
                        SET_PTR_DO(choiceList, nullptr);
                        SET_PTR_DO(lineEdit, new QLineEdit(this);)
                        lineEdit->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
                        lineEdit->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
                        lineEdit->installEventFilter(parent->getParent());
                        lineEdit->show();
                    }
                    break;
                default:
                    break;
                }
            }
                break;
            case FILE_TYPE_CLIENTS_FILE:
            {
                switch (static_cast<UserStateParamList>(parametersList.currentIndex())) {
                case USER_STATE_PARAM_LIST_PERMISSIONS:
                    if(!choiceList){
                        SET_PTR_DO(lineEdit, nullptr);
                        SET_PTR_DO(choiceList, new QComboBox(this));
                        choiceList->addItem("Czytelnik");
                        choiceList->addItem("Bibliotekarz");
                        choiceList->addItem("Administrator");
                        choiceList->setCurrentIndex(0);
                        choiceList->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
                        choiceList->show();
                    }
                    break;
                case USER_STATE_PARAM_LIST_PESEL:
                case USER_STATE_PARAM_LIST_SURNAME:
                case USER_STATE_PARAM_LIST_USER_NAME:
                case USER_STATE_PARAM_LIST_FIRST_NAME:
                case USER_STATE_PARAM_LIST_SECOND_NAME:
                    if(!lineEdit){
                        SET_PTR_DO(choiceList, nullptr);
                        SET_PTR_DO(lineEdit, new QLineEdit(this);)
                        lineEdit->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
                        lineEdit->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
                        lineEdit->installEventFilter(parent->getParent());
                        lineEdit->show();
                    }
                    break;
                default:
                    break;
                }
            }
                break;
            case FILE_TYPE_BOOK_LOG_FILE:
            {
                switch (static_cast<BookLogsStateParamList>(parametersList.currentIndex())) {
                case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION:
                    if(!choiceList){
                    SET_PTR_DO(lineEdit, nullptr);
                    SET_PTR_DO(choiceList, new QComboBox(this));
                    choiceList->addItem("Logowanie");
                    choiceList->addItem("Dodanie użytkownika");
                    choiceList->addItem("Rejestracja");
                    choiceList->addItem("Usunięcie użytkownika");
                    choiceList->addItem("Wylogowanie");
                    choiceList->addItem("Dodanie książki");
                    choiceList->addItem("Rezerwacja książki");
                    choiceList->addItem("Wypożyczenie książki");
                    choiceList->addItem("Wygaśnięcie książki");
                    choiceList->addItem("Oddanie książki");
                    choiceList->addItem("Usunięcie książki");
                    choiceList->addItem("Dodanie/edycja komentarza");
                    choiceList->addItem("Usunięcie komentarza");
                    choiceList->setCurrentIndex(0);
                    choiceList->installEventFilter(parent);
                    choiceList->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
                    choiceList->show();
                    }
                    break;
                case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PERMISSIONS:
                    if(!choiceList){
                        SET_PTR_DO(lineEdit, nullptr);
                        SET_PTR_DO(choiceList, new QComboBox(this));
                        choiceList->addItem("Czytelnik");
                        choiceList->addItem("Bibliotekarz");
                        choiceList->addItem("Administrator");
                        choiceList->setCurrentIndex(0);
                        choiceList->installEventFilter(parent);
                        choiceList->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
                        choiceList->show();
                    }
                    break;
                case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_BOOK_ID:
                case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PESEL:
                case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_SURNAME:
                case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_FIRST_NAME:
                case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION_DATE_TIME:
                    if(!lineEdit){
                        SET_PTR_DO(choiceList, nullptr);
                        SET_PTR_DO(lineEdit, new QLineEdit(this);)
                        lineEdit->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
                        lineEdit->setGeometry(FILTER_ELEMENT_DYNAMIC_ELEMENT_X,FILTER_ELEMENT_DYNAMIC_ELEMENT_Y,FILTER_ELEMENT_DYNAMIC_ELEMENT_WIDTH,FILTER_ELEMENT_DYNAMIC_ELEMENT_HEIGHT);
                        lineEdit->show();
                    }
                    break;
                default:
                    break;
                }
            }
                break;
            default:
                break;
            }
        }
    }
        break;
    default:
        break;
    }
    return false;
}

void FilterPanelElement::reload(){
    disconnectAll();
    deleteWidgets();
    createWidgets();
    createLayout();
    connectAll();
}

bool FilterPanelElement::isCorrect(){
    switch(parent->getParent()->getFilterType()){
    case FILE_TYPE_BOOKS_FILE:
    {
        switch (static_cast<BooksStateParamList>(parametersList.currentIndex())) {
        case BOOKS_STATE_PARAM_LIST_BOOK_TYPE:
        case BOOKS_STATE_PARAM_LIST_BOOK_STATUS:
            break;
        case BOOKS_STATE_PARAM_LIST_BOOK_AUTHOR:
        case BOOKS_STATE_PARAM_LIST_BOOK_ID:
        case BOOKS_STATE_PARAM_LIST_BOOK_TITLE:
        case BOOKS_STATE_PARAM_LIST_BOOK_EDITION:
        case BOOKS_STATE_PARAM_LIST_BOOK_PUBLISHER:
            return lineEditOk;
        default:
            break;
        }
    }
        break;
    case FILE_TYPE_CLIENTS_FILE:
    {
        switch (static_cast<UserStateParamList>(parametersList.currentIndex())) {
        case USER_STATE_PARAM_LIST_PERMISSIONS:
            break;
        case USER_STATE_PARAM_LIST_PESEL:
        case USER_STATE_PARAM_LIST_SURNAME:
        case USER_STATE_PARAM_LIST_USER_NAME:
        case USER_STATE_PARAM_LIST_FIRST_NAME:
        case USER_STATE_PARAM_LIST_SECOND_NAME:
            return lineEditOk;
        default:
            break;
        }
    }
        break;
    case FILE_TYPE_BOOK_LOG_FILE:
    {
        switch (static_cast<BookLogsStateParamList>(parametersList.currentIndex())) {
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PERMISSIONS:
            break;
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_BOOK_ID:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PESEL:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_SURNAME:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_FIRST_NAME:
        case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION_DATE_TIME:
            return lineEditOk;
        default:
            break;
        }
    }
        break;
    default:
        break;
    }
    return true;
}

ClientsFileFilter FilterPanelElement::getClientFileFilter(){
    ClientsFileFilter cff;
    switch (static_cast<UserStateParamList>(parametersList.currentIndex())) {
    case USER_STATE_PARAM_LIST_PESEL:
        cff.param = USER_PESEL;
        cff.filterStr = lineEdit->text();
        break;
    case USER_STATE_PARAM_LIST_SURNAME:
        cff.param = USER_SURNAME;
        cff.filterStr = lineEdit->text();
        break;
    case USER_STATE_PARAM_LIST_USER_NAME:
        cff.param = USER_NAME;
        cff.filterStr = lineEdit->text();
        break;
    case USER_STATE_PARAM_LIST_FIRST_NAME:
        cff.param = USER_FIRST_NAME;
        cff.filterStr = lineEdit->text();
        break;
    case USER_STATE_PARAM_LIST_PERMISSIONS:
        cff.param = USER_PERMISSIONS;
        cff.filterStr = QString::number(choiceList->currentIndex());
        break;
    case USER_STATE_PARAM_LIST_SECOND_NAME:
        cff.param = USER_SECOND_NAME;
        cff.filterStr = lineEdit->text();
        break;        
    default:
        break;
    }
    return cff;
}

BooksFileFilter FilterPanelElement::getBookFileFilter(){
    BooksFileFilter bff;
    switch (static_cast<BooksStateParamList>(parametersList.currentIndex())) {
    case BOOKS_STATE_PARAM_LIST_BOOK_ID:
        bff.param = BOOK_ID;
        bff.filterStr = lineEdit->text();
        break;
    case BOOKS_STATE_PARAM_LIST_BOOK_TITLE:
        bff.param = BOOK_TITLE;
        bff.filterStr = lineEdit->text();
        break;
    case BOOKS_STATE_PARAM_LIST_BOOK_STATUS:
        bff.param = BOOK_STATUS;
        bff.filterStr = QString::number(choiceList->currentIndex());
        break;
    case BOOKS_STATE_PARAM_LIST_BOOK_EDITION:
        bff.param = BOOK_EDITION;
        bff.filterStr = lineEdit->text();
        break;
    case BOOKS_STATE_PARAM_LIST_BOOK_PUBLISHER:
        bff.param = BOOK_PUBLISHER;
        bff.filterStr = lineEdit->text();
        break;
    case BOOKS_STATE_PARAM_LIST_BOOK_TYPE:
        bff.param = BOOK_TYPE;
        bff.filterStr = QString::number(choiceList->currentIndex());
        break;
    case BOOKS_STATE_PARAM_LIST_BOOK_AUTHOR:
        bff.param = BOOK_AUTHOR;
        bff.filterStr = lineEdit->text();
        break;
    default:
        break;
    }
    return bff;
}

BookLogsFileFilter FilterPanelElement::getBookLogFileFilter(){
    BookLogsFileFilter bff;
    switch (static_cast<BookLogsStateParamList>(parametersList.currentIndex())) {
    case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION:
        bff.param = BOOK_LOG_ACTION;
        bff.filterStr = QString::number(choiceList->currentIndex());
        break;
    case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_BOOK_ID:
        bff.param = BOOK_LOG_BOOK_ID;
        bff.filterStr = lineEdit->text();
        break;
    case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PESEL:
        bff.param = BOOK_LOG_USER_PESEL;
        bff.filterStr = lineEdit->text();
        break;
    case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_SURNAME:
        bff.param = BOOK_LOG_USER_SURNAME;
        bff.filterStr = lineEdit->text();
        break;
    case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_FIRST_NAME:
        bff.param = BOOK_LOG_USER_FIRST_NAME;
        bff.filterStr = lineEdit->text();
        break;
    case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_USER_PERMISSIONS:
        bff.param = BOOK_LOG_USER_PERMISSIONS;
        bff.filterStr = QString::number(choiceList->currentIndex());
        break;
    case BOOK_LOGS_STATE_PARAM_LIST_BOOK_LOG_ACTION_DATE_TIME:
        bff.param = BOOK_LOG_ACTION_DATE_TIME;
        bff.filterStr = lineEdit->text();
        break;
    default:
        break;
    }
    return bff;
}

bool FilterPanelElement::lineEditKeyPressed(QKeyEvent *ev){
    uint len = lineEdit->text().length();
    if(len > 29){
        switch(ev->key()){
        case Qt::Key_Left:
            return false;
        case Qt::Key_Right:
            return false;
        case Qt::Key_Backspace:
            lineEdit->backspace();
            break;
        case Qt::Key_Delete:
            lineEdit->del();
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
            lineEdit->insert(" ");
        case Qt::Key_Control:
            return true;
        case Qt::Key_Backspace:
            lineEdit->backspace();
            break;
        case Qt::Key_Delete:
            lineEdit->del();
            break;
        default:
            lineEdit->insert(ev->text());
            break;
        }
    }
    len = lineEdit->text().length();
    if(lineEdit->text().isEmpty() || len > 30){
        lineEdit->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
        lineEditOk = false;
    }
    else{
        lineEdit->setStyleSheet("");
        lineEditOk = true;
    }
    return true;
}
