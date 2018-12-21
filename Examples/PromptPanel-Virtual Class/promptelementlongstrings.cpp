#include"promptelementlongstrings.hpp"
#include"windowmacros.hpp"
#include<QLabel>
#include"promptelementexpandbutton.hpp"
#include"promptlist.hpp"
#include"projectinfo.hpp"
#include"promptpanel.hpp"
#include"promptpanelcatchevents.hpp"
#include<QEvent>

PromptElementLongStrings::PromptElementLongStrings(PromptList *parent, PromptType type, QString str)
    : PromptElement(parent,type,project){
    text = str;
    init(str);
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

PromptElementLongStrings::~PromptElementLongStrings(){
    disconnectAll();
    deleteWidgets();
}

void PromptElementLongStrings::init(QString &str){
    generateText(str);
}

void PromptElementLongStrings::setWindow(){
    if(expanded)
        resize(PROMPT_ELEMENT_WIDTH,generalInfoLabel->height() + PROMPT_ELEMENT_EXPAND_BUTTON_HEIGHT);
    else
        resize(PROMPT_ELEMENT_WIDTH, PROMPT_ELEMENT_BUTTON_HEIGHT + PROMPT_ELEMENT_EXPAND_BUTTON_HEIGHT);
}

void PromptElementLongStrings::createWidgets(){
    // Brak
}

void PromptElementLongStrings::createLayout(){
    // Brak
    if(expanded)
        expandButton->move(0, generalInfoLabel->height());
    else
        expandButton->move(0, PROMPT_ELEMENT_BUTTON_HEIGHT);
}

void PromptElementLongStrings::deleteWidgets(){
    // Brak
}

void PromptElementLongStrings::connectAll(){
    // Brak
}

void PromptElementLongStrings::disconnectAll(){
    // Brak
}

void PromptElementLongStrings::generateText(){
    if(expanded){
        uint newHeight = generalInfoLabel->fontMetrics().boundingRect(0,0, PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH, 1200, Qt::TextWordWrap, text).height();
        generalInfoLabel->resize(PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH, (newHeight < PROMPT_ELEMENT_BUTTON_HEIGHT)? PROMPT_ELEMENT_BUTTON_HEIGHT : newHeight);
        generalInfoLabel->setText(text);
    }else{
        generalInfoLabel->resize(PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH, PROMPT_ELEMENT_ERROR_LABEL_HEIGHT);
        generalInfoLabel->setText(generalInfoLabel->fontMetrics().elidedText(text,Qt::ElideRight, PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH));
    }
}

void PromptElementLongStrings::generateText(QString &str){
    if(expanded){
        uint newHeight = generalInfoLabel->fontMetrics().boundingRect(0,0, PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH, 1200, Qt::TextWordWrap, text).height();
        generalInfoLabel->resize(PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH, (newHeight < PROMPT_ELEMENT_BUTTON_HEIGHT)? PROMPT_ELEMENT_BUTTON_HEIGHT : newHeight);
        generalInfoLabel->setText(text);
    }else{
        generalInfoLabel->resize(PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH, PROMPT_ELEMENT_ERROR_LABEL_HEIGHT);
        generalInfoLabel->setText(generalInfoLabel->fontMetrics().elidedText(text,Qt::ElideRight, PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH));
    }
}

void PromptElementLongStrings::reload(){
    disconnectAll();
    deleteWidgets();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

bool PromptElementLongStrings::eventMatching(QObject *obj, QEvent *ev){
    if(obj == closeButton){
        switch (ev->type()){
        case QEvent::MouseButtonRelease:
            closeButtonReleased();
            break;
        default:
            break;
        }
        return true;
    }
    if(obj == expandButton){
        switch(ev->type()){
        case QEvent::MouseButtonRelease:
            expandButtonReleased();
            break;
        default:
            break;
        }
        return true;
    }
    return false;
}

void PromptElementLongStrings::expandButtonReleased(){
    if(expanded)
        minimize();
    else
        expand();
    parent->reallocate();
}

void PromptElementLongStrings::expand(){
    expanded = true;
    expandButton->repaint();
    generateText();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

void PromptElementLongStrings::minimize(){
    expanded = false;
    expandButton->repaint();
    generateText();
    setWindow();
    createLayout();
    disconnectAll();
    deleteWidgets();
}

void PromptElementLongStrings::closeButtonReleased(){
    parent->deleteElement(this);
}
