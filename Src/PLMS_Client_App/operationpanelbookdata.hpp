#ifndef OPERATIONPANELBOOKDATA_HPP
#define OPERATIONPANELBOOKDATA_HPP

#include<QLabel>
#include"loggedinoperationpanel.hpp"
#include<QScrollArea>
#include"bookdatapanel.hpp"

class AppWindowLoggedInPanel;

class OperationPanelBookData : public LoggedInOperationPanel{
    Q_OBJECT
public:
    OperationPanelBookData(AppWindowLoggedInPanel*);
    ~OperationPanelBookData();

private:
    QLabel bookDataTitleLabel;
    // User Data Panel
    QScrollArea scrollArea;
    BookDataPanel dataPanel;

    // Register Button
    QLabel changeDataButton;
    // Cancel Button
    QLabel removeButton;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    void changeDataButtonPressed();
    void removeButtonPressed();

    protected:
    // Funkcja przeładowania elementu
    void reload();

    bool eventMatching(QObject*, QEvent*);

};

#endif // OPERATIONPANELBOOKDATA_HPP
