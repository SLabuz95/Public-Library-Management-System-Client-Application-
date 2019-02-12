#ifndef OPERATIONPANELUSERDATA_HPP
#define OPERATIONPANELUSERDATA_HPP
#include<QLabel>
#include"loggedinoperationpanel.hpp"
#include<QScrollArea>
#include"userdatapanel.hpp"

class AppWindowLoggedInPanel;

class OperationPanelUserData : public LoggedInOperationPanel{
    Q_OBJECT
public:
    OperationPanelUserData(AppWindowLoggedInPanel*);
    ~OperationPanelUserData();

private:
    QLabel userDataTitleLabel;
    // User Data Panel
    QScrollArea scrollArea;
    UserDataPanel dataPanel;

    // Book Panel
    QLabel bookPanelButton;
    // Change Data Button
    QLabel changeDataButton;
    // Cancel Button
    QLabel removeAccountButton;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    void bookPanelButtonPressed();
    void changeDataButtonPressed();
    void removeAccountButtonPressed();

    protected:
    // Funkcja przeładowania elementu
    void reload();

    bool eventMatching(QObject*, QEvent*);

};
#endif // OPERATIONPANELUSERDATA_HPP
