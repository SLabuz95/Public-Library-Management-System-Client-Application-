#include"operationpanelfilteredlist.hpp"
#include"appwindowloggedinpanel.hpp"
#include"bookpanel.hpp"
#include"app.hpp"
#include<QScrollBar>
#include"filteredlist.hpp"
#include"../PLMS_Server_App/user.hpp"

OperationPanelFilteredList::OperationPanelFilteredList(AppWindowLoggedInPanel* parent)
    : LoggedInOperationPanel(parent),
      scrollArea(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationPanelFilteredList::OperationPanelFilteredList(BookPanel* parent, AppWindowLoggedInPanel* appWindowParent)
    : LoggedInOperationPanel(parent, appWindowParent), bookPanelParent(parent),
      scrollArea(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationPanelFilteredList::~OperationPanelFilteredList(){
    disconnectAll();
    deleteWidgets();
}

void OperationPanelFilteredList::init(){
    // Empty
}

void OperationPanelFilteredList::setWindow(){
    // Empty
}

void OperationPanelFilteredList::createWidgets(){
    // Filtered List
    FileType fileType;
    if(bookPanelParent){
        fileType = FILE_TYPE_BOOKS_FILE;
    }else{
        switch(parent->getCurrentAppWindowLoggedInStat()){
        case LOGGED_IN_PANEL_BOOKS_STAT:
        case LOGGED_IN_PANEL_LIBRARY_STAT:
        case LOGGED_IN_PANEL_MY_BOOKS_STAT:
            fileType = FILE_TYPE_BOOKS_FILE;
            break;
        case LOGGED_IN_PANEL_USERS_STAT:
        case LOGGED_IN_PANEL_READERS_STAT:
            fileType = FILE_TYPE_CLIENTS_FILE;
            break;
        case LOGGED_IN_PANEL_BOOK_LOG_STAT:
            fileType = FILE_TYPE_BOOK_LOG_FILE;
            break;
        default:
            break;
        }
    }
    SET_PTR_DO(filteredList, new FilteredList(this, fileType));
}

void OperationPanelFilteredList::createLayout(){
    // Filtered List
    filteredList->move(OPERATION_PANEL_FILTERED_LIST_PANEL_X,OPERATION_PANEL_FILTERED_LIST_PANEL_Y);

    // Scroll Area
    scrollArea.setStyleSheet("QScrollArea{background-color: transparent;}");
    scrollArea.verticalScrollBar()->setStyleSheet("QScrollBar::vertical{background: transparent; width: 5px;} QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical, QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical, QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{border: none; background: none; color: none;} QScrollBar::handle:vertical{background-color: white; border: 1px solid black;}");
    scrollArea.setFrameShape(QFrame::NoFrame);
    scrollArea.setWidget(filteredList);
    scrollArea.setGeometry(OPERATION_PANEL_FILTERED_LIST_PANEL_X,OPERATION_PANEL_FILTERED_LIST_PANEL_Y,OPERATION_PANEL_FILTERED_LIST_PANEL_WIDTH,OPERATION_PANEL_FILTERED_LIST_PANEL_HEIGHT);
    scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea.show();

}

void OperationPanelFilteredList::deleteWidgets(){
    SET_PTR_DO(filteredList, nullptr);
}

void OperationPanelFilteredList::connectAll(){

}

void OperationPanelFilteredList::disconnectAll(){
    // Empty
}

void OperationPanelFilteredList::reload(bool reloadDynamic)
{
    if(!reloadDynamic){
        createWidgets();
        createLayout();
    }else{
    createLayout();
    }
}

bool OperationPanelFilteredList::eventMatching(QObject* obj, QEvent* ev){
    switch (ev->type()) {
    case QEvent::MouseButtonRelease:
    {

    }
        break;
    case QEvent::KeyPress:
    {

    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, ev);
}

BookPanel* OperationPanelFilteredList::getBookPanelParent(){
    return bookPanelParent;
}
