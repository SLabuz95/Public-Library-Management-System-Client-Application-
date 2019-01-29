#ifndef APPWINDOWLOGINPANEL_HPP
#define APPWINDOWLOGINPANEL_HPP

#include"appwindowcentralpanel.hpp"
#include"emptyenum.hpp"
#include<QLabel>
#include<QCheckBox>
#include"formatabledatafield.hpp"

class AppWindow;

class AppWindowLoginPanel : public AppWindowCentralPanel{
    Q_OBJECT
public:
    AppWindowLoginPanel(AppWindow*);
    ~AppWindowLoginPanel();

private:
    QLabel loginTitleLabel;
    // Login Name Line
    QLabel loginNameLabel;
    FormatableDataField<Empty> loginNameField;
    // Login Password Line
    QLabel loginPasswordLabel;
    FormatableDataField<Empty> loginPasswordField;
    QCheckBox passwordHiddenCB;
    QString password;
    // Actions Buttons
    QLabel loginButton;
    QLabel registerButton;

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
    void reload();

    bool eventMatching(QObject*, QEvent*);
    void loginButtonPressed();
    void registerButtonPressed();
    void passwordHiddenCBPressed();

};

#endif // APPWINDOWLOGINPANEL_HPP
