#include"PromptElementDataNotReaded.hpp"
#include"windowmacros.hpp"
#include<QLabel>
#include"promptelementexpandbutton.hpp"
#include"promptlist.hpp"
#include"projectinfo.hpp"
#include"promptpanel.hpp"
#include"promptpanelcatchevents.hpp"
#include<QEvent>

PromptElementDataNotReaded::PromptElementDataNotReaded(PromptList *parent, PromptType type, ProjectInfo *project, ProjectMenagerParam param, QString wrongData)
    : PromptElement(parent,type,project){
    projectParam = param;
    this->wrongData = wrongData;
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

PromptElementDataNotReaded::~PromptElementDataNotReaded(){
    disconnectAll();
    deleteWidgets();
}

void PromptElementDataNotReaded::init(){
    generateText();
}

void PromptElementDataNotReaded::setWindow(){
    if(expanded)
        resize(PROMPT_ELEMENT_WIDTH,generalInfoLabel->height() + PROMPT_ELEMENT_EXPAND_BUTTON_HEIGHT);
    else
        resize(PROMPT_ELEMENT_WIDTH, PROMPT_ELEMENT_BUTTON_HEIGHT + PROMPT_ELEMENT_EXPAND_BUTTON_HEIGHT);
}

void PromptElementDataNotReaded::createWidgets(){
    // Brak
}

void PromptElementDataNotReaded::createLayout(){
    // Brak
    if(expanded)
        expandButton->move(0, generalInfoLabel->height());
    else
        expandButton->move(0, PROMPT_ELEMENT_BUTTON_HEIGHT);
}

void PromptElementDataNotReaded::deleteWidgets(){
    // Brak
}

void PromptElementDataNotReaded::connectAll(){
    // Brak
}

void PromptElementDataNotReaded::disconnectAll(){
    // Brak
}

QString PromptElementDataNotReaded::getParamName(){
    switch(projectParam){
    case PROJECT_MENAGER_COMPRESIBILITY_FACTOR:
        return QString("\"Współczynnik ściśliwości\"");
    case PROJECT_MENAGER_FLOW:
        return QString("\"Znamionowy przepływ\"");
    case PROJECT_MENAGER_MAX_DIFF_PRESSURE:
        return QString("\"Ciśnienie różnicowe\"");
    case PROJECT_MENAGER_MAX_FLOW_VALUE:
        return QString("\"Maksymalny przepływ\"");
    case PROJECT_MENAGER_MAX_UPSTREAM_PRESSURE:
        return QString("\"Bezwzględne ciśnienie przed zwężką\"");
    case PROJECT_MENAGER_PIPE_DIAMETER:
        return QString("\"Średnica rurociągu\"");
    case PROJECT_MENAGER_PRESSURE_TAP_DIAMETER:
        return QString("\"Średnica otworu impulsowego\"");
    case PROJECT_MENAGER_TEMP:
        return QString("\"Temperatura substancji\"");
    case PROJECT_MENAGER_WORK_DENSITY:
        return QString("\"Gęstość robocza\"");
    case PROJECT_MENAGER_WORK_DYNAMIC_VISCOSITY:
        return QString("\"Dynamiczny współczynnik lepkości\"");
    case PROJECT_MENAGER_WORK_HEAT_CAPACITY_RATIO:
        return QString("\"Wykładnik izentropy\"");
    case PROJECT_MENAGER_COMPANY_NAME:
        return QString("\"Nazwa firmy\"");
    case PROJECT_MENAGER_FLANGE_NAME:
        return QString("\"Nazwa zwężki\"");
    case PROJECT_MENAGER_OBJECT_NAME:
        return QString("\"Nazwa obiektu\"");
    case PROJECT_MENAGER_PROJECT_NAME:
        return QString("\"Nazwa projektu\"");
    case PROJECT_MENAGER_OTHER_SUBSTANCE_NAME:
        return QString("\"Nazwa substancji\"");
   default:
        return nullptr;
    }
}

void PromptElementDataNotReaded::generateText(){
    QString str(QString("Parametr ") + getParamName() + " nie został odczytany z powodu błędnego formatu.");
    if(expanded){
        uint newHeight = generalInfoLabel->fontMetrics().boundingRect(0,0, PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH, 1200, Qt::TextWordWrap, str).height();
        generalInfoLabel->resize(PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH, (newHeight < PROMPT_ELEMENT_BUTTON_HEIGHT)? PROMPT_ELEMENT_BUTTON_HEIGHT : newHeight);
        generalInfoLabel->setText(str);
    }else{
        generalInfoLabel->resize(PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH, PROMPT_ELEMENT_ERROR_LABEL_HEIGHT);
        generalInfoLabel->setText(generalInfoLabel->fontMetrics().elidedText(str,Qt::ElideRight, PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH));
    }
}

void PromptElementDataNotReaded::reload(){
    disconnectAll();
    deleteWidgets();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

bool PromptElementDataNotReaded::eventMatching(QObject *obj, QEvent *ev){
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

void PromptElementDataNotReaded::expandButtonReleased(){
    if(expanded)
        minimize();
    else
        expand();
    parent->reallocate();
}

void PromptElementDataNotReaded::expand(){
    expanded = true;
    expandButton->repaint();
    setWindow();
    generateText();
    createWidgets();
    createLayout();
    connectAll();
}

void PromptElementDataNotReaded::minimize(){
    expanded = false;
    expandButton->repaint();
    generateText();
    setWindow();
    createLayout();
    disconnectAll();
    deleteWidgets();
}

void PromptElementDataNotReaded::closeButtonReleased(){
    parent->deleteElement(this);
}
