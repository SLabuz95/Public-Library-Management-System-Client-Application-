#include"operationelementexpandbutton.hpp"
#include"operationlistelement.hpp"


OperationElementExpandButton::OperationElementExpandButton(OperationListElement *parent)
    : parent(parent)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationElementExpandButton::~OperationElementExpandButton(){
    disconnectAll();
    deleteWidgets();
}

void OperationElementExpandButton::init(){
    QFrame::setParent(parent);
}

void OperationElementExpandButton::setWindow(){
    // Brak
}

void OperationElementExpandButton::createWidgets(){
    expandPixmap = new QLabel(this);
}

void OperationElementExpandButton::createLayout(){
    repaint();
    expandPixmap->setScaledContents(true);
    expandPixmap->setAlignment(Qt::AlignCenter);
    expandPixmap->setGeometry(OPERATION_ELEMENT_EXPAND_BUTTON_ARROW_X, OPERATION_ELEMENT_EXPAND_BUTTON_ARROW_Y, OPERATION_ELEMENT_EXPAND_BUTTON_ICON_WIDTH,OPERATION_ELEMENT_EXPAND_BUTTON_ICON_HEIGHT);
    expandPixmap->show();
}

void OperationElementExpandButton::deleteWidgets(){
    delete expandPixmap;
    expandPixmap = nullptr;
}

void OperationElementExpandButton::connectAll(){
    // Brak
}

void OperationElementExpandButton::disconnectAll(){
    // Brak
}

OperationListElement* OperationElementExpandButton::getParent(){
    return parent;
}

void OperationElementExpandButton::repaint(){
    if(parent->isExpanded()){
        expandPixmap->setPixmap(PROMPT_ELEMENT_EXPAND_BUTTON_UP_EXTEND_ARROW_ICON);
    }else{
        expandPixmap->setPixmap(PROMPT_ELEMENT_EXPAND_BUTTON_DOWN_EXTEND_ARROW_ICON);
    }
}
