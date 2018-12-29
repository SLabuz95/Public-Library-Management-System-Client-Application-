#ifndef USERTAB_HPP
#define USERTAB_HPP
// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"

// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>
// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class QLabel;
class User;
class TabBar;
// ----------------------------------------------------------------------

// ------------------ UserTab Class ------------------------------------
class UserTab : public QFrame{
    Q_OBJECT
public:
    // Constructor
    UserTab(TabBar*, User*);

    // Destructor
    ~UserTab();

private:
    // Parent
    TabBar *parent = nullptr;

    // Elements
    QLabel *userNameLabel = nullptr;
    QLabel *closeLabel = nullptr;

    // Address of user
    User *user = nullptr;

    // Control Function
    void init();
    void createWidgets();
    void deleteWidgets();
    void createLayout();
    void connectAll();
    void disconnectAll();

public:
    // Get Functions
    QLabel* getUserNameLabel();
    User* getUser();
    QLabel* getCloseLabel();
};

#endif // USERTAB_HPP
