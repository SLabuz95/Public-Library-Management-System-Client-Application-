#ifndef FILTEREDLIST_HPP
#define FILTEREDLIST_HPP

// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>
#include"../PLMS_Server_App/filetypeenum.hpp"
// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class QLabel;
class OperationPanelFilteredList;
class FilterPanel;
class OperationList;
// ----------------------------------------------------------------------

// ------------------ PromptElement Class ------------------------------------

class FilteredList : public QFrame{
    Q_OBJECT
public:
    // Constructor
    FilteredList(OperationPanelFilteredList*, FileType);

    // Destructor
    ~FilteredList();

protected:
    // Parent
    OperationPanelFilteredList *parent = nullptr;
    FileType filterType = NUMB_OF_FILE_TYPES;

    FilterPanel *filterPanel = nullptr;
    OperationList *operationList = nullptr;

    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

public:
    // Get Functions
    OperationPanelFilteredList* getParent();
    FileType getFilterType();

    // -----------------
    // Set Functions

    // -----------------

    void reload(bool);
    bool eventFilter(QObject*, QEvent*);

};

#endif // FILTEREDLIST_HPP
