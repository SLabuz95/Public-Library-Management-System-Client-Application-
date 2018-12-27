#ifndef APP_HPP
#define APP_HPP

// ------------------ Macros --------------------------------------------

// Include macros

// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QApplication>
#include "appwindow.hpp"
// _PH_ #include "server.hpp"

// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
// _PH_ class User;
// ----------------------------------------------------------------------

// ------------------ App Class -----------------------------------------
class App : public QApplication{
    Q_OBJECT
    public: // public +++

    // Constructors ----
    App(int, char**);
    // -----------------

    // Destructors -----
    ~App();
    // -----------------

    private: // private ++

    // Main App Window Object
    AppWindow appWindow;

    // Server Object
    // _PH_ Server server;

    // Logged User Virtual Class PTR
    // _PH_ User* user;

    public: // public +++
    // Get Functions --------------------------------------

    AppWindow& getAppWindow();
    // _PH_ Server& getServer();
    // _PH_ User* getUser();

    // -----------------------------------------------------
    // Set Functions ---------------------------------------
    // _PH_ void setUser(User* set);
    // -----------------------------------------------------

    // Check Bool Variables State
    bool isCloseApp();

    private: // private ++

    // Is other instance of program is running?
    bool isOneInstanceOfProgram();
    // + Variable to Close App (Cant close app in QApplication constructor)
    bool closeApp = false;

    // Show app window
    void show();

    // Run All Timers
    void runTimers();
};

//-----------------------------------------------------------------------
#endif // APP_HPP
