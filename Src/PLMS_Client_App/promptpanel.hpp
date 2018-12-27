#ifndef PROMPTPANEL_HPP
#define PROMPTPANEL_HPP
// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>
#include"prompttypeenum.hpp"
#include"promptpanelstatusenum.hpp"
// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class QScrollArea;
class AppWindow;
class PromptElement;
class PromptPanelMaximizeButton;
class PromptPanelMinimizeButton;
class PromptList;
// ----------------------------------------------------------------------

// ------------------ PromptPanel Class ------------------------------------

class PromptPanel : public QFrame{
public:
    // Constructors
    PromptPanel(AppWindow*);

    // Destructors
    ~PromptPanel();

private:
    // Control Functions
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    // Parent
    AppWindow *parent = nullptr;
    // Panel elements
    PromptPanelMaximizeButton *maximizeButton = nullptr;
    PromptPanelMinimizeButton *minimizeButton = nullptr;
    QScrollArea *promptSA = nullptr;
    PromptList *promptList = nullptr;
    // Actual Panel Stat
    PromptPanelStatus *status = nullptr;

public:
    // Get Functions
    PromptPanelMaximizeButton* getMaximizeButton();
    PromptPanelMinimizeButton* getMinimizeButton();
    PromptList* getPromptList();
    PromptPanelStatus* getStatus();
    // -----------------------------------------
    // Set Functions ---------------------------
    void setStatus(PromptPanelStatus);
    // -----------------------------------------

    void reload(bool);

    // Add prompt with only string arguments (Standard Error, Standard Warning)
    void addPrompt(PromptType, QString);
    // Remove All Prompts with PromptType Type
    void removePrompt(PromptType);
    // Show number of errors and warnings
    void writeNumbOfPrompts();
};

#endif // PROMPTPANEL_HPP
