#ifndef OPERATIONPANELFILTEREDLIST_HPP
#define OPERATIONPANELFILTEREDLIST_HPP

#include<QLabel>
#include"loggedinoperationpanel.hpp"
#include<QScrollArea>
#include"userdatapanel.hpp"

class BookPanel;
class AppWindowLoggedInPanel;
class FilteredList;
class OperationPanelFilteredList : public LoggedInOperationPanel{
    Q_OBJECT
public:
    OperationPanelFilteredList(AppWindowLoggedInPanel*);
    OperationPanelFilteredList(BookPanel*, AppWindowLoggedInPanel*);
    ~OperationPanelFilteredList();

private:
    BookPanel* bookPanelParent = nullptr;

    // Filtered List
    QScrollArea scrollArea;
    FilteredList *filteredList = nullptr;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    protected:
    // Funkcja przeładowania elementu
    bool eventMatching(QObject*, QEvent*);

public:
    void reload(bool);
    BookPanel* getBookPanelParent();
};


#endif // OPERATIONPANELFILTEREDLIST_HPP
