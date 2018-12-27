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

// ------------------ AppWindow Class ------------------------------------


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
    QMenu toolsMenu;
    QMenu helpMenu;

    // Actions for Application Menu
    QAction loginActionAM;
    QAction registerActionAM;
    QAction quitActionAM;

    // Actions for Tools Menu:
    // - Actions for Administrator ------------
    QAction* yourAcountActionTM = nullptr;
    QAction* usersActionTM = nullptr;
    QAction* booksActionTM = nullptr;
    QAction* logoutActionTM = nullptr;

    // ---------------------------------------

    // - Actions for Librarian----------------
    // QAction* yourAcountActionTM = nullptr;
    /* !!!!!!! Used as ReadersActionTM
       QAction* usersActionTM = nullptr;*/
    // QAction* booksActionTM = nullptr;
    //QAction* logoutActionAM = nullptr;
    // --------------------------------------

    // - Actions For Readers ----------------
    // QAction* yourAcountActionTM = nullptr;
    /* !!!!!!! Used as yourBooksActionTM
       QAction* booksActionTM = nullptr;*/
    QAction* libraryActionTM = nullptr;
   // QAction* logoutActionAM = nullptr;

    // Actions for Help Menu
    QAction appInfoActionHM;
    QAction helpActionHM;

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

    // Reload Function
    void reload();

    // Create Application Menu
    inline void createApplicationMenu(){
        applicationMenu.setTitle(APPLICATION_MENU_TEXT);
        createActionForApplicationMenu();
        addMenu(&applicationMenu);
    }
    // Create Tools Menu
    inline void createToolsMenu(){
        toolsMenu.setTitle(TOOLS_MENU_TEXT);
        createActionsForToolsMenu();
        addMenu(&toolsMenu);
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

    // Create Actions For Tools Menu
    void createActionsForToolsMenu();

    // Delete Actions For Tools Menu
    void deleteActionsForToolsMenu();

    // Create Actions For Help Menu
    inline void createActionsForHelpMenu(){
        // Prepare Actions -----------------------------------
        appInfoActionHM.setText(HELP_MENU_APP_INFO_ACTION_TEXT);
        helpActionHM.setText(HELP_MENU_HELP_ACTION_TEXT);

        // Add actions to Help Menu ------------------------
        helpMenu.addAction(&appInfoActionHM);
        helpMenu.addAction(&helpActionHM);
    }

    // Connect Actions For ApplicationMenu
    inline void connectActionsForApplicationMenu(){
        connect(&loginActionAM, SIGNAL(triggered()), this, SLOT(loginActionAMTriggered()));
        connect(&registerActionAM, SIGNAL(triggered()), this, SLOT(registerActionAMTriggered()));
        connect(&quitActionAM, SIGNAL(triggered()), this, SLOT(quitActionAMTriggered()));
    }

    // Connect Actions For Tools Menu
    inline void connectActionsForToolsMenu(){
        /* _PH_ switch( parent->( get Actual Window Stat Object ) -> (Get Actual Panel Stat) ){
            case ... :
            // Add actions to Tools Menu -------------------

            break;
            default:

            break;
         }
         */
    }

    // Connect Actions For Help Menu
    inline void connectActionsForHelpMenu(){
        connect(&appInfoActionHM, SIGNAL(triggered()), this, SLOT(appInfoActionHMTriggered()));
        connect(&helpActionHM, SIGNAL(triggered()), this, SLOT(helpActionHMTriggered()));
    }

    public slots: // public slots +++

    void loginActionAMTriggered();
    void registerActionAMTriggered();
    void quitActionAMTriggered();

    void yourAcountActionTMTriggered();
    void usersActionTMTriggered();
    void booksActionTMTriggered();
    void logoutActionTMTriggered();
    void libraryActionTMTriggered();

    void appInfoActionHMTriggered();
    void helpActionHMTriggered();

};

// -----------------------------------------------------------------------

#endif // MENU_HPP
