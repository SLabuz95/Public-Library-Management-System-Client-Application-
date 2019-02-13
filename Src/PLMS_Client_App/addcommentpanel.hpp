#ifndef ADDCOMMENTPANEL_HPP
#define ADDCOMMENTPANEL_HPP

#include"appwindowloggedinpanel.hpp"
#include"operationpanelfilteredlist.hpp"
#include<QFrame>
#include<QLabel>
#include<QTextEdit>

class Dialog;
class User;
class AddCommentPanel : public QFrame{
    Q_OBJECT
public:
    AddCommentPanel(Dialog* parent, Book* book, unsigned long long userId);
    ~AddCommentPanel();

private:
    Dialog* parent = nullptr;
    Book* book = nullptr;
    unsigned long long userId = 0;

    QLabel titleLabel;
    QTextEdit commentEdit;
    QLabel acceptButton;
    QLabel cancelButton;

    void create();
    bool commentEditKeyPressed(QKeyEvent*);
    void acceptButtonPressed();
    void cancelButtonPressed();


public:
    bool eventMatching(QObject* obj, QEvent* ev);

};


#endif // ADDCOMMENTPANEL_HPP
