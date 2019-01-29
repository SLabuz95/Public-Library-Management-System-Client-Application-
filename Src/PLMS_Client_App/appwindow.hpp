#ifndef APPWINDOW_HPP
#define APPWINDOW_HPP

// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include <QWidget>
#include "appwindowstatenum.hpp"
#include "menu.hpp"
#include "toolbar.hpp"
#include "promptpanel.hpp"
#include <QStatusBar>
#include "tabbar.hpp"

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
    AppWindowStat appWindowStat[2] = {APP_WINDOW_STAT_LOGIN, APP_WINDOW_STAT_LOGIN};

    // Menu
    Menu menu;

    // ToolBar
    ToolBar toolBar;

    // Prompt Panel
    PromptPanel promptPanel;

    // Status Bar
    QStatusBar statusBar;

    // Users Bar
    TabBar userBar;

    public: // public functions +++
    // Get Functions --------------------------------------
    App* getParent();
    AppWindowStat getLastAppWindowStat();
    AppWindowStat getCurrentAppWindowStat();
    QStatusBar& getStatusBar();
    TabBar& getUserBar();
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

    // Clear Memory
    void clearMemory();

};

// -----------------------------------------------------------------------

#endif // APPWINDOW_HPP
