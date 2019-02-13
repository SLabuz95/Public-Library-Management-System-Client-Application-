#ifndef OPERATIONLIST_HPP
#define OPERATIONLIST_HPP

// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>
#include"controlbar.hpp"
// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class QLabel;
class AppWindow;
class FilteredList;
class OperationListElement;
// ----------------------------------------------------------------------

// ------------------ PromptElement Class ------------------------------------

class OperationList : public QFrame{
    Q_OBJECT
public:
    // Constructor
    OperationList(FilteredList*);

    // Destructor
    ~OperationList();

protected:
    // Parent
    FilteredList *parent = nullptr;

    OperationListElement** elements = nullptr;
    uint numbOfElements = 0;

    uint pageNumber = 0;
    ControlBar upperControlBar;
    ControlBar bottomControlBar;
    QLabel noElementsInfo;

    uint elementsHeight = 0;

    bool nextPageAvailable = false;

    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();


public:
    // Get Functions
    FilteredList* getParent();

    // -----------------
    // Set Functions

    // -----------------
    void addElement(OperationListElement*, bool);
    void removeElement(OperationListElement*, bool);

    void reload();
    bool eventMatching(QObject*, QEvent*);

    void reallocate(bool);

    void nextPageInit();
    void previousPageInit();
};


#endif // OPERATIONLIST_HPP
