#include"promptelementdisplaydataavailable.hpp"
#include"windowmacros.hpp"
#include<QLabel>
#include"promptelementexpandbutton.hpp"
#include"promptlist.hpp"
#include"projectinfo.hpp"
#include"promptpanel.hpp"
#include"promptpanelcatchevents.hpp"
#include<QEvent>
#include"formatabledatafield.hpp"
#include<QLineEdit>

PromptElementDisplayDataAvailable::PromptElementDisplayDataAvailable(PromptList *parent, PromptType type, ProjectInfo *project, ProjectMenagerParam param, FormatableDataField<ProjectMenagerParam> *element)
    : PromptElement(parent,type,project){
    projectParam = param;
    this->element = element;
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

PromptElementDisplayDataAvailable::~PromptElementDisplayDataAvailable(){
    disconnectAll();
    deleteWidgets();
}

void PromptElementDisplayDataAvailable::init(){
    generateText();
}

void PromptElementDisplayDataAvailable::setWindow(){
    if(expanded)
        resize(PROMPT_ELEMENT_WIDTH,generalInfoLabel->height() + PROMPT_ELEMENT_BUTTON_HEIGHT + PROMPT_ELEMENT_EXPAND_BUTTON_HEIGHT);
    else
        resize(PROMPT_ELEMENT_WIDTH, PROMPT_ELEMENT_BUTTON_HEIGHT + PROMPT_ELEMENT_EXPAND_BUTTON_HEIGHT);
}

void PromptElementDisplayDataAvailable::createWidgets(){
    if(expanded){
        if(checkValueExistance(false))
            lastSavedValueButton = new QLabel(this);
        if((projectParam == PROJECT_MENAGER_WORK_DENSITY || projectParam == PROJECT_MENAGER_WORK_DYNAMIC_VISCOSITY) && checkValueExistance(true))
            interpolatedValueButton = new QLabel(this);
    }
}

void PromptElementDisplayDataAvailable::createLayout(){
    if(expanded){
        if(lastSavedValueButton && interpolatedValueButton){
            lastSavedValueButton->setGeometry(0,generalInfoLabel->height(),PROMPT_ELEMENT_DISPLAY_DATA_AVAILABLE_WHEN_TWO_BUTTONS_BUTTON_WIDTH, PROMPT_ELEMENT_BUTTON_HEIGHT);
            lastSavedValueButton->setStyleSheet("font-family: \"Georgia\"; font-weight: 400;border-radius: 4px; border-color: rgba(190,190,190,0.6); border-width: 1px; background-color: rgba(190,190,190,0.6);");
            interpolatedValueButton->setGeometry(PROMPT_ELEMENT_DISPLAY_DATA_AVAILABLE_WHEN_TWO_BUTTONS_BUTTON_WIDTH, generalInfoLabel->height(),PROMPT_ELEMENT_DISPLAY_DATA_AVAILABLE_WHEN_TWO_BUTTONS_BUTTON_WIDTH,PROMPT_ELEMENT_BUTTON_HEIGHT);
            interpolatedValueButton->setStyleSheet("font-family: \"Georgia\"; font-weight: 400;border-radius: 4px; border-color: rgba(190,190,190,0.6); border-width: 1px; background-color: rgba(190,190,190,0.6);");
            lastSavedValueButton->setText("Ostatnia własna");
            lastSavedValueButton->setAlignment(Qt::AlignCenter);
            interpolatedValueButton->setText("Ostatnia programowa");
            interpolatedValueButton->setAlignment(Qt::AlignCenter);
            lastSavedValueButton->show();
            interpolatedValueButton->show();
        }else{
            if(lastSavedValueButton){
                lastSavedValueButton->setGeometry(0,generalInfoLabel->height(),PROMPT_ELEMENT_DISPLAY_DATA_AVAILABLE_ONLY_ONE_BUTTON_WIDTH, PROMPT_ELEMENT_BUTTON_HEIGHT);
                lastSavedValueButton->setStyleSheet("font-family: \"Georgia\"; font-weight: 400;border-radius: 4px; border-color: rgba(190,190,190,0.6); border-width: 1px; background-color: rgba(190,190,190,0.6);");
                lastSavedValueButton->setText("Ostatnia własna");
                lastSavedValueButton->setAlignment(Qt::AlignCenter);
                lastSavedValueButton->show();
            }
            else{
                if(interpolatedValueButton){
                    interpolatedValueButton->setGeometry(0, generalInfoLabel->height(),PROMPT_ELEMENT_DISPLAY_DATA_AVAILABLE_ONLY_ONE_BUTTON_WIDTH,PROMPT_ELEMENT_BUTTON_HEIGHT);
                    interpolatedValueButton->setStyleSheet("font-family: \"Georgia\"; font-weight: 400;border-radius: 4px; border-color: rgba(190,190,190,0.6); border-width: 1px; background-color: rgba(190,190,190,0.6);");
                    interpolatedValueButton->setText("Ostatnia programowa");
                    interpolatedValueButton->setAlignment(Qt::AlignCenter);
                    interpolatedValueButton->show();
                }
            }
        }
    }
    if(expanded)
        expandButton->move(0, generalInfoLabel->height() +  PROMPT_ELEMENT_BUTTON_HEIGHT );
    else
        expandButton->move(0, PROMPT_ELEMENT_BUTTON_HEIGHT);
}

void PromptElementDisplayDataAvailable::deleteWidgets(){
    if(lastSavedValueButton){
        delete lastSavedValueButton;
        lastSavedValueButton = nullptr;
    }
    if(interpolatedValueButton){
        delete interpolatedValueButton;
        interpolatedValueButton = nullptr;
    }
}

void PromptElementDisplayDataAvailable::connectAll(){
    if(expanded){
        if(lastSavedValueButton)
            lastSavedValueButton->installEventFilter(parent->getParent()->getCatchEvents());
        if(interpolatedValueButton)
            interpolatedValueButton->installEventFilter(parent->getParent()->getCatchEvents());
    }
}

void PromptElementDisplayDataAvailable::disconnectAll(){
    // Brak
}

FormatableData<ProjectMenagerParam>* PromptElementDisplayDataAvailable::checkValueExistance(bool interpolatedValueCheck){
    switch(projectParam){
    case PROJECT_MENAGER_COMPRESIBILITY_FACTOR:
        return project->getCompresibilityFactor();
    case PROJECT_MENAGER_FLOW:
        return project->getFlow();
    case PROJECT_MENAGER_MAX_DIFF_PRESSURE:
        return project->getMaxDiffPressure();
    case PROJECT_MENAGER_MAX_FLOW_VALUE:
        return project->getMaxFlowValue();
    case PROJECT_MENAGER_MAX_UPSTREAM_PRESSURE:
        return project->getMaxUpstreamPressure();
    case PROJECT_MENAGER_PIPE_DIAMETER:
        return project->getPipeDiameter();
    case PROJECT_MENAGER_PRESSURE_TAP_DIAMETER:
        return project->getPressureTapDiameter();
    case PROJECT_MENAGER_TEMP:
        return project->getTemp();
    case PROJECT_MENAGER_WORK_DENSITY:
        if(interpolatedValueCheck)
            return project->getFluidDensityFromFile();
        else
            return project->getFluidDensity();
    case PROJECT_MENAGER_WORK_DYNAMIC_VISCOSITY:
        if(interpolatedValueCheck)
            return project->getFluidDynamicViscosityFromFile();
        else
            return project->getFluidDynamicViscosity();
    case PROJECT_MENAGER_WORK_HEAT_CAPACITY_RATIO:
        return project->getFluidHeatCapacityRatio();
    default:
        return nullptr;
    }
}

void PromptElementDisplayDataAvailable::generateText(){
    QString str(QString("Przywróć poprzednią zapisaną lub zinterpolowaną wartość parametru \"") + ((projectParam == PROJECT_MENAGER_WORK_DENSITY)? "Gęstość\"" : "Współ. lepkości dynamicznej\"" ));
    if(expanded){
        uint newHeight = generalInfoLabel->fontMetrics().boundingRect(0,0, PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH, 1200, Qt::TextWordWrap, str).height();
        generalInfoLabel->resize(PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH, (newHeight < PROMPT_ELEMENT_BUTTON_HEIGHT)? PROMPT_ELEMENT_BUTTON_HEIGHT : newHeight);
        generalInfoLabel->setText(str);
    }else{
        generalInfoLabel->resize(PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH, PROMPT_ELEMENT_ERROR_LABEL_HEIGHT);
        generalInfoLabel->setText(generalInfoLabel->fontMetrics().elidedText(str,Qt::ElideRight, PROMPT_ELEMENT_GENERAL_INFO_LABEL_WIDTH));
    }
}

void PromptElementDisplayDataAvailable::reload(){
    disconnectAll();
    deleteWidgets();
    generateText();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

bool PromptElementDisplayDataAvailable::eventMatching(QObject *obj, QEvent *ev){
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
    if(obj == lastSavedValueButton){
         switch(ev->type()){
            case QEvent::MouseButtonRelease:
                lastSavedValueButtonReleased();
                break;
            case QEvent::Enter:
                lastSavedValueButton->setStyleSheet("font-family: \"Georgia\"; font-weight: 400;border-radius: 4px; border-color: rgba(190,190,190,0.6); border-width: 1px; background-color: rgba(240,240,240,0.6);");
             break;
         case QEvent::Leave:
             lastSavedValueButton->setStyleSheet("font-family: \"Georgia\"; font-weight: 400;border-radius: 4px; border-color: rgba(190,190,190,0.6); border-width: 1px; background-color: rgba(190,190,190,0.6);");
              break;
            default:
                break;
            }
         return true;
        }
        if(obj == interpolatedValueButton){
            switch(ev->type()){
            case QEvent::MouseButtonRelease:
                interpolatedValueButtonReleased();
                break;
            case QEvent::Enter:
                interpolatedValueButton->setStyleSheet("font-family: \"Georgia\"; font-weight: 400;border-radius: 4px; border-color: rgba(190,190,190,0.6); border-width: 1px; background-color: rgba(240,240,240,0.6);");
             break;
         case QEvent::Leave:
             interpolatedValueButton->setStyleSheet("font-family: \"Georgia\"; font-weight: 400;border-radius: 4px; border-color: rgba(190,190,190,0.6); border-width: 1px; background-color: rgba(190,190,190,0.6);");
              break;
            default:
                break;
        }
        return true;
    }
    return false;
}

void PromptElementDisplayDataAvailable::expandButtonReleased(){
    if(expanded)
        minimize();
    else
        expand();
    parent->reallocate();
}

void PromptElementDisplayDataAvailable::lastSavedValueButtonReleased(){
    element->getDataUTextEdit()->setText(checkValueExistance(false)->useStringFormat());
}

void PromptElementDisplayDataAvailable::interpolatedValueButtonReleased(){
    element->getDataUTextEdit()->setText(checkValueExistance(true)->useStringFormat());
    element->getDataUTextEdit()->setStyleSheet("");
    closeButtonReleased();
}

void PromptElementDisplayDataAvailable::expand(){
    expanded = true;
    expandButton->repaint();
    generateText();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

void PromptElementDisplayDataAvailable::minimize(){
    expanded = false;
    expandButton->repaint();
    generateText();
    setWindow();
    createLayout();
    disconnectAll();
    deleteWidgets();
}

void PromptElementDisplayDataAvailable::closeButtonReleased(){
    parent->deleteElement(this);
}

FormatableDataField<ProjectMenagerParam>* PromptElementDisplayDataAvailable::getFDF(){
    return element;
}

bool PromptElementDisplayDataAvailable::checkValidity(){
    return (!checkValueExistance(false) && !checkValueExistance(true));
}
