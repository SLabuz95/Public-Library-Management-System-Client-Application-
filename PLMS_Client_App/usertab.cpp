#include"usertab.hpp"
#include"tabbar.hpp"
#include<QLabel>
#include"windowmacros.hpp"
#include"user.hpp"

UserTab::UserTab(TabBar *setParent, User *setUser){
    parent = setParent;
    user = setUser;
    init();
    createWidgets();
    createLayout();
    connectAll();
}

UserTab::~UserTab(){
    disconnectAll();
    deleteWidgets();
    user = nullptr;
}

void UserTab::init(){
    installEventFilter(parent);
}

void UserTab::createWidgets(){
    userNameLabel = new QLabel(this);
    userNameLabel->show();
    closeLabel = new QLabel(this);
    closeLabel->installEventFilter(parent);
    closeLabel->show();
}

void UserTab::deleteWidgets(){
    delete userNameLabel;
    userNameLabel = nullptr;
    delete closeLabel;
    closeLabel = nullptr;
}

void UserTab::createLayout(){
    userNameLabel->setText(user->getUserName());
    userNameLabel->setGeometry(TABBAR_SIDEOFFSET, 0, QLabel(userNameLabel->text()).fontMetrics().horizontalAdvance(userNameLabel->text()), TABBAR_HEIGHT);
    closeLabel->setPixmap(QPixmap(USER_TAB_CLOSE_BUTTON_ICON));
}

void UserTab::connectAll(){
    // Brak operacji
}

void UserTab::disconnectAll(){
    // Brak operacji
}


QLabel* UserTab::getUserNameLabel(){
    return userNameLabel;
}

User* UserTab::getUser(){
    return user;
}

QLabel* UserTab::getCloseLabel(){
    return closeLabel;
}
