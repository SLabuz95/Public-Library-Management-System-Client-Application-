#include"promptelementexpandbutton.hpp"
#include"promptelement.hpp"
#include<QLabel>
#include"windowmacros.hpp"

PromptElementExpandButton::PromptElementExpandButton(PromptElement *parent)
    : parent(parent)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

PromptElementExpandButton::~PromptElementExpandButton(){
    disconnectAll();
    deleteWidgets();
}

void PromptElementExpandButton::init(){
    QFrame::setParent(parent);
}

void PromptElementExpandButton::setWindow(){
    // Brak
}

void PromptElementExpandButton::createWidgets(){
    expandPixmap = new QLabel(this);
}

void PromptElementExpandButton::createLayout(){
    repaint();
    expandPixmap->setScaledContents(true);
    expandPixmap->setAlignment(Qt::AlignCenter);
    expandPixmap->setGeometry(PROMPT_ELEMENT_EXPAND_BUTTON_ARROW_X, PROMPT_ELEMENT_EXPAND_BUTTON_ARROW_Y, PROMPT_ELEMENT_EXPAND_BUTTON_ICON_WIDTH,PROMPT_ELEMENT_EXPAND_BUTTON_ICON_HEIGHT);
    expandPixmap->show();
}

void PromptElementExpandButton::deleteWidgets(){
    delete expandPixmap;
    expandPixmap = nullptr;
}

void PromptElementExpandButton::connectAll(){
    // Brak
}

void PromptElementExpandButton::disconnectAll(){
    // Brak
}

PromptElement* PromptElementExpandButton::getParent(){
    return parent;
}

void PromptElementExpandButton::repaint(){
    if(parent->isExpanded()){
        expandPixmap->setPixmap(PROMPT_ELEMENT_EXPAND_BUTTON_UP_EXTEND_ARROW_ICON);
    }else{
        expandPixmap->setPixmap(PROMPT_ELEMENT_EXPAND_BUTTON_DOWN_EXTEND_ARROW_ICON);
    }
}
