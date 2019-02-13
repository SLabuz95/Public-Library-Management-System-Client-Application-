#ifndef APPWINDOWLOGGEDINPANEL_HPP
#define APPWINDOWLOGGEDINPANEL_HPP
#include"appwindowcentralpanel.hpp"
#include"appwindowloggedinstatus.hpp"
#include"loggedincontrolpanel.hpp"
#include"loggedinoperationpanel.hpp"
#include"../PLMS_Server_App/readfilerules.hpp"

struct BooksLoggedInSave{
    // List of Books
    Book *books = nullptr;
    uint numbOfBooks = 0;
    unsigned long long nextIdBook= 0;
    uint bookCurrentPage = 0;   //Decremented
};

struct UsersLoggedInSave{
    // List of Users
        User *users = nullptr;
        uint numbOfUsers = 0;
        unsigned long long nextIdUser = 0;
        uint userCurrentPage = 0;   // Decremented
};

struct BookLogsLoggedInSave{
    // List of Book Logs
        BookLog *bookLogs = nullptr;
        uint numbOfBookLogs = 0;
        bool nextBookLog = false;
        uint bookLogCurrentPage = 0;   // Decremented
};

struct UserFiltersLoggedInSave{
    ClientsFileFilter *userFilters = nullptr;
    uint numbOfFilters = 0;
};

struct BookFiltersLoggedInSave{
    BooksFileFilter *bookFilters = nullptr;
    uint numbOfFilters = 0;
};

struct BookLogFiltersLoggedInSave{
    BookLogsFileFilter *bookLogFilters = nullptr;
    uint numbOfFilters = 0;
};

class Book;
class User;
class BookLog;
class AppWindow;
class User;
class AppWindowLoggedInPanel : public AppWindowCentralPanel{
    Q_OBJECT
public:
    AppWindowLoggedInPanel(AppWindow*, User*);
    ~AppWindowLoggedInPanel();

private:
    AppWindowLoggedInStatus loggedInStatus[2] = {LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT, LOGGED_IN_PANEL_YOUR_ACCOUNT_STAT};
    bool loggedInStatusChanged = false;
    User* user = nullptr;
    User* userDataPtr = nullptr;
    Book* bookDataPtr = nullptr;
    LoggedInControlPanel controlPanel;
    LoggedInOperationPanel* operationPanel = nullptr;

    BooksLoggedInSave savedBooks;
    UsersLoggedInSave savedUsers;
    UserFiltersLoggedInSave savedUserFilters;
    BookFiltersLoggedInSave savedBookFilters;
    BookLogsLoggedInSave savedBookLogs;
    BookLogFiltersLoggedInSave savedBookLogFilters;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    bool eventMatching(QObject*, QEvent*);

public:
    // Funkcja przeładowania elementu
    void reload();

    AppWindowLoggedInStatus getLastAppWindowLoggedInStat();
    AppWindowLoggedInStatus getCurrentAppWindowLoggedInStat();
    AppWindowLoggedInStatus getLoggedInStatus();
    BooksLoggedInSave* getSavedBooks();
    UsersLoggedInSave* getSavedUsers();
    BookLogsLoggedInSave* getSavedBookLogs();
    UserFiltersLoggedInSave* getSavedUserFilters();
    BookFiltersLoggedInSave* getSavedBookFilters();
    BookLogFiltersLoggedInSave* getSavedBookLogFilters();
    User* getUser();
    void setAppWindowLoggedInStatus(AppWindowLoggedInStatus awlis, bool doReload);
    void setAppWindowLoggedInStatus(AppWindowLoggedInStatus awlis, User* userDataPtrF);
    void setAppWindowLoggedInStatus(AppWindowLoggedInStatus awlis, Book* bookDataPtrF);
    User* getUserDataPtr();
    Book* getBookDataPtr();

    bool isLoggedInStatusChanged();
    bool eventFilter(QObject* obj, QEvent* ev);
    void readDataFromServer();
};

#endif // APPWINDOWLOGGEDINPANEL_HPP
