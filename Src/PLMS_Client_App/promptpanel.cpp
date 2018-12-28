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
#include<QEvent>

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
        setGeometry(PROMPT_PANEL_HIDDEN_X, PROMPT_PANEL_HIDDEN_Y, PROMPT_PANEL_HIDDEN_WIDTH, PROMPT_PANEL_HIDDEN_HEIGHT);
        break;
    case PROMPT_PANEL_MAXIMIZED:
        setGeometry(PROMPT_PANEL_MAXIMIZE_X,PROMPT_PANEL_MAXIMIZE_Y,PROMPT_PANEL_MAXIMIZE_WIDTH, PROMPT_PANEL_MAXIMIZE_HEIGHT);
        break;
    case PROMPT_PANEL_MINIMIZED:
        setGeometry(PROMPT_PANEL_MINIMIZE_X,PROMPT_PANEL_MINIMIZE_Y,PROMPT_PANEL_MINIMIZE_WIDTH, PROMPT_PANEL_MINIMIZE_HEIGHT);
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
        promptList->move(PROMPT_LIST_X, PROMPT_PANEL_MAXIMIZE_Y);
        promptSA->setStyleSheet("background-color: transparent");
        promptSA->verticalScrollBar()->setStyleSheet("QScrollBar::vertical{background: transparent; width: 5px;} QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical, QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical, QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{border: none; background: none; color: none;} QScrollBar::handle:vertical{background-color: white; border: 1px solid black;}");
        promptSA->setFrameShape(QFrame::NoFrame);
        promptSA->setWidget(promptList);
        promptSA->setGeometry(PROMPT_LIST_SA_X, PROMPT_LIST_SA_Y,PROMPT_LIST_SA_WIDTH, PROMPT_LIST_SA_HEIGHT);
        promptSA->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        promptSA->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        promptSA->show();
        maximizeButton->move(0, 0);
        maximizeButton->show();
    case PROMPT_PANEL_HIDDEN:
        minimizeButton->move(PROMPT_PANEL_MINIMIZE_BUTTON_X,PROMPT_PANEL_MINIMIZE_BUTTON_Y);
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

void PromptPanel::setServerStatusNoConnection(){
    minimizeButton->setServerStatus(SERVER_STATUS_NO_CONNECTION_TEXT);
}

void PromptPanel::setServerStatusConnection(){
    minimizeButton->setServerStatus(SERVER_STATUS_CONNECTION_TEXT);
}

void PromptPanel::setServerStatusInitalization(){
    minimizeButton->setServerStatus(SERVER_STATUS_INITIALIZATION_TEXT);
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

bool PromptPanel::eventFilter(QObject* obj, QEvent* ev){
    switch(*status){
    case PROMPT_PANEL_HIDDEN:
        switch(ev->type()){
        case QEvent::MouseButtonRelease:
            if(obj == minimizeButton){
                setStatus(*(status + 1));
                return true;
            }
            break;
        default:
            break;
        }
        break;
    case PROMPT_PANEL_MAXIMIZED:
        switch(ev->type()){
        case QEvent::MouseButtonRelease:
            if(obj == maximizeButton){
                setStatus(PROMPT_PANEL_MINIMIZED);
                return true;
            }
            if(obj == minimizeButton){
                setStatus(PROMPT_PANEL_HIDDEN);
                return true;
            }
            promptList->matchEvents(obj, ev);
            return true;
            break;
        default:
            break;
        }
        break;
    case PROMPT_PANEL_MINIMIZED:
        switch(ev->type()){
        case QEvent::MouseButtonRelease:
            if(obj == maximizeButton){
                setStatus(PROMPT_PANEL_MAXIMIZED);
                return true;
            }
            if(obj == minimizeButton){
                setStatus(PROMPT_PANEL_HIDDEN);
                break;
            }
            promptList->matchEvents(obj, ev);
            return true;
        default:
            break;
        }
            break;
        default:
            break;
    }
    return QObject::eventFilter(obj,ev);
}
