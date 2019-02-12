#ifndef FILTERPANEL_HPP
#define FILTERPANEL_HPP

// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"

// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>
#include<QLabel>
// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------

class AppWindow;
class FilteredList;
class FilterPanelElement;

// ----------------------------------------------------------------------

// ------------------ PromptElement Class ------------------------------------

class FilterPanel : public QFrame{
    Q_OBJECT
public:
    // Constructor
    FilterPanel(FilteredList*);

    // Destructor
    ~FilterPanel();

protected:
    // Parent
    FilteredList *parent = nullptr;

    QLabel filterTitle;

    FilterPanelElement** elements = nullptr;
    uint numbOfElements = 0;
    uint elementsHeight = 0;

    QLabel addFilterButton;
    QLabel findButton;

    bool blinkPossible = false;
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    void addFilterButtonPressed();
    void findButtonPressed();
    void blinkFilterElement(uint index);
    void lowlightFilterElement(uint index);
public:
    // Get Functions
    FilteredList* getParent();

    // -----------------
    // Set Functions

    // -----------------
    void addElement(FilterPanelElement*);
    void removeElement(FilterPanelElement*);
    void reallocate();

    void reload();
    bool eventMatching(QObject*, QEvent*);

};

#endif // FILTERPANEL_HPP
