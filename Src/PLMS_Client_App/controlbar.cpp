#include"controlbar.hpp"
#include"operationlist.hpp"
#include<QEvent>
#include"filteredlist.hpp"
ControlBar::ControlBar(OperationList *parent, bool nextPage, uint pageNumber)
    : QFrame(parent), parent(parent),
      leftArrowLabel(this),
      rightArrowLabel(this),
      pageNumberLabel(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    repaint(nextPage, pageNumber);
    connectAll();
}

ControlBar::~ControlBar(){
    disconnectAll();
    deleteWidgets();
}

void ControlBar::init(){

}

void ControlBar::setWindow(){
    setStyleSheet("ControlBar{background-color: rgba(245, 245, 245, 0.4);}");
    resize(CONTROL_BAR_WIDTH, CONTROL_BAR_HEIGHT);
}

void ControlBar::createWidgets(){
    // Empty
}

void ControlBar::createLayout(){
    leftArrowLabel.setPixmap(TAB_BAR_LEFT_EXTEND_BUTTON_ICON);
    leftArrowLabel.setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_LOWLIGHT);
    rightArrowLabel.setPixmap(TAB_BAR_RIGHT_EXTEND_BUTTON_ICON);
    rightArrowLabel.setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_LOWLIGHT);
    leftArrowLabel.setGeometry(0,0, CONTROL_BAR_BUTTON_WIDTH, CONTROL_BAR_HEIGHT);
    rightArrowLabel.setGeometry(CONTROL_BAR_WIDTH - CONTROL_BAR_BUTTON_WIDTH, 0, CONTROL_BAR_BUTTON_WIDTH, CONTROL_BAR_BUTTON_HEIGHT);
    pageNumberLabel.setGeometry(CONTROL_BAR_LABEL_X, CONTROL_BAR_LABEL_Y, CONTROL_BAR_LABEL_WIDTH, CONTROL_BAR_LABEL_HEIGHT);
    pageNumberLabel.setStyleSheet("background-color: transparent;");
    pageNumberLabel.setAlignment(Qt::AlignCenter);
}

void ControlBar::deleteWidgets(){

}

void ControlBar::connectAll(){
   leftArrowLabel.installEventFilter(parent->getParent());
   rightArrowLabel.installEventFilter(parent->getParent());
}

void ControlBar::disconnectAll(){
    // Brak
}

OperationList* ControlBar::getParent(){
    return parent;
}

void ControlBar::repaint(bool nextPage, uint pageNumb){
    if(pageNumb > 0)
        leftArrowLabel.show();
    else {
        leftArrowLabel.hide();
    }
    if(nextPage)
        rightArrowLabel.show();
    else {
        rightArrowLabel.hide();
    }
    pageNumberLabel.setText(QString("Strona: ") + QString::number(pageNumb + 1));

}

bool ControlBar::eventMatching(QObject *obj, QEvent *ev){
    switch(ev->type()){
    case QEvent::MouseButtonRelease:
    {
        if(obj == &leftArrowLabel){
            leftArrowButtonPressed();
            return true;
        }
        if(obj == &rightArrowLabel){
            rightArrowButtonPressed();
            return true;
        }
    }
        break;
    case QEvent::Enter:
    {
        if(obj == &leftArrowLabel){
            leftArrowLabel.setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_HIGHLIGHT);
            break;
        }
        if(obj == &rightArrowLabel){
            rightArrowLabel.setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_HIGHLIGHT);
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &leftArrowLabel){
            leftArrowLabel.setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_LOWLIGHT);
            break;
        }
        if(obj == &rightArrowLabel){
            rightArrowLabel.setStyleSheet(STYLESHEET_BUTTON_NO_BORDER_LOWLIGHT);
            break;
        }
    }
        break;
    default:
        break;
    }
    return false;
}

void ControlBar::leftArrowButtonPressed(){
    parent->previousPageInit();
}

void ControlBar::rightArrowButtonPressed(){
    parent->nextPageInit();
}
