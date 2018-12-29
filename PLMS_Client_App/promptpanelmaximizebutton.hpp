#ifndef PROMPTPANELMAXIMIZEBUTTON_HPP
#define PROMPTPANELMAXIMIZEBUTTON_HPP
// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>

// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class PromptPanel;
class QLabel;
// ----------------------------------------------------------------------

// ------------------ PromptPanelMaximizeButton Class ------------------------------------


class PromptPanelMaximizeButton : public QFrame{
    Q_OBJECT
public:
    // Constructor
    PromptPanelMaximizeButton(PromptPanel*);

    // Destructor
    ~PromptPanelMaximizeButton();

private:
    // Parent
    PromptPanel *parent = nullptr;

    // Elements
    QLabel *arrowPixmap = nullptr;

protected:
    // Control Functions
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();


public:
    // Get Functions ---------------------------------------
    PromptPanel* getParent();
    // -----------------------------------------------------

    // Set Functions ---------------------------------------

    // -----------------------------------------------------

    void repaint();
};

#endif // PROMPTPANELMAXIMIZEBUTTON_HPP
