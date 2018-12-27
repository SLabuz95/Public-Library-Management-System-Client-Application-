#include"promptpanel.hpp"
#include<QScrollBar>
#include"appwindow.hpp"
#include"windowmacros.hpp"
#include"promptpanelminimizebutton.hpp"
#include"promptlist.hpp"
#include<QScrollArea>
#include"promptpanelmaximizebutton.hpp"
#include"promptelement.hpp"
#include<QLineEdit>

PromptPanel::PromptPanel(AppWindow *parent)
    :parent(parent)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    setStyleSheet("background-color: rgba(245, 245, 245, 0.4);");
}

PromptPanel::~PromptPanel(){
    disconnectAll();
    deleteWidgets();    
}

void PromptPanel::init(){
    QFrame::setParent(parent);
    status = new PromptPanelStatus[2];
    *status = PROMPT_PANEL_HIDDEN;
    *(status + 1) = PROMPT_PANEL_MINIMIZED;
}

void PromptPanel::setWindow(){
    switch(*status){
    case PROMPT_PANEL_HIDDEN:
        setGeometry(0, APP_WINDOW_HEIGHT - STATUS_BAR_HEIGHT - PROMPT_PANEL_MAXIMIZE_BUTTON_LABEL_HEIGHT, PROMPT_PANEL_WIDTH, PROMPT_PANEL_MAXIMIZE_BUTTON_LABEL_HEIGHT);
        break;
    case PROMPT_PANEL_MAXIMIZED:
        setGeometry(0,MENU_BAR_HEIGHT + TOOL_BAR_HEIGHT,PROMPT_PANEL_WIDTH, APP_WINDOW_HEIGHT - MENU_BAR_HEIGHT - TOOL_BAR_HEIGHT - STATUS_BAR_HEIGHT);
        break;
    case PROMPT_PANEL_MINIMIZED:
        setGeometry(0,APP_WINDOW_HEIGHT - PROMPT_PANEL_DEFAULT_HEIGHT - STATUS_BAR_HEIGHT,PROMPT_PANEL_WIDTH, PROMPT_PANEL_DEFAULT_HEIGHT);
        break;
    }
}

void PromptPanel::createWidgets(){
    switch(*status){
    case PROMPT_PANEL_HIDDEN:
        if(!minimizeButton)
        minimizeButton = new PromptPanelMinimizeButton(this);
        break;
    default:        
        if(!maximizeButton)
        maximizeButton = new PromptPanelMaximizeButton(this);
    }
    if(!promptSA){
        promptSA = new QScrollArea(this);
        promptSA->hide();
    }
    if(!promptList)
        promptList = new PromptList(this);
}

void PromptPanel::createLayout(){
switch(*status){
    default:
        promptList->move(0, PROMPT_PANEL_MAXIMIZE_BUTTON_LABEL_HEIGHT);
        promptSA->setStyleSheet("background-color: transparent");
        promptSA->verticalScrollBar()->setStyleSheet("QScrollBar::vertical{background: transparent; width: 5px;} QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical, QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical, QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{border: none; background: none; color: none;} QScrollBar::handle:vertical{background-color: white; border: 1px solid black;}");
        promptSA->setFrameShape(QFrame::NoFrame);
        promptSA->setWidget(promptList);
        promptSA->setGeometry(0, PROMPT_PANEL_MAXIMIZE_BUTTON_LABEL_HEIGHT,PROMPT_LIST_WIDTH, this->height() - 25 - 25);
        promptSA->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        promptSA->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        promptSA->show();
        maximizeButton->move(0, 0);
        maximizeButton->show();
    case PROMPT_PANEL_HIDDEN:
        minimizeButton->move(0,this->height() - PROMPT_PANEL_MAXIMIZE_BUTTON_LABEL_HEIGHT);
        minimizeButton->show();
    break;
    }
}

void PromptPanel::deleteWidgets(){
    delete minimizeButton;
    delete maximizeButton;
    delete promptList;
    delete promptSA;
}

void PromptPanel::connectAll(){
    minimizeButton->installEventFilter(this);
    if(maximizeButton)
    maximizeButton->installEventFilter(this);
}

void PromptPanel::disconnectAll(){
    minimizeButton->removeEventFilter(this);
    if(maximizeButton)
    maximizeButton->removeEventFilter(this);
}

PromptPanelMaximizeButton* PromptPanel::getMaximizeButton(){
    return maximizeButton;
}

PromptPanelMinimizeButton* PromptPanel::getMinimizeButton(){
    return minimizeButton;
}

PromptList* PromptPanel::getPromptList(){
    return promptList;
}

PromptPanelStatus* PromptPanel::getStatus(){
    return status;
}

void PromptPanel::setStatus(PromptPanelStatus set){
    WINDOW_STATUS_SAVE(status)
    *status = set;
    reload(false);
}

void PromptPanel::reload(bool reloadSA){
    if(reloadSA){
        setWindow();
        createLayout();
    }else{
        switch(*(status + 1)){
        case PROMPT_PANEL_HIDDEN:
            switch (*status) {
            case PROMPT_PANEL_HIDDEN:
                break;
            default:
                setWindow();
                createWidgets();
                createLayout();
                maximizeButton->installEventFilter(this);
                minimizeButton->repaint();
                promptSA->show();
                break;
            }
            break;
        default:
            switch(*status){
            case PROMPT_PANEL_HIDDEN:
                delete maximizeButton;
                maximizeButton = nullptr;
                promptSA->hide();
                setWindow();
                createLayout();
                minimizeButton->repaint();
                break;
            default:
                setWindow();
                createLayout();
                maximizeButton->repaint();
                break;
            }
        }
    }
    show();
}

void PromptPanel::addPrompt(PromptType pt, QString str){
     if(*status == PROMPT_PANEL_HIDDEN)
         setStatus(PROMPT_PANEL_MINIMIZED);
     switch(pt){
     // _CHECK_PH_
     default:
         break;
    }
}

void PromptPanel::removePrompt(PromptType pt){
    uint listSize = promptList->getNumbOfElements();
    PromptElement **element = promptList->getPromptElements();
    for(uint i = 0; i < listSize; element++, i++){
        if((*element)->getType() == pt){
            promptList->deleteElement(i);
            listSize--;
            i--;
        }
    }
}

void PromptPanel::writeNumbOfPrompts(){
    uint listSize = promptList->getNumbOfElements();
    uint numbOfInfos = 0;
    uint numbOfWarnings = 0;
    for(uint i = 0; i < listSize; i++){
        switch((*(promptList->getPromptElements() + i))->getType()){
        // _CHECK_PH_ Add warnings and error types
        }
    }
    minimizeButton->setNumbOfInfos(numbOfInfos);
    minimizeButton->setNumbOfWarnings(numbOfWarnings);
}
