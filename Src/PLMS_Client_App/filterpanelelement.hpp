#ifndef FILTERPANELELEMENT_HPP
#define FILTERPANELELEMENT_HPP

// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>
#include<QComboBox>
#include<QLabel>
// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class FilterPanel;
struct ClientsFileFilter;
struct BooksFileFilter;
struct BookLogsFileFilter;
// ----------------------------------------------------------------------

// ------------------ PromptElement Class ------------------------------------

class FilterPanelElement : public QFrame{
    Q_OBJECT
public:

    // Constructor
    FilterPanelElement(FilterPanel*, uint number);
    FilterPanelElement(FilterPanel*, uint number, ClientsFileFilter* clientsFileFilter);
    FilterPanelElement(FilterPanel*, uint number, BooksFileFilter* booksFileFilter);
    FilterPanelElement(FilterPanel*, uint number, BookLogsFileFilter* bookLogsFileFilter);
    // Destructor
    ~FilterPanelElement();

protected:
    // Parent
    QComboBox parametersList;
    QLabel deleteButton;
    // Dynamic Elements
    QLineEdit *lineEdit = nullptr;
    QComboBox *choiceList = nullptr;
    bool lineEditOk = false;
    // -------------------
    FilterPanel *parent = nullptr;

    uint number = 0;
    void init();
    void init(BooksFileFilter&);
    void init(ClientsFileFilter&);
    void init(BookLogsFileFilter&);
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    bool lineEditKeyPressed(QKeyEvent*);
public:
    // Get Functions
    FilterPanel* getParent();

    // -----------------
    // Set Functions
    BooksFileFilter getBookFileFilter();
    ClientsFileFilter getClientFileFilter();
    BookLogsFileFilter getBookLogFileFilter();
    // -----------------
    void reload();
    bool eventMatching(QObject*, QEvent*);
    bool isCorrect();

};

#endif // FILTERPANELELEMENT_HPP
