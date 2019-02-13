#include"loggedincontrolpanel.hpp"
#include"appwindowloggedinpanel.hpp"
#include<QLabel>
#include"../PLMS_Server_App/user.hpp"
#include"loggedincontrolpanellibrarianfunc.hpp"
#include"loggedincontrolpanelreaderfunc.hpp"
#include"loggedinpaneladminfunc.hpp"
#include"appwindow.hpp"
#include"app.hpp"
#include<QEvent>

LoggedInControlPanel::LoggedInControlPanel(AppWindowLoggedInPanel* parent)
    : QFrame(parent), parent(parent)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

LoggedInControlPanel::~LoggedInControlPanel(){
    disconnectAll();
    deleteWidgets();
}

void LoggedInControlPanel::init(){

}

void LoggedInControlPanel::setWindow(){
    resize(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_WIDTH, APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_HEIGHT);
}

void LoggedInControlPanel::createWidgets(){
    if(elements)
        SET_PTR_DOA(elements, nullptr);
    switch(parent->getUser()->getUserPermissions()){
    case USER_PERMISSIONS_ADMIN:
        elements = new QLabel[NUMB_OF_LOGGED_IN_PANEL_ADMIN_FUNC];
        break;
    case USER_PERMISSIONS_READER:
        elements = new QLabel[NUMB_OF_LOGGED_IN_CONTROL_PANEL_READER_FUNC];
        break;
    case USER_PERMISSIONS_LIBRARIAN:
        elements = new QLabel[NUMB_OF_LOGGED_IN_PANEL_LIBRARIAN_FUNC];
        break;
    default:
        break;
    }
}

void LoggedInControlPanel::createLayout(){
    switch(parent->getUser()->getUserPermissions()){
    case USER_PERMISSIONS_ADMIN:
        for(uint i = 0; i < NUMB_OF_LOGGED_IN_PANEL_ADMIN_FUNC; i++)
        {
            (*(elements + i)).setAlignment(Qt::AlignCenter);
            (*(elements + i)).setGeometry(0,static_cast<int>(i * APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ELEMENTS_HEIGHT),APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ELEMENTS_WIDTH, static_cast<int>(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ELEMENTS_HEIGHT));
            (*(elements + i)).setStyleSheet("background: rgba(240,240,240,0.5); border: 1px solid rgba(250,250,250, 0.5);");
            switch(static_cast<LoggedInPanelAdminFunc>(i)){
            case LOGGED_IN_PANEL_ADMIN_YOUR_ACCOUNT:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_YOUR_ACCOUNT_TEXT);
                break;
            case LOGGED_IN_PANEL_ADMIN_USERS:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_USERS_TEXT);
                break;
            case LOGGED_IN_PANEL_ADMIN_BOOKS:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_BOOKS_TEXT);
                break;
            case LOGGED_IN_PANEL_ADMIN_ADD_BOOK:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ADD_BOOK_TEXT);
                break;
            case LOGGED_IN_PANEL_ADMIN_ADD_USER:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ADD_USER_TEXT);
                break;
            case LOGGED_IN_PANEL_ADMIN_LOG_LIST:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_BOOK_LOG_TEXT);
                break;
            case LOGGED_IN_PANEL_ADMIN_LOGOUT:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_LOGOUT_TEXT);
                break;
            default:
                break;
            }
            if(activeIndex == i){
                (*(elements + i)).setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_HIGHLIGHT);
            }else{
                (*(elements + i)).setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_LOWLIGHT);
            }
            (*(elements + i)).setParent(this);
            (*(elements + i)).show();
        }
        break;
    case USER_PERMISSIONS_READER:
        for(uint i = 0; i < NUMB_OF_LOGGED_IN_CONTROL_PANEL_READER_FUNC; i++)
        {
            (*(elements + i)).setAlignment(Qt::AlignCenter);
            (*(elements + i)).setGeometry(0,static_cast<int>(i * APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ELEMENTS_HEIGHT),APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ELEMENTS_WIDTH, static_cast<int>(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ELEMENTS_HEIGHT));
            (*(elements + i)).setStyleSheet("background: rgba(240,240,240,0.5); border: 1px solid rgba(250,250,250, 0.5);");
            switch(static_cast<LoggedInControlPanelReaderFunc>(i)){
            case LOGGED_IN_PANEL_READER_YOUR_ACCOUNT:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_YOUR_ACCOUNT_TEXT);
                break;
            case LOGGED_IN_PANEL_READER_YOUR_BOOKS:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_YOUR_BOOKS_TEXT);
                break;
            case LOGGED_IN_PANEL_READER_LIBRARY:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_LIBRARY_TEXT);
                break;
            case LOGGED_IN_PANEL_READER_LOGOUT:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_LOGOUT_TEXT);
                break;
            default:
                break;
            }
            if(activeIndex == i){
                (*(elements + i)).setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_HIGHLIGHT);
            }else{
                (*(elements + i)).setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_LOWLIGHT);
            }
            (*(elements + i)).setParent(this);
            (*(elements + i)).show();
        }

        break;
    case USER_PERMISSIONS_LIBRARIAN:
        for(uint i = 0; i < NUMB_OF_LOGGED_IN_PANEL_LIBRARIAN_FUNC; i++)
        {
            (*(elements + i)).setAlignment(Qt::AlignCenter);
            (*(elements + i)).setGeometry(0,static_cast<int>(i * APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ELEMENTS_HEIGHT),APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ELEMENTS_WIDTH, static_cast<int>(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ELEMENTS_HEIGHT));
            (*(elements + i)).setStyleSheet("background: rgba(240,240,240,0.5); border: 1px solid rgba(250,250,250, 0.5);");
            switch(static_cast<LoggedInControlPanelLibrarianFunc>(i)){
            case LOGGED_IN_PANEL_LIBRARIAN_YOUR_ACCOUNT:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_YOUR_ACCOUNT_TEXT);
                break;
            case LOGGED_IN_PANEL_LIBRARIAN_READERS:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_READERS_TEXT);
                break;
            case LOGGED_IN_PANEL_LIBRARIAN_BOOKS:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_BOOKS_TEXT);
                break;
            case LOGGED_IN_PANEL_LIBRARIAN_ADD_BOOK:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ADD_BOOK_TEXT);
                break;
            case LOGGED_IN_PANEL_LIBRARIAN_ADD_USER:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ADD_USER_TEXT);
                break;
            case LOGGED_IN_PANEL_LIBRARIAN_LOG_LIST:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_BOOK_LOG_TEXT);
                break;
            case LOGGED_IN_PANEL_LIBRARIAN_LOGOUT:
                (*(elements + i)).setText(APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_LOGOUT_TEXT);
                break;
            default:
                break;
            }
            if(activeIndex == i){
                (*(elements + i)).setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_HIGHLIGHT);
            }else{
                (*(elements + i)).setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_LOWLIGHT);
            }
            (*(elements + i)).setParent(this);
            (*(elements + i)).show();
        }
        break;
    default:
        break;
    }
}

void LoggedInControlPanel::deleteWidgets(){
    if(elements)
        SET_PTR_DOA(elements, nullptr);
}

void LoggedInControlPanel::connectAll(){
    switch(parent->getUser()->getUserPermissions()){
    case USER_PERMISSIONS_ADMIN:
        for(uint i = 0; i < NUMB_OF_LOGGED_IN_PANEL_ADMIN_FUNC; i++)
            (*(elements + i)).installEventFilter(parent);
        break;
    case USER_PERMISSIONS_READER:
        for(uint i = 0; i < NUMB_OF_LOGGED_IN_CONTROL_PANEL_READER_FUNC; i++)
            (*(elements + i)).installEventFilter(parent);
        break;
    case USER_PERMISSIONS_LIBRARIAN:
        for(uint i = 0; i < NUMB_OF_LOGGED_IN_PANEL_LIBRARIAN_FUNC; i++)
            (*(elements + i)).installEventFilter(parent);
        break;
    default:
        break;
    }
}

void LoggedInControlPanel::disconnectAll(){
    // Empty
}

bool LoggedInControlPanel::eventMatching(QObject *obj, QEvent *ev){
    switch (ev->type()) {
    case QEvent::MouseButtonRelease:
    {
        switch(parent->getUser()->getUserPermissions()){
        case USER_PERMISSIONS_ADMIN:
            for(uint i = 0; i < NUMB_OF_LOGGED_IN_PANEL_ADMIN_FUNC; i++)
                if(obj == (elements + i)){
                    switch (static_cast<LoggedInPanelAdminFunc>(i)) {
                        case LOGGED_IN_PANEL_ADMIN_LOGOUT:
                        {
                        User** user = new User*[1];
                        *user = parent->getUser();
                        parent->getParent()->getParent()->logoutUser(user, 1);
                        SET_PTR_DOA(user, nullptr);
                        }
                        return true;
                    case LOGGED_IN_PANEL_ADMIN_BOOKS:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_BOOKS_STAT, true);
                        break;
                    case LOGGED_IN_PANEL_ADMIN_USERS:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_USERS_STAT, true);
                        break;
                    case LOGGED_IN_PANEL_ADMIN_YOUR_ACCOUNT:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT, true);
                        break;
                    case LOGGED_IN_PANEL_ADMIN_ADD_BOOK:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_ADD_BOOK_STAT, true);
                        break;
                    case LOGGED_IN_PANEL_ADMIN_ADD_USER:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_ADD_USER_STAT, true);
                        break;
                    case LOGGED_IN_PANEL_ADMIN_LOG_LIST:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_BOOK_LOG_STAT, true);
                        break;
                        default:                            
                        return false;
                    }
                    return true;
                }
            break;
        case USER_PERMISSIONS_READER:
            for(uint i = 0; i < NUMB_OF_LOGGED_IN_CONTROL_PANEL_READER_FUNC; i++)
                if(obj == (elements + i)){
                    switch (static_cast<LoggedInControlPanelReaderFunc>(i)) {
                        case LOGGED_IN_PANEL_READER_LOGOUT:
                            {
                            User** user = new User*[1];
                            *user = parent->getUser();
                            parent->getParent()->getParent()->logoutUser(user, 1);
                            SET_PTR_DOA(user, nullptr);
                            }
                        return true;
                    case LOGGED_IN_PANEL_READER_LIBRARY:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_LIBRARY_STAT, true);
                        break;
                    case LOGGED_IN_PANEL_READER_YOUR_BOOKS:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_MY_BOOKS_STAT, true);
                        break;
                    case LOGGED_IN_PANEL_READER_YOUR_ACCOUNT:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT, true);
                        break;
                        default:
                        return false;
                    }
                    return true;
                }
            break;
        case USER_PERMISSIONS_LIBRARIAN:
            for(uint i = 0; i < NUMB_OF_LOGGED_IN_PANEL_LIBRARIAN_FUNC; i++)
                if(obj == (elements + i)){
                    switch (static_cast<LoggedInControlPanelLibrarianFunc>(i)) {
                        case LOGGED_IN_PANEL_LIBRARIAN_LOGOUT:
                            {
                            User** user = new User*[1];
                            *user = parent->getUser();
                            parent->getParent()->getParent()->logoutUser(user, 1);
                            SET_PTR_DOA(user, nullptr);
                            }
                        return true;
                    case LOGGED_IN_PANEL_LIBRARIAN_BOOKS:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_BOOKS_STAT, true);
                        break;
                    case LOGGED_IN_PANEL_LIBRARIAN_READERS:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_READERS_STAT, true);
                        break;
                    case LOGGED_IN_PANEL_LIBRARIAN_YOUR_ACCOUNT:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT, true);
                        break;
                    case LOGGED_IN_PANEL_LIBRARIAN_ADD_BOOK:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_ADD_BOOK_STAT, true);
                        break;
                    case LOGGED_IN_PANEL_LIBRARIAN_ADD_USER:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_ADD_USER_STAT, true);
                        break;
                    case LOGGED_IN_PANEL_LIBRARIAN_LOG_LIST:
                        parent->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_BOOK_LOG_STAT, true);
                        break;
                        default:
                        return false;
                    }
                    return true;
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
    return false;
}

uint LoggedInControlPanel::getActiveIndex(){
    return activeIndex;
}

void LoggedInControlPanel::setActiveIndex(uint index){
    if(activeIndex != index){
        activeIndex = index;
        reload();
    }
}

void LoggedInControlPanel::reload(){
    createLayout();
}
