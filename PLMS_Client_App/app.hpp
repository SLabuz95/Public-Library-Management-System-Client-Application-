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
class User;
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
    User** users =  nullptr;
    // + Number of logged users
    uint numbOfUsers = 0;
    // + Active Logged User
    User* activeUser = nullptr;

    public: // public +++
    // Get Functions --------------------------------------

    AppWindow& getAppWindow();
    // _PH_ Server& getServer();
    User** getUsers();
    uint getNumbOfUsers();
    User* getActiveUser();
    // -----------------------------------------------------
    // Set Functions ---------------------------------------
    void setActiveUser(User*);
    // -----------------------------------------------------

    // Check Bool Variables State
    bool isCloseApp();

    // Add User
    void addUser();
    // _PH_ TEST
    void addUser(QString);
    // Remove User
    void removeUser(User*);


    private: // private ++

    // Is other instance of program is running?
    bool isOneInstanceOfProgram();
    // + Variable to Close App (Cant close app in QApplication constructor)
    bool closeApp = false;

    // Show app window
    void show();

    // Run All Timers
    void runTimers();

    void clearMemory();

};

//-----------------------------------------------------------------------
#endif // APP_HPP
