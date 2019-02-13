#include"operationlist.hpp"
#include"filteredlist.hpp"
#include"operationpanelfilteredlist.hpp"
#include"appwindowloggedinpanel.hpp"
#include"operationlistelementbooks.hpp"
#include"operationlistelementlibrary.hpp"
#include"operationlistelementmybooks.hpp"
#include"operationlistelementreaders.hpp"
#include"operationlistelementusers.hpp"
#include"operationlistelementbooklog.hpp"
#include"operationlistelementbookpanelusersbooks.hpp"
#include"bookpanel.hpp"
#include"../PLMS_Server_App/book.hpp"
#include"../PLMS_Server_App/user.hpp"
#include"../PLMS_Server_App/booklog.hpp"
#include"dialog.hpp"
#include"appwindow.hpp"
#include"appwindowcentralpanel.hpp"


OperationList::OperationList(FilteredList *parent)
    : QFrame(parent), parent(parent),
      upperControlBar(this, false, 0),
      bottomControlBar(this, false, 0),
      noElementsInfo(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    setStyleSheet("OperationList{background-color: transparent;}");
}

OperationList::~OperationList(){
    if(parent->getParent()->getBookPanelParent()){
        BooksLoggedInSave* bookLoggedInSave = nullptr;
            SET_PTR_NDO(bookLoggedInSave, parent->getParent()->getBookPanelParent()->getSavedBooks());
            bookLoggedInSave->bookCurrentPage = pageNumber;
            if(!nextPageAvailable)
                bookLoggedInSave->nextIdBook = 0;
    }else{
        switch(parent->getParent()->getParent()->getCurrentAppWindowLoggedInStat()){
        case LOGGED_IN_PANEL_BOOKS_STAT:
        case LOGGED_IN_PANEL_LIBRARY_STAT:
        case LOGGED_IN_PANEL_MY_BOOKS_STAT:
        {
            BooksLoggedInSave* bookLoggedInSave = nullptr;
            SET_PTR_NDO(bookLoggedInSave, parent->getParent()->getParent()->getSavedBooks());
            bookLoggedInSave->bookCurrentPage = pageNumber;
            if(!nextPageAvailable)
                bookLoggedInSave->nextIdBook = 0;
        }
            break;
        case LOGGED_IN_PANEL_USERS_STAT:
        case LOGGED_IN_PANEL_READERS_STAT:
        {
            UsersLoggedInSave* userLoggedInSave = nullptr;
            SET_PTR_NDO(userLoggedInSave, parent->getParent()->getParent()->getSavedUsers());
            userLoggedInSave->userCurrentPage = pageNumber;
            if(!nextPageAvailable)
                userLoggedInSave->nextIdUser = 0;
        }
            break;
        case LOGGED_IN_PANEL_BOOK_LOG_STAT:
        {
            BookLogsLoggedInSave* bookLogsLoggedInSave = nullptr;
            SET_PTR_NDO(bookLogsLoggedInSave, parent->getParent()->getParent()->getSavedBookLogs());
            bookLogsLoggedInSave->bookLogCurrentPage = pageNumber;
            if(!nextPageAvailable)
                bookLogsLoggedInSave->nextBookLog = 0;
        }
            break;
        default:
            break;
        }
    }
    disconnectAll();
    deleteWidgets();
}

void OperationList::init(){
    noElementsInfo.setAlignment(Qt::AlignCenter);
    noElementsInfo.setGeometry(0, CONTROL_BAR_HEIGHT, CONTROL_BAR_WIDTH, OPERATION_LIST_NO_ELEMENTS_LABEL_HEIGHT);
}

void OperationList::setWindow(){

}

void OperationList::createWidgets(){
    if(parent->getParent()->getBookPanelParent()){
        BooksLoggedInSave* bookLoggedInSave = nullptr;
            SET_PTR_NDO(bookLoggedInSave, parent->getParent()->getBookPanelParent()->getSavedBooks());
            parent->getParent()->getBookPanelParent()->readDataFromServer();
            for(uint i = 0; i < bookLoggedInSave->numbOfBooks; i++)
                addElement(new OperationListElementBookPanelUsersBooks(this, (bookLoggedInSave->books + i)), false);
            pageNumber = bookLoggedInSave->bookCurrentPage;
            nextPageAvailable = (bookLoggedInSave->nextIdBook != 0);
            noElementsInfo.setText(OPERATION_LIST_NO_ELEMENTS_BOOKS_INFO_TEXT);
            return;
    }
    switch(parent->getParent()->getParent()->getCurrentAppWindowLoggedInStat()){
    case LOGGED_IN_PANEL_BOOKS_STAT:
    {
        BooksLoggedInSave* bookLoggedInSave = nullptr;
        if(parent->getParent()->getBookPanelParent()){
            SET_PTR_NDO(bookLoggedInSave, parent->getParent()->getBookPanelParent()->getSavedBooks());
        }else{
            SET_PTR_NDO(bookLoggedInSave, parent->getParent()->getParent()->getSavedBooks());
        }
        parent->getParent()->getParent()->readDataFromServer();
        for(uint i = 0; i < bookLoggedInSave->numbOfBooks; i++)
            addElement(new OperationListElementBooks(this, (bookLoggedInSave->books + i)), false);
        pageNumber = bookLoggedInSave->bookCurrentPage;
        nextPageAvailable = (bookLoggedInSave->nextIdBook != 0);
        noElementsInfo.setText(OPERATION_LIST_NO_ELEMENTS_BOOKS_INFO_TEXT);
    }
        break;
    case LOGGED_IN_PANEL_LIBRARY_STAT:
    {
        BooksLoggedInSave* bookLoggedInSave = nullptr;
        if(parent->getParent()->getBookPanelParent()){
            SET_PTR_NDO(bookLoggedInSave, parent->getParent()->getBookPanelParent()->getSavedBooks());
        }else{
            SET_PTR_NDO(bookLoggedInSave, parent->getParent()->getParent()->getSavedBooks());
        }
        parent->getParent()->getParent()->readDataFromServer();
        bookLoggedInSave = parent->getParent()->getParent()->getSavedBooks();
        for(uint i = 0; i < bookLoggedInSave->numbOfBooks; i++)
            addElement(new OperationListElementLibrary(this, (bookLoggedInSave->books + i)), false);
        pageNumber = bookLoggedInSave->bookCurrentPage;
        nextPageAvailable = (bookLoggedInSave->nextIdBook != 0);
        noElementsInfo.setText(OPERATION_LIST_NO_ELEMENTS_BOOKS_INFO_TEXT);
    }
        break;
    case LOGGED_IN_PANEL_MY_BOOKS_STAT:
    {
        BooksLoggedInSave* bookLoggedInSave = nullptr;
        SET_PTR_NDO(bookLoggedInSave, parent->getParent()->getParent()->getSavedBooks());
        parent->getParent()->getParent()->readDataFromServer();
        for(uint i = 0; i < bookLoggedInSave->numbOfBooks; i++)
            addElement(new OperationListElementMyBooks(this, (bookLoggedInSave->books + i)), false);
        pageNumber = bookLoggedInSave->bookCurrentPage;
        nextPageAvailable = (bookLoggedInSave->nextIdBook != 0);
        noElementsInfo.setText(OPERATION_LIST_NO_ELEMENTS_MY_BOOKS_INFO_TEXT);
    }
        break;
    case LOGGED_IN_PANEL_USERS_STAT:
    {
        UsersLoggedInSave* userLoggedInSave = nullptr;
        SET_PTR_NDO(userLoggedInSave, parent->getParent()->getParent()->getSavedUsers());
        parent->getParent()->getParent()->readDataFromServer();
        for(uint i = 0; i < userLoggedInSave->numbOfUsers; i++)
            addElement(new OperationListElementUsers(this, (userLoggedInSave->users + i)), false);
        pageNumber = userLoggedInSave->userCurrentPage;
        nextPageAvailable = (userLoggedInSave->nextIdUser != 0);
        noElementsInfo.setText(OPERATION_LIST_NO_ELEMENTS_USERS_INFO_TEXT);
    }
        break;
    case LOGGED_IN_PANEL_READERS_STAT:
    {
        UsersLoggedInSave* userLoggedInSave = nullptr;
        SET_PTR_NDO(userLoggedInSave, parent->getParent()->getParent()->getSavedUsers());
        parent->getParent()->getParent()->readDataFromServer();
        for(uint i = 0; i < userLoggedInSave->numbOfUsers; i++)
            addElement(new OperationListElementReaders(this, (userLoggedInSave->users + i)), false);
        pageNumber = userLoggedInSave->userCurrentPage;
        nextPageAvailable = (userLoggedInSave->nextIdUser != 0);
        noElementsInfo.setText(OPERATION_LIST_NO_ELEMENTS_READERS_INFO_TEXT);
    }
        break;
    case LOGGED_IN_PANEL_BOOK_LOG_STAT:
    {
        BookLogsLoggedInSave* bookLogsLoggedInSave = nullptr;
        SET_PTR_NDO(bookLogsLoggedInSave, parent->getParent()->getParent()->getSavedBookLogs());
        parent->getParent()->getParent()->readDataFromServer();
        for(uint i = 0; i < bookLogsLoggedInSave->numbOfBookLogs; i++)
            addElement(new OperationListElementBookLog(this, (bookLogsLoggedInSave->bookLogs + i)), false);
        pageNumber = bookLogsLoggedInSave->bookLogCurrentPage;
        nextPageAvailable = (bookLogsLoggedInSave->nextBookLog != 0);
        noElementsInfo.setText(OPERATION_LIST_NO_ELEMENTS_READERS_INFO_TEXT);
    }
        break;
    default:
        break;
    }
}

void OperationList::createLayout(){
    upperControlBar.move(0,0);
    upperControlBar.repaint(nextPageAvailable, pageNumber);
    bottomControlBar.repaint(nextPageAvailable, pageNumber);
    if(numbOfElements > 0){
        noElementsInfo.hide();
        bottomControlBar.move(0, CONTROL_BAR_HEIGHT + elementsHeight);
    }
    else {
        noElementsInfo.show();
        bottomControlBar.move(0, CONTROL_BAR_HEIGHT + OPERATION_LIST_NO_ELEMENTS_LABEL_HEIGHT);
    }
}

void OperationList::deleteWidgets(){
    for(uint i = 0; i < numbOfElements; i++)
        SET_PTR_DO((*(elements +i)), nullptr);
    SET_PTR_DOA(elements, nullptr);
}

void OperationList::connectAll(){
    // Empty
}

void OperationList::disconnectAll(){
    // Empty
}

FilteredList* OperationList::getParent(){
    return parent;
}

void OperationList::addElement(OperationListElement *newElement, bool reload){
    if(elements){
        OperationListElement **temp = new OperationListElement*[numbOfElements + 1];
        for(uint i = 0; i < numbOfElements; i++)
            (*(temp + i)) = (*(elements + i));
        (*(temp + numbOfElements)) = newElement;
        delete []elements;
        elements = temp;
        numbOfElements++;
    }else{
        elements = new OperationListElement*[1];
        *elements = newElement;
        numbOfElements++;
    }
    reallocate(reload);
}

void OperationList::removeElement(OperationListElement *delElem, bool reload){
    if(elements){
        if(numbOfElements > 1){
            bool removed = false;
            OperationListElement** temp = new OperationListElement*[numbOfElements - 1];
            for(uint i = 0; i < numbOfElements; i++)
                if(removed){
                    (*(temp + i - 1)) = (*(elements + i));
                }else{
                    if(*(elements + i) == delElem ){
                        delete (*(elements + i));
                        (*(elements + i)) = nullptr;
                        removed = true;
                    }else{
                        (*(temp + i)) = *(elements + i);
                    }
                }
            delete []elements;
            elements = temp;
        }else{
            delete (*elements);
            delete []elements;
            elements = nullptr;
        }
        numbOfElements--;
        reallocate(reload);
    }
}

void OperationList::reallocate(bool reload){
    elementsHeight = OPERATION_ELEMENT_VERTICAL_SIDE_OFFSET;
    for(uint i = 0; i < numbOfElements; i++){
        (*(elements + i))->setGeometry(OPERATION_ELEMENT_HORIZONTAL_SIDE_OFFSET, CONTROL_BAR_HEIGHT + elementsHeight, OPERATION_ELEMENT_WIDTH, (*(elements + i))->height());
        elementsHeight += (*(elements + i))->height() + OPERATION_ELEMENT_VERTICAL_SIDE_OFFSET;
        (*(elements + i))->show();
    }
    if(numbOfElements > 0)
        resize(OPERATION_LIST_WIDTH, CONTROL_BAR_HEIGHT * 2 + elementsHeight);
    else {
        resize(OPERATION_LIST_WIDTH, CONTROL_BAR_HEIGHT * 2 + OPERATION_LIST_NO_ELEMENTS_LABEL_HEIGHT);
    }
    if(reload){
        setWindow();
        createLayout();
        parent->reload(true);        
    }
}

bool OperationList::eventMatching(QObject* obj, QEvent* ev){
    if(upperControlBar.eventMatching(obj, ev))
        return true;
    if(bottomControlBar.eventMatching(obj,ev))
        return true;
    uint i = 0;
    uint numbOfElement = numbOfElements;
    if(elements){
        for(; i < numbOfElement; i++)
            if((*(elements + i)) && (*(elements + i))->eventMatching(obj, ev))
                break;
        if(i < numbOfElement)
            return true;
        else {
            return false;
        }
    }
}

void OperationList::nextPageInit(){
    pageNumber++;
    parent->reload(false);
}

void OperationList::previousPageInit(){
    nextPageAvailable = false;
    if(pageNumber > 0)
        pageNumber--;
    parent->reload(false);
}
