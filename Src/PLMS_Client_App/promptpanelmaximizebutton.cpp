#include"promptpanelmaximizebutton.hpp"
#include<QMatrix>
#include"promptpanel.hpp"
#include"windowmacros.hpp"
#include<QLabel>

PromptPanelMaximizeButton::PromptPanelMaximizeButton(PromptPanel *parent){
    this->parent = parent;
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

PromptPanelMaximizeButton::~PromptPanelMaximizeButton(){
    disconnectAll();
    deleteWidgets();
}

void PromptPanelMaximizeButton::init(){
    QFrame::setParent(parent);
}

void PromptPanelMaximizeButton::setWindow(){
    // Brak
}

void PromptPanelMaximizeButton::createWidgets(){
    arrowPixmap = new QLabel(this);
}

void PromptPanelMaximizeButton::createLayout(){
    repaint();
    arrowPixmap->setScaledContents(true);
    arrowPixmap->setAlignment(Qt::AlignCenter);
    arrowPixmap->setGeometry(PROMPT_PANEL_MAXIMIZE_BUTTON_ARROW_X,PROMPT_PANEL_MAXIMIZE_BUTTON_ARROW_Y,PROMPT_PANEL_MAXIMIZE_BUTTON_ARROW_WIDTH,PROMPT_PANEL_MAXIMIZE_BUTTON_ARROW_HEIGHT);
    arrowPixmap->show();
}

void PromptPanelMaximizeButton::deleteWidgets(){
    delete arrowPixmap;
    arrowPixmap = nullptr;
}

void PromptPanelMaximizeButton::connectAll(){
    // Brak
}

void PromptPanelMaximizeButton::disconnectAll(){
    // Brak
}

PromptPanel* PromptPanelMaximizeButton::getParent(){
    return parent;
}

void PromptPanelMaximizeButton::repaint(){
    switch(*parent->getStatus()){
    case PROMPT_PANEL_MAXIMIZED:
        arrowPixmap->setPixmap(PROMPT_PANEL_MAXIMIZE_BUTTON_DOWN_EXTEND_ARROW_ICON);
        break;
    case PROMPT_PANEL_MINIMIZED:
        arrowPixmap->setPixmap(PROMPT_PANEL_MAXIMIZE_BUTTON_UP_EXTEND_ARROW_ICON);
        break;
    default:
        break;
    }
}
