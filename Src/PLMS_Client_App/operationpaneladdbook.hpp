#ifndef OPERATIONPANELADDBOOK_HPP
#define OPERATIONPANELADDBOOK_HPP
#include<QLabel>
#include"loggedinoperationpanel.hpp"
#include<QScrollArea>
#include"bookdatapanel.hpp"

class AppWindowLoggedInPanel;

class OperationPanelAddBook : public LoggedInOperationPanel{
    Q_OBJECT
public:
    OperationPanelAddBook(AppWindowLoggedInPanel*);
    ~OperationPanelAddBook();

private:
    QLabel addBookTitleLabel;
    // Book Data Panel
    QScrollArea scrollArea;
    BookDataPanel dataPanel;

    // Add Button
    QLabel addButton;
    // Cancel Button
    QLabel cancelButton;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    void addButtonPressed();
    void cancelButtonPressed();

    protected:
    // Funkcja przeładowania elementu
    void reload();

    bool eventMatching(QObject*, QEvent*);

};



#endif // OPERATIONPANELADDBOOK_HPP
