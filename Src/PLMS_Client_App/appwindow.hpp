#ifndef APPWINDOW_HPP
#define APPWINDOW_HPP

// ------------------ Macros --------------------------------------------
/* Macros In App Class (app.hpp)
#define APP_NAME ("Aplikacja biblioteki publicznej")
#define APP_VERSION ("ver 1.0")

#define SET_PTR_DO(ptr, newPtr) {if(ptr) delete ptr; ptr = newPtr;}
#define SET_PTR_NDO(ptr) {ptr = newPtr;}
*/

#define WINDOW_STATUS_SAVE(windowStatusPTR) *(windowStatusPTR + 1) = *windowStatusPTR;

// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include <QWidget>
#include "appwindowstatenum.hpp"
#include "windowmacros.hpp"

// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class App;
// ----------------------------------------------------------------------

// ------------------ AppWindow Class ------------------------------------


class AppWindow : public QWidget{
    Q_OBJECT
    public: // public +++

    // Constructors ----
    AppWindow(App* parent);
    // -----------------

    // Destructors -----
    ~AppWindow();
    // -----------------

    private: // private elements ++

    // App Class As Parent (parent)
    App* parent = nullptr;

    // Window Stat
    AppWindowStat appWindowStat[2] = {APP_WINDOW_STAT_USER_LOGOUT, APP_WINDOW_STAT_USER_LOGOUT};

    public: // public functions +++
    // Get Functions --------------------------------------
    App* getParent();

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

    // Create Widgets Function
    void createWidgets();

    // Create Layout Function
    void createLayout();

    // Connect Widgets
    void connectWidgets();

    // Delete Widgets
    void deleteWidgets();


};

// -----------------------------------------------------------------------

#endif // APPWINDOW_HPP
