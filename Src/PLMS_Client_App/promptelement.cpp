#include"promptelement.hpp"
#include"promptelementexpandbutton.hpp"
#include<QLabel>
#include"promptlist.hpp"
#include"promptpanel.hpp"


PromptElement::PromptElement(PromptList *parent, PromptType type)
    : QFrame(parent), parent(parent), type(type){
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    setStyleSheet("QWidget{background-color: rgba(245, 245, 245, 0.4);}");
}

PromptElement::~PromptElement(){
    disconnectAll();
    deleteWidgets();
}

void PromptElement::init(){

}

void PromptElement::setWindow(){
    // Brak
}

void PromptElement::createWidgets(){
    closeButton = new QLabel(this);
    expandButton = new PromptElementExpandButton(this);
    errorTypeLabel = new QLabel(this);
    generalInfoLabel = new QLabel(this);
}

void PromptElement::createLayout(){
    generalInfoLabel->setGeometry(PROMPT_ELEMENT_ERROR_LABEL_WIDTH + 5, 0, PROMPT_ELEMENT_WIDTH - PROMPT_ELEMENT_ERROR_LABEL_WIDTH - 10 - PROMPT_ELEMENT_BUTTON_WIDTH, PROMPT_ELEMENT_ERROR_LABEL_HEIGHT);
    generalInfoLabel->setAlignment(Qt::AlignVCenter);
    generalInfoLabel->setWordWrap(true);
    expandButton->setBaseSize(PROMPT_ELEMENT_EXPAND_BUTTON_WIDTH, PROMPT_ELEMENT_EXPAND_BUTTON_HEIGHT);
    expandButton->show();
    closeButton->setGeometry(PROMPT_ELEMENT_WIDTH - PROMPT_ELEMENT_BUTTON_WIDTH,0,PROMPT_ELEMENT_BUTTON_WIDTH,PROMPT_ELEMENT_BUTTON_HEIGHT);
    closeButton->setAlignment(Qt::AlignCenter);
    closeButton->setPixmap(PROMPT_PANEL_CLOSE_BUTTON_PIXMAP);
    closeButton->show();
    errorTypeLabel->setScaledContents(true);
    errorTypeLabel->setGeometry(0,0,PROMPT_ELEMENT_ERROR_LABEL_WIDTH,PROMPT_ELEMENT_ERROR_LABEL_HEIGHT);
    errorTypeLabel->setAlignment(Qt::AlignCenter);
    switch(type){
    default:
        break;
    }
    errorTypeLabel->show();
}

void PromptElement::deleteWidgets(){
    delete expandButton;
    expandButton = nullptr;
    delete closeButton;
    closeButton = nullptr;
    delete generalInfoLabel;
    generalInfoLabel = nullptr;
    delete errorTypeLabel;
    errorTypeLabel = nullptr;
}

void PromptElement::connectAll(){
    expandButton->installEventFilter(parent->getParent());
    closeButton->installEventFilter(parent->getParent());
}

void PromptElement::disconnectAll(){
    parent->getParent()->removeEventFilter(expandButton);
    parent->getParent()->removeEventFilter(closeButton);
}

PromptElementExpandButton* PromptElement::getExpandButton(){
    return expandButton;
}

QLabel* PromptElement::getCloseButton(){
    return closeButton;
}

QLabel* PromptElement::getGeneralInfoLabel(){
    return generalInfoLabel;
}

PromptList* PromptElement::getParent(){
    return parent;
}

bool PromptElement::isExpanded(){
    return expanded;
}

PromptType PromptElement::getType(){
    return type;
}
