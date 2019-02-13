#ifndef OPERATIONPANELADDUSER_HPP
#define OPERATIONPANELADDUSER_HPP

#include<QLabel>
#include"loggedinoperationpanel.hpp"
#include<QScrollArea>
#include"userdatapanel.hpp"

class AppWindowLoggedInPanel;

class OperationPanelAddUser : public LoggedInOperationPanel{
    Q_OBJECT
public:
    OperationPanelAddUser(AppWindowLoggedInPanel*);
    ~OperationPanelAddUser();

private:
    QLabel addUserTitleLabel;
    // User Data Panel
    QScrollArea scrollArea;
    UserDataPanel dataPanel;

    // Register Button
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



#endif // OPERATIONPANELADDUSER_HPP
