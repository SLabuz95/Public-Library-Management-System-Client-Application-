#ifndef PROMPTELEMENT_HPP
#define PROMPTELEMENT_HPP
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
class PromptElementExpandButton;
class PromptList;
// ----------------------------------------------------------------------

// ------------------ PromptElement Class ------------------------------------

class PromptElement : public QFrame{

public:
    // Constructor
    PromptElement(PromptList*, PromptType);

    // Destructor
    virtual ~PromptElement();

protected:
    // Parent
    PromptList *parent = nullptr;

    // Type of prompt
    PromptType type = PROMPT_TYPE_DEFAULT;

    // Is element expanded?
    bool expanded = false;

    // Virtual Element's widgets
    PromptElementExpandButton *expandButton = nullptr;
    QLabel *closeButton = nullptr;
    QLabel *errorTypeLabel = nullptr;
    QLabel *generalInfoLabel = nullptr;

    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    virtual void expand(){}
    virtual void minimize(){}

public:
    // Get Functions
    PromptElementExpandButton* getExpandButton();
    QLabel* getCloseButton();
    QLabel* getGeneralInfoLabel();
    uint textHeight = 0;
    PromptList* getParent();
    PromptType getType();
    bool isExpanded();

    // Set Functions

    // -----------------

    virtual void reload(){}
    virtual void generateText(){}
    virtual bool eventMatching(QObject*, QEvent*){return true;}

    virtual void closeButtonReleased(){}
    virtual void expandButtonReleased(){}
};

#endif // PROMPTELEMENT_HPP
