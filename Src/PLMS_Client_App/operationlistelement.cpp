#include"operationlistelement.hpp"
#include"operationlist.hpp"
#include"filteredlist.hpp"


OperationListElement::OperationListElement(OperationList *parent)
    : QFrame(parent), parent(parent),
      numberLabel(this),
      generalInfoLabel(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    setStyleSheet("OperationListElement{background-color: rgba(245, 245, 245, 0.5); border: 1px solid rgba(230,230,230, 0.8); border-radius: 5px;}");
}

OperationListElement::~OperationListElement(){
    disconnectAll();
    deleteWidgets();
}

void OperationListElement::init(){

}

void OperationListElement::setWindow(){
    // Brak
}

void OperationListElement::createWidgets(){

}

void OperationListElement::createLayout(){
    generalInfoLabel.setGeometry(OPERATION_ELEMENT_ERROR_LABEL_WIDTH, OPERATION_ELEMENT_VERTICAL_SIDE_OFFSET, OPERATION_ELEMENT_WIDTH - OPERATION_ELEMENT_ERROR_LABEL_WIDTH - OPERATION_ELEMENT_BUTTON_WIDTH, OPERATION_ELEMENT_ERROR_LABEL_HEIGHT);
    generalInfoLabel.setAlignment(Qt::AlignVCenter);
    generalInfoLabel.setWordWrap(true);
    numberLabel.setScaledContents(true);
    numberLabel.setGeometry(OPERATION_ELEMENT_HORIZONTAL_SIDE_OFFSET,OPERATION_ELEMENT_VERTICAL_SIDE_OFFSET,OPERATION_ELEMENT_ERROR_LABEL_WIDTH,OPERATION_ELEMENT_ERROR_LABEL_HEIGHT);
    numberLabel.setAlignment(Qt::AlignCenter);
}

void OperationListElement::deleteWidgets(){

}

void OperationListElement::connectAll(){

}

void OperationListElement::disconnectAll(){

}

QLabel& OperationListElement::getGeneralInfoLabel(){
    return generalInfoLabel;
}

OperationList* OperationListElement::getParent(){
    return parent;
}

QLabel& OperationListElement::getNumberLabel(){
    return numberLabel;
}
