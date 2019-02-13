#ifndef MENU_HPP
#define MENU_HPP

// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QMenuBar>
#include<QMenu>
#include<QAction>

// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class AppWindow;
// ----------------------------------------------------------------------

// ------------------ Menu Class ------------------------------------

class Menu : public QMenuBar{
    Q_OBJECT
    public: // public +++

    // Constructors ----
    Menu(AppWindow* parent);
    // -----------------

    // Destructors -----
    ~Menu();
    // -----------------

    private: // private elements ++

    // AppWindow Class As Parent (parent)
    AppWindow* parent = nullptr;

    // Menus
    QMenu applicationMenu;
    QMenu helpMenu;

    // Actions for Application Menu
    QAction loginActionAM;
    QAction registerActionAM;
    QAction quitActionAM;

    // Actions for Help Menu
    QAction appInfoActionHM;
    QAction authorsActionHM;

    public: // public functions +++
    // Get Functions --------------------------------------
    AppWindow* getParent();

    // -----------------------------------------------------
    // Set Functions ---------------------------------------

    // -----------------------------------------------------

    // Run All Timers
    void runTimers();

    private: // private functions ++

    // Init Function
    void init();

    // Set Window Function
    void setWindow();

    // Create Menu Function
    void createMenu();

    // Connect Menu
    void connectMenu();

    // Clear Memory
    void clearMemory();


    // Create Application Menu
    inline void createApplicationMenu(){
        applicationMenu.setTitle(APPLICATION_MENU_TEXT);
        createActionForApplicationMenu();
        addMenu(&applicationMenu);
    }
     // Create Help Menu
    inline void createHelpMenu(){
        helpMenu.setTitle(HELP_MENU_TEXT);
        createActionsForHelpMenu();
        addMenu(&helpMenu);
    }

    // Create Actions For Application Menu
    inline void createActionForApplicationMenu(){
        // Prepare Actions -----------------------------------
        // Prepare loginActionAM
        loginActionAM.setText(APPLICATION_MENU_LOGIN_ACTION_TEXT);
        // Prepare regiserActionAM
        registerActionAM.setText(APPLICATION_MENU_REGISTER_ACTION_TEXT);
        // Prepare quitActionAM
        quitActionAM.setText(APPLICATION_MENU_QUIT_ACTION_TEXT);

        // Add actions to Application Menu ------------------------
        applicationMenu.addAction(&loginActionAM);
        applicationMenu.addAction(&registerActionAM);
        applicationMenu.addAction(&quitActionAM);
    }

   // Create Actions For Help Menu
    inline void createActionsForHelpMenu(){
        // Prepare Actions -----------------------------------
        appInfoActionHM.setText(HELP_MENU_APP_INFO_ACTION_TEXT);
        authorsActionHM.setText(HELP_MENU_AUTHORS_ACTION_TEXT);

        // Add actions to Help Menu ------------------------
        helpMenu.addAction(&appInfoActionHM);
        helpMenu.addAction(&authorsActionHM);
    }

    // Connect Actions For ApplicationMenu
    inline void connectActionsForApplicationMenu(){
        connect(&loginActionAM, SIGNAL(triggered()), this, SLOT(loginActionAMTriggered()));
        connect(&registerActionAM, SIGNAL(triggered()), this, SLOT(registerActionAMTriggered()));
        connect(&quitActionAM, SIGNAL(triggered()), this, SLOT(quitActionAMTriggered()));
    }

    // Connect Actions For Help Menu
    inline void connectActionsForHelpMenu(){
        connect(&appInfoActionHM, SIGNAL(triggered()), this, SLOT(appInfoActionHMTriggered()));
        connect(&authorsActionHM, SIGNAL(triggered()), this, SLOT(authorsActionHMTriggered()));
 }

    void disconnectActions();

    public slots: // public slots +++

    void loginActionAMTriggered();
    void registerActionAMTriggered();
    void quitActionAMTriggered();

    void appInfoActionHMTriggered();
    void authorsActionHMTriggered();

};

// -----------------------------------------------------------------------

#endif // MENU_HPP
