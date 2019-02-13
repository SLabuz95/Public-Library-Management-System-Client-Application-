#ifndef LOGGEDINOPERATIONPANEL_HPP
#define LOGGEDINOPERATIONPANEL_HPP
// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>

// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class AppWindowLoggedInPanel;
class Book;
class User;
class BookLog;
class BookPanel;
// ----------------------------------------------------------------------

// ------------------ PromptElement Class ------------------------------------

class LoggedInOperationPanel : public QFrame{
    Q_OBJECT
public:
    // Constructor
    LoggedInOperationPanel(AppWindowLoggedInPanel*);
    LoggedInOperationPanel(BookPanel*, AppWindowLoggedInPanel*);

    // Destructor
    virtual ~LoggedInOperationPanel();

protected:
    // Parent
    AppWindowLoggedInPanel *parent = nullptr;

    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    virtual void expand(){}
    virtual void minimize(){}

public:
    // Get Functions
    AppWindowLoggedInPanel* getParent();

    // -----------------
    // Set Functions

    // -----------------
    bool eventFilter(QObject* obj, QEvent* ev);

    virtual void reload(){}
    virtual bool eventMatching(QObject*, QEvent*){return true;}

};

#endif // LOGGEDINOPERATIONPANEL_HPP
