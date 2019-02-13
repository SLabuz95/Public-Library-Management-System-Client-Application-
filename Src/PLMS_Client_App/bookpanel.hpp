#ifndef BOOKPANEL_HPP
#define BOOKPANEL_HPP
#include"appwindowloggedinpanel.hpp"
#include"operationpanelfilteredlist.hpp"
#include<QFrame>
#include<QLabel>

class Dialog;
class User;
class BookPanel : public QFrame{
    Q_OBJECT
public:
    BookPanel(Dialog* parent, User* user);
    ~BookPanel();

private:
    Dialog* parent = nullptr;
    User* user = nullptr;

    bool usersBooksStat = true;
    BooksLoggedInSave savedBooks;
    BookFiltersLoggedInSave savedBookFilters;

    OperationPanelFilteredList* filteredList = nullptr;

    QLabel usersBooksButton;
    QLabel checkOutButton;
    QLabel closeButton;

    void create();
    void usersBooksButtonPressed();
    void checkOutButtonPressed();
    void closeButtonPressed();

public:
    void reload(bool);
    bool eventMatching(QObject* obj, QEvent* ev);
    BookFiltersLoggedInSave* getSavedBookFilters();
    BooksLoggedInSave* getSavedBooks();
    void readDataFromServer();
    Dialog* getParent();
    bool isUsersBooksStat();
    User* getUser();
};

#endif // BOOKPANEL_HPP
