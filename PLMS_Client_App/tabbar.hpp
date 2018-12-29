#ifndef TABBAR_HPP
#define TABBAR_HPP
// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"

// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>
// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class AppWindow;
class QLabel;
class UserTab;
// ----------------------------------------------------------------------

// ------------------ TabBar Class ------------------------------------

class TabBar : public QFrame{
    Q_OBJECT
public:
    // Constructor
    TabBar(AppWindow*);

    // Destructor
    ~TabBar();

 private:
    // Parent
    AppWindow *parent = nullptr;

    // Elements
    UserTab **userTabs = nullptr;
    QLabel *leftArrowButton = nullptr;
    QLabel *rightArrowButton = nullptr;

    // Control Variables
    uint numbOfElements = 0;
    uint leftPos = 0;
    ushort actualNumberOfUserTabs = 0;
    short move = 0; // To inform about tab shift

public:
    uint offset = 0;
private:
    // Control Functions
    void init(bool);
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();
    ushort calculateActualNumberOfUserTabs();
public:
    // Reload of elements
    void reload();

    // Get Functions
    AppWindow* getParent();
    UserTab** getUserTabs();
    ushort getActualNumberOfUserTabs();
    QLabel* getLeftArrowButton();
    QLabel* getRightArrowButton();

    // EventFilter
    bool eventFilter(QObject* obj, QEvent* ev);

    // Event Functions
    void leftArrowButtonReleased();
    void rightArrowButtonReleased();
 };

#endif // TABBAR_HPP
