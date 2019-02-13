#ifndef OPERATIONPANELYOURACCOUNT_HPP
#define OPERATIONPANELYOURACCOUNT_HPP
#include<QLabel>
#include"loggedinoperationpanel.hpp"
#include<QScrollArea>
#include"userdatapanel.hpp"

class AppWindowLoggedInPanel;

class OperationPanelYourAccount : public LoggedInOperationPanel{
    Q_OBJECT
public:
    OperationPanelYourAccount(AppWindowLoggedInPanel*);
    ~OperationPanelYourAccount();

private:
    QLabel yourAccountTitleLabel;
    // User Data Panel
    QScrollArea scrollArea;
    UserDataPanel dataPanel;

    // Register Button
    QLabel changeDataButton;
    // RemoveAccount Button
    QLabel removeAccountButton;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    void changeDataButtonPressed();
    void removeAccountButtonPressed();

    protected:
    // Funkcja przeładowania elementu
    void reload();

    bool eventMatching(QObject*, QEvent*);

};


#endif // OPERATIONPANELYOURACCOUNT_HPP
