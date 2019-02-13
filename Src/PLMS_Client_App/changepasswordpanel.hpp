#ifndef CHANGEPASSWORDPANEL_HPP
#define CHANGEPASSWORDPANEL_HPP
#include<QFrame>
#include<QLineEdit>
#include<QLabel>

class Dialog;
class User;
class ChangePasswordPanel : public QFrame{
    Q_OBJECT
public:
    ChangePasswordPanel(Dialog* parent, User* user);
    ~ChangePasswordPanel();

private:
    Dialog* parent = nullptr;
    User* user = nullptr;

    QLabel title;
    QLabel oldPasswordLabel;
    QLineEdit oldPasswordLE;
    QLabel newPasswordLabel;
    QLineEdit newPasswordLE;
    QLabel acceptButton;
    QLabel cancelButton;

    void create();
    bool standardLEKeyPressed(QKeyEvent* ev,QLineEdit* le);
    void acceptButtonPressed();
    void cancelButtonPressed();

public:
    bool eventMatching(QObject* obj, QEvent* ev);
};

#endif // CHANGEPASSWORDPANEL_HPP
