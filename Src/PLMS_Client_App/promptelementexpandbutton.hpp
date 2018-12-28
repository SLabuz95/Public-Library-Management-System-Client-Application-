#ifndef PROMPTPANELEXPANDELEMENTBUTTON_HPP
#define PROMPTPANELEXPANDELEMENTBUTTON_HPP
// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>
#include"prompttypeenum.hpp"

// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class QLabel;
class PromptElement;
// ----------------------------------------------------------------------

// ------------------ PromptElementExpandButton Class ------------------------------------

class PromptElementExpandButton : public QFrame{
public:
    // Constructors
    PromptElementExpandButton(PromptElement*);

    // Destructors
    ~PromptElementExpandButton();

private:
    // Parent
    PromptElement *parent = nullptr;

    // Elements
    QLabel *expandPixmap = nullptr;

    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

public:
    // Get Functions
    PromptElement* getParent();
    // ------------

    // Set Functions

     // -----------

    void repaint();
};


#endif // PROMPTPANELEXPANDELEMENTBUTTON_HPP
