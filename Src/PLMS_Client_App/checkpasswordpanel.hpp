#ifndef CHECKPASSWORDPANEL_HPP
#define CHECKPASSWORDPANEL_HPP

#include"appwindowloggedinpanel.hpp"
#include"operationpanelfilteredlist.hpp"
#include<QFrame>
#include<QLabel>
#include<QLineEdit>

class Dialog;
class User;
class CheckPasswordPanel : public QFrame{
    Q_OBJECT
public:
    CheckPasswordPanel(Dialog* parent, User* user);
    ~CheckPasswordPanel();

private:
    Dialog* parent = nullptr;
    User* user = nullptr;

    QLabel titleLabel;
    QLabel password;
    QLineEdit passwordLE;
    QLabel acceptButton;
    QLabel cancelButton;

    void create();
    bool passwordLEKeyPressed(QKeyEvent*);
    void acceptButtonPressed();
    void cancelButtonPressed();

public:
    bool eventMatching(QObject* obj, QEvent* ev);

};

#endif // CHECKPASSWORDPANEL_HPP
