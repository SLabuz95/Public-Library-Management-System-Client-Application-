#ifndef TOOLBAR_HPP
#define TOOLBAR_HPP

// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QToolBar>
#include<QIcon>
#include<QAction>

// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class AppWindow;
// ----------------------------------------------------------------------

// ------------------ ToolBar Class ------------------------------------


class ToolBar : public QToolBar{
    Q_OBJECT
    public: // public +++

    // Constructors ----
    ToolBar(AppWindow* parent);
    // -----------------

    // Destructors -----
    ~ToolBar();
    // -----------------

    private: // private elements ++

    // AppWindow Class As Parent (parent)
    AppWindow* parent = nullptr;

    // Static elements
    QAction loginAction; // Position 1
    QAction registerAction; // Position 2
    QAction helpAction; // Position End

    // Dynamic elements
    // - Actions for Administrator ------------
    QAction* yourAccountAction = nullptr;
    QAction* usersAction = nullptr;
    QAction* booksAction = nullptr;
    QAction* logoutAction = nullptr;

    // ----------------------------------------

    // - Actions for Librarian-----------------
    // QAction* yourAccountAction = nullptr;
    /* !!!!!!! Used as ReadersAction
       QAction* usersAction = nullptr;*/
    // QAction* booksAction = nullptr;
    //QAction* logoutAction = nullptr;
    // ---------------------------------------

    // - Actions For Readers -----------------
    // QAction* yourAccountAction = nullptr;
    /* !!!!!!! Used as yourBooksAction
       QAction* booksAction = nullptr;*/
    QAction* libraryAction = nullptr;
    // QAction* logoutAction = nullptr;
    // ---------------------------------------


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

    // Create ToolBar Function
    void createToolBar();

    // Clear Memory
    void clearMemory();

    // Reload Function
    void reload();

    inline void createStaticActions(){
        // Prepare static actions
        loginAction.setIcon(TOOL_BAR_LOGIN_ACTION_ICON);
        registerAction.setIcon(TOOL_BAR_REGISTER_ACTION_ICON);
        helpAction.setIcon(TOOL_BAR_HELP_ACTION_ICON);

        // Connect static actions
        connectStaticActions();

        // Add Static Actions to ToolBar
        addAction(&loginAction);
        addAction(&registerAction);
        addAction(&helpAction);
    }


    inline void connectStaticActions(){
        connect(&loginAction, SIGNAL(triggered()), this, SLOT(loginActionTriggered()));
        connect(&registerAction, SIGNAL(triggered()), this, SLOT(registerActionTriggered()));
        connect(&helpAction, SIGNAL(triggered()), this, SLOT(helpActionTriggered()));
    }

    void createDynamicActions();
    void deleteDynamicActions();
    void disconnectDynamicActions();

    void disconnectToolBar();

    public slots: // public slots +++

    void loginActionTriggered();
    void registerActionTriggered();

    void yourAccountActionTriggered();
    void usersActionTriggered();
    void booksActionTriggered();
    void logoutActionTriggered();
    void libraryActionTriggered();

    void helpActionTriggered();


};

#endif // TOOLBAR_HPP
