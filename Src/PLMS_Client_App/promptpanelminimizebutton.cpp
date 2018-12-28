#include"promptpanelminimizebutton.hpp"
#include"promptpanel.hpp"
#include<QLabel>
#include"windowmacros.hpp"

PromptPanelMinimizeButton::PromptPanelMinimizeButton(PromptPanel *parent)
    : parent(parent)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

PromptPanelMinimizeButton::~PromptPanelMinimizeButton(){
    disconnectAll();
    deleteWidgets();
}

void PromptPanelMinimizeButton::init(){
    QFrame::setParent(parent);
}

void PromptPanelMinimizeButton::setWindow(){
    setStyleSheet("background-color: rgba(245, 245, 245, 0.4);");
}

void PromptPanelMinimizeButton::createWidgets(){
    arrowPixmap = new QLabel(this);
    warningPixmap = new QLabel(this);
    numberOfWarnings = new QLabel(this);
    informationPixmap = new QLabel(this);
    numberOfInformations = new QLabel(this);
}

void PromptPanelMinimizeButton::createLayout(){
    repaint();
    arrowPixmap->setScaledContents(true);
    arrowPixmap->setAlignment(Qt::AlignCenter);
    arrowPixmap->setGeometry(PROMPT_PANEL_MINIMIZE_BUTTON_ARROW_X,PROMPT_PANEL_MINIMIZE_BUTTON_ARROW_Y,PROMPT_PANEL_MINIMIZE_BUTTON_ARROW_WIDTH, PROMPT_PANEL_MINIMIZE_BUTTON_ARROW_HEIGHT);
    arrowPixmap->show();
    informationPixmap->setScaledContents(true);
    informationPixmap->setAlignment(Qt::AlignCenter);
    informationPixmap->setGeometry(PROMPT_PANEL_MINIMIZE_BUTTON_WARNING_ICON_X,PROMPT_PANEL_MINIMIZE_BUTTON_WARNING_ICON_Y,PROMPT_PANEL_MINIMIZE_BUTTON_INFO_WIDTH,PROMPT_PANEL_MINIMIZE_BUTTON_INFO_HEIGHT);
    informationPixmap->setPixmap(PROMPT_PANEL_MINIMIZE_BUTTON_INFO_ICON);
    informationPixmap->show();
    numberOfInformations->setGeometry(PROMPT_PANEL_MINIMIZE_BUTTON_WARNING_NUMB_X, PROMPT_PANEL_MINIMIZE_BUTTON_WARNING_NUMB_Y,PROMPT_PANEL_MINIMIZE_BUTTON_INFO_WIDTH, PROMPT_PANEL_MINIMIZE_BUTTON_INFO_HEIGHT);
    numberOfInformations->setAlignment(Qt::AlignCenter);
    numberOfInformations->setText("0");
    numberOfInformations->show();
    warningPixmap->setScaledContents(true);
    warningPixmap->setAlignment(Qt::AlignCenter);
    warningPixmap->setGeometry(PROMPT_PANEL_MINIMIZE_BUTTON_ERROR_ICON_X,PROMPT_PANEL_MINIMIZE_BUTTON_ERROR_ICON_Y,PROMPT_PANEL_MINIMIZE_BUTTON_INFO_WIDTH, PROMPT_PANEL_MINIMIZE_BUTTON_INFO_HEIGHT);
    warningPixmap->setPixmap(PROMPT_PANEL_MINIMIZE_BUTTON_ERROR_ICON);
    warningPixmap->show();
    numberOfWarnings->setGeometry(PROMPT_PANEL_MINIMIZE_BUTTON_ERROR_NUMB_X,PROMPT_PANEL_MINIMIZE_BUTTON_ERROR_NUMB_Y,PROMPT_PANEL_MINIMIZE_BUTTON_INFO_WIDTH,PROMPT_PANEL_MINIMIZE_BUTTON_INFO_HEIGHT);
    numberOfWarnings->setAlignment(Qt::AlignCenter);
    numberOfWarnings->setText("0");
    numberOfWarnings->show();
}

void PromptPanelMinimizeButton::deleteWidgets(){
    delete arrowPixmap;
    arrowPixmap = nullptr;
    delete warningPixmap;
    warningPixmap = nullptr;
    delete numberOfWarnings;
    numberOfWarnings = nullptr;
    delete informationPixmap;
    informationPixmap = nullptr;
    delete numberOfInformations;
    numberOfInformations = nullptr;
}

void PromptPanelMinimizeButton::connectAll(){
    // Brak
}

void PromptPanelMinimizeButton::disconnectAll(){
    // Brak
}

PromptPanel* PromptPanelMinimizeButton::getParent(){
    return parent;
}

QLabel* PromptPanelMinimizeButton::getNumberOfWarnings(){
    return numberOfWarnings;
}

QLabel* PromptPanelMinimizeButton::getNumberOfInformations(){
    return numberOfInformations;
}

void PromptPanelMinimizeButton::setNumbOfWarnings(uint numb){
    numberOfWarnings->setText(QString::number(numb));
}

void PromptPanelMinimizeButton::setNumbOfInfos(uint numb){
    numberOfInformations->setText(QString::number(numb));
}

void PromptPanelMinimizeButton::repaint(){
    switch(*parent->getStatus()){
    case PROMPT_PANEL_HIDDEN:
        arrowPixmap->setPixmap(PROMPT_PANEL_MINIMIZE_BUTTON_UP_EXTEND_ARROW_ICON);
        break;
    default:
        arrowPixmap->setPixmap(PROMPT_PANEL_MINIMIZE_BUTTON_DOWN_EXTEND_ARROW_ICON);
        break;
    }
}


