#ifndef APPWINDOWREGISTERPANEL_HPP
#define APPWINDOWREGISTERPANEL_HPP

#include"appwindowcentralpanel.hpp"
#include"emptyenum.hpp"
#include<QLabel>
#include<QScrollArea>
#include"userdatapanel.hpp"

class AppWindow;

class AppWindowRegisterPanel : public AppWindowCentralPanel{
    Q_OBJECT
public:
    AppWindowRegisterPanel(AppWindow*);
    ~AppWindowRegisterPanel();

private:
    QLabel registerTitleLabel;
    // User Data Panel
    QScrollArea scrollArea;
    UserDataPanel dataPanel;

    // Register Button
    QLabel registerButton;
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

    void registerButtonPressed();
    void cancelButtonPressed();

    protected:
    // Funkcja przeładowania elementu
    void reload();

    bool eventMatching(QObject*, QEvent*);

};

#endif // APPWINDOWREGISTERPANEL_HPP
