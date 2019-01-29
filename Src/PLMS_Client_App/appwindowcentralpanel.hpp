#ifndef APPWINDOWCENTRALPANEL_HPP
#define APPWINDOWCENTRALPANEL_HPP
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
class AppWindow;
// ----------------------------------------------------------------------

// ------------------ PromptElement Class ------------------------------------

class AppWindowCentralPanel : public QFrame{

public:
    // Constructor
    AppWindowCentralPanel(AppWindow*);

    // Destructor
    virtual ~AppWindowCentralPanel();

protected:
    // Parent
    AppWindow *parent = nullptr;

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
    AppWindow* getParent();

    // -----------------
    // Set Functions

    // -----------------

    virtual void reload(){}
    virtual bool eventMatching(QObject*, QEvent*){return true;}

};
#endif // APPWINDOWCENTRALPANEL_HPP
