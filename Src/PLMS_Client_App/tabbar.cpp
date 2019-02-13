#include"tabbar.hpp"
#include<QFontMetrics>
#include"appwindow.hpp"
#include"usertab.hpp"
#include"app.hpp"
#include"../PLMS_Server_App/user.hpp"
#include<QLabel>

TabBar::TabBar(AppWindow *setParent)
    : QFrame (setParent)
{
    parent = setParent;
    setGeometry(TABBAR_X, TABBAR_Y, TABBAR_WIDTH, TABBAR_HEIGHT);
    init(true);
    createWidgets();
    createLayout();
    connectAll();
}

TabBar::~TabBar(){
    disconnectAll();
    deleteWidgets();
 }

void TabBar::init(bool firstIteration){
    if(firstIteration)
    {
        offset = 0;
        numbOfElements = parent->getParent()->getNumbOfUsers();
        actualNumberOfUserTabs = calculateActualNumberOfUserTabs();
        if(leftPos + actualNumberOfUserTabs == numbOfElements && leftPos != 0)
           init(false);
    }else{
        uint tempLeftPos = leftPos;
        ushort tempActualNumberOfUserTabs;
        do{
            leftPos--;
            tempActualNumberOfUserTabs = calculateActualNumberOfUserTabs();
            if(leftPos + tempActualNumberOfUserTabs != numbOfElements){
                leftPos = tempLeftPos;
                return;
            }else{
                tempLeftPos = leftPos;
                actualNumberOfUserTabs = tempActualNumberOfUserTabs;
            }
        }while(tempLeftPos != 0);
    }
 }

void TabBar::createWidgets(){
    if(actualNumberOfUserTabs != numbOfElements){
        userTabs = new UserTab*[actualNumberOfUserTabs];
        for(uint i = 0; i < actualNumberOfUserTabs; i++){
           (*(userTabs + i)) =  new UserTab(this, *(parent->getParent()->getUsers() + leftPos + i));
            static_cast<QWidget*>(*(userTabs + i))->setParent(this);
            (*(userTabs + i))->show();
        }
        leftArrowButton = new QLabel(this);
        rightArrowButton = new QLabel(this);
        }else{
        userTabs = new UserTab*[numbOfElements];
        for(uint i = 0; i < numbOfElements; i++){
            (*(userTabs + i)) =  new UserTab(this, *(parent->getParent()->getUsers() + i));
            static_cast<QFrame*>(*(userTabs + i))->setParent(this);
            (*(userTabs + i))->show();
        }
    }

}

void TabBar::createLayout(){
    if(actualNumberOfUserTabs != numbOfElements){
        leftArrowButton->setGeometry(0, 0, TABBAR_BUTTON_WIDTH, TABBAR_HEIGHT);
        leftArrowButton->setPixmap(TAB_BAR_LEFT_EXTEND_BUTTON_ICON);
        rightArrowButton->setGeometry(TABBAR_WIDTH - TABBAR_BUTTON_WIDTH , 0, TABBAR_BUTTON_WIDTH, TABBAR_HEIGHT);
        rightArrowButton->setPixmap(TAB_BAR_RIGHT_EXTEND_BUTTON_ICON);
        leftArrowButton->installEventFilter(this);
        rightArrowButton->installEventFilter(this);
        if(leftPos != 0){
            leftArrowButton->show();
            if(leftPos + actualNumberOfUserTabs != numbOfElements){
                rightArrowButton->show();
                uint sumOfTextWidth = 0;
                for(uint i = 0; i < (actualNumberOfUserTabs); i++)
                    sumOfTextWidth += TABBAR_ELEMENT_WIDTH_FOR_CREATED;
                offset = ((TABBAR_WIDTH - 2 * TABBAR_BUTTON_WIDTH - actualNumberOfUserTabs * TABBAR_BUTTONS_OFFSET) - sumOfTextWidth)/actualNumberOfUserTabs;
                uint offsetForUserTabs = TABBAR_BUTTON_WIDTH;
                for(uint i = 0; i < (actualNumberOfUserTabs); i++){
                    (*(userTabs + i))->getCloseLabel()->setGeometry(TABBAR_ELEMENT_WIDTH_FOR_CREATED - TABBAR_BUTTON_WIDTH, 0, TABBAR_BUTTON_WIDTH, TABBAR_HEIGHT);
                    (*(userTabs + i))->setGeometry(offsetForUserTabs, 0, TABBAR_ELEMENT_WIDTH_FOR_CREATED, TABBAR_HEIGHT);
                    offsetForUserTabs += TABBAR_ELEMENT_WIDTH_FOR_CREATED + TABBAR_BUTTONS_OFFSET;
                }
                }else{
                    uint sumOfTextWidth = 0;
                    for(uint i = 0; i < (actualNumberOfUserTabs); i++)
                       sumOfTextWidth += TABBAR_ELEMENT_WIDTH_FOR_CREATED;
                    offset = ((TABBAR_WIDTH - TABBAR_BUTTON_WIDTH - actualNumberOfUserTabs * TABBAR_BUTTONS_OFFSET) - sumOfTextWidth)/actualNumberOfUserTabs;
                    uint offsetForUserTabs = TABBAR_BUTTON_WIDTH;
                    for(uint i = 0; i < (actualNumberOfUserTabs); i++){
                        (*(userTabs + i))->setGeometry(offsetForUserTabs, 0, TABBAR_ELEMENT_WIDTH_FOR_CREATED, TABBAR_HEIGHT);
                        (*(userTabs + i))->getCloseLabel()->setGeometry(TABBAR_ELEMENT_WIDTH_FOR_CREATED - TABBAR_BUTTON_WIDTH, 0, TABBAR_BUTTON_WIDTH, TABBAR_HEIGHT);
                        offsetForUserTabs += TABBAR_ELEMENT_WIDTH_FOR_CREATED + TABBAR_BUTTONS_OFFSET;
                    }
                }

            }
            else{
                rightArrowButton->show();
                uint sumOfTextWidth = 0;
                for(uint i = 0; i < (actualNumberOfUserTabs); i++)
                    sumOfTextWidth += TABBAR_ELEMENT_WIDTH_FOR_CREATED;
                offset = ((TABBAR_WIDTH - TABBAR_BUTTON_WIDTH - actualNumberOfUserTabs * TABBAR_BUTTONS_OFFSET) - sumOfTextWidth)/actualNumberOfUserTabs;
                uint offsetForUserTabs = 0;
                for(uint i = 0; i < (actualNumberOfUserTabs); i++){
                    (*(userTabs + i))->setGeometry(offsetForUserTabs, 0, TABBAR_ELEMENT_WIDTH_FOR_CREATED, TABBAR_HEIGHT);
                    (*(userTabs + i))->getCloseLabel()->setGeometry(TABBAR_ELEMENT_WIDTH_FOR_CREATED  - TABBAR_BUTTON_WIDTH, 0, TABBAR_BUTTON_WIDTH, TABBAR_HEIGHT);
                    offsetForUserTabs += TABBAR_ELEMENT_WIDTH_FOR_CREATED+ TABBAR_BUTTONS_OFFSET;
                }
            }
        }else{
            offset = 10;
            uint offsetForUserTabs = 0;
            for(uint i = 0; i < actualNumberOfUserTabs; i++){
                (*(userTabs + i))->setGeometry(offsetForUserTabs, 0, TABBAR_ELEMENT_WIDTH_FOR_CREATED, TABBAR_HEIGHT);
                (*(userTabs + i))->getCloseLabel()->setGeometry(TABBAR_ELEMENT_WIDTH_FOR_CREATED  - TABBAR_BUTTON_WIDTH, 0, TABBAR_BUTTON_WIDTH, TABBAR_HEIGHT);
                offsetForUserTabs += TABBAR_ELEMENT_WIDTH_FOR_CREATED + TABBAR_BUTTONS_OFFSET;
            }
         }
    for(uint i = 0; i < actualNumberOfUserTabs; i++){
        if((*(userTabs + i))->getUser() == parent->getParent()->getActiveUser())
            (*(userTabs + i))->setStyleSheet("UserTab{background-color: qlineargradient(x1:0.5 , y1: 1, x2: 0.5, y2: 0, stop: 0 rgba(200,200,200,0.77), stop: 0.93 rgba(247,247,247,0.8), stop: 0.99 rgba(247,247,247,0.8)); border-radius: 10px 10px; border-style:solid; border-width: 1px; border-color: rgba(255, 255, 255, 0.4);}");
        else
            (*(userTabs + i))->setStyleSheet("UserTab{background-color: rgba(255, 255, 255, 0.4); border-radius: 10px 10px; border-style:solid; border-width: 1px; border-color: rgba(255, 255, 255, 0.7);}");
    }
}

void TabBar::deleteWidgets(){
    for(uint i = 0; i < (actualNumberOfUserTabs) ; i++){
        delete (*(userTabs + i));
        (*(userTabs + i)) = nullptr;
    }
    delete []userTabs;
    userTabs = nullptr;
   if(leftArrowButton != nullptr)
       delete leftArrowButton;
   leftArrowButton = nullptr;
   if(rightArrowButton != nullptr)
       delete rightArrowButton;
   rightArrowButton = nullptr;
   }

void TabBar::connectAll(){

}

void TabBar::disconnectAll(){

}

ushort TabBar::calculateActualNumberOfUserTabs(){
    uint offsetFunc = 0;
    ushort number = 0;
    for(ushort i = leftPos ; i < numbOfElements ; i++){
        offsetFunc += TABBAR_ELEMENT_WIDTH_BEFORE_CREATING + TABBAR_BUTTONS_OFFSET;
        number++;
        if(offsetFunc > (TABBAR_WIDTH - 2 * TABBAR_BUTTON_WIDTH))
            return number - 1;
    }
    return number;
}

void TabBar::reload(){
    disconnectAll();
    deleteWidgets();
    move = 0;
    init(true);
    createWidgets();
    createLayout();
    connectAll();
    }

AppWindow* TabBar::getParent(){
    return parent;
}

UserTab** TabBar::getUserTabs(){
    return userTabs;
}

ushort TabBar::getActualNumberOfUserTabs(){
    return actualNumberOfUserTabs;
}

QLabel* TabBar::getLeftArrowButton(){
    return leftArrowButton;
}

QLabel* TabBar::getRightArrowButton(){
    return rightArrowButton;
}

void TabBar::leftArrowButtonReleased(){
    leftPos--;
    move = 1;
    reload();
}

void TabBar::rightArrowButtonReleased(){
    leftPos++;
    move = -1;
    reload();
}

bool TabBar::eventFilter(QObject *obj, QEvent *ev){
    switch(ev->type()){
    case QEvent::MouseButtonRelease:
    {
        if(leftArrowButton == obj)
        {
            leftArrowButtonReleased();
            return true;
        }
        if(rightArrowButton == obj){
            rightArrowButtonReleased();
            return true;
        }
        UserTab** tempPtr = (userTabs + leftPos);
        // _PH_ Events for UsersTabs _ need implemantion
        for(ushort i = leftPos; i <  leftPos + actualNumberOfUserTabs; i++, tempPtr++){
            if(obj == (*tempPtr)->getCloseLabel()){
                parent->getParent()->removeUser((*tempPtr)->getUser());
                reload();
                return true;
            }
        }
    }
        break;
    case QEvent::Enter:
        {
            uint i = 0;
            for( ; i < actualNumberOfUserTabs; i++){
                if(obj == (*(userTabs + i))->getCloseLabel())
                {
                    parent->getStatusBar().showMessage(QString("Wyloguj wskazane konto"));
                    return true;
                }else{
                    parent->getStatusBar().showMessage(QString("Przejdź do wskazanego konta"));
                    return true;
                }
            }
        }
         break;
        case QEvent::Leave:
        {
            parent->getStatusBar().showMessage(STATUS_BAR_READY_TEXT);
            return true;
        }
    default:
        {
          return QObject::eventFilter(obj, ev);
        }
      }
    return true;
}
