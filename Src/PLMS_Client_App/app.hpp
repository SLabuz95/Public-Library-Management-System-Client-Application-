#ifndef APP_HPP
#define APP_HPP

// ------------------ Macros --------------------------------------------
#define MAIN_APP_TIMER_INTERVAL (10)
#define SEND_ACTIVITY_PTR (989)
// Include macros

// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QApplication>
#include "appwindow.hpp"
#include "server.hpp"
#include<QTimer>

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

    // Logged User Virtual Class PTR
    User** users =  nullptr;
    // + Active Logged User
    User* activeUser = nullptr;

    // + Number of logged users
    uint numbOfUsers = 0;

    // Main App Window Object
    AppWindow appWindow;

    // Server Object
    Server server;

    // Main App Timer
    QTimer mainAppTimer;

    uint sendActivityPtr = 0;

    public: // public +++
    // Get Functions --------------------------------------

    AppWindow& getAppWindow();
    Server& getServer();
    User** getUsers();
    uint getNumbOfUsers();
    User* getActiveUser();
    // -----------------------------------------------------
    // Set Functions ---------------------------------------
    void setActiveUser(User*);
    // -----------------------------------------------------

    // Event Filter
    bool eventFilter(QObject* obj, QEvent* ev);

    // Check Bool Variables State
    bool isCloseApp();

    void addUser(User*);
    // Remove User
    void removeUser(User*);

    void logoutUser(User**, uint);
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

    static unsigned long long strLenForFile(QString&);

    // Timer Function
    void timerFunction();

    void sendActivityUpdate();
};

//-----------------------------------------------------------------------
#endif // APP_HPP
