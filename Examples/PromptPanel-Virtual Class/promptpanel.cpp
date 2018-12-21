#include"promptpanel.hpp"
#include<QScrollBar>
#include"appwindow.hpp"
#include"promptpanelcatchevents.hpp"
#include"windowmacros.hpp"
#include"promptpanelminimizebutton.hpp"
#include"promptlist.hpp"
#include<QScrollArea>
#include"promptpanelmaximizebutton.hpp"
#include"promptelementdisplaydataavailable.hpp"
#include"promptelementdatanotsaved.hpp"
#include"promptelementdatanotreaded.hpp"
#include"promptelementlongstrings.hpp"
#include"formatabledatafield.hpp"
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
    delete catchEvents;
    catchEvents = nullptr;
}

void PromptPanel::init(){
    QFrame::setParent(parent);
    catchEvents = new PromptPanelCatchEvents(this);
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
    minimizeButton->installEventFilter(catchEvents);
    if(maximizeButton)
    maximizeButton->installEventFilter(catchEvents);
}

void PromptPanel::disconnectAll(){
    minimizeButton->removeEventFilter(catchEvents);
    if(maximizeButton)
    maximizeButton->removeEventFilter(catchEvents);
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

PromptPanelCatchEvents* PromptPanel::getCatchEvents(){
    return catchEvents;
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
                maximizeButton->installEventFilter(catchEvents);
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
     case PROMPT_TYPE_LONG_STRINGS:
         removePrompt(PROMPT_TYPE_LONG_STRINGS);
         if(*status == PROMPT_PANEL_HIDDEN)
             setStatus(PROMPT_PANEL_MINIMIZED);
         promptList->addElement(new PromptElementLongStrings(promptList, pt, str));
         break;
     default:
         break;
    }
}

void PromptPanel::addPrompt(PromptType pt, ProjectInfo *pi, ProjectMenagerParam pmp, FormatableDataField<ProjectMenagerParam> *fdf){
    if(*status == PROMPT_PANEL_HIDDEN)
        setStatus(PROMPT_PANEL_MINIMIZED);
    int index = -1;
    switch(pt){
    case PROMPT_TYPE_DISPLAY_DATA_AVAILABLE:
        if((index = checkPrompt(pt, pi, fdf)) == -1){
            promptList->addElement(new PromptElementDisplayDataAvailable(promptList, pt, pi, pmp, fdf));
            if(static_cast<PromptElementDisplayDataAvailable*>(*promptList->getPromptElements())->checkValidity())
                promptList->deleteElement((*promptList->getPromptElements()));
        }
        else
            (*(promptList->getPromptElements() + index))->reload();
        break;
    case PROMPT_TYPE_DATA_NOT_SAVED:
        promptList->addElement(new PromptElementDataNotSaved(promptList,pt, pi, pmp, fdf->getDataUTextEdit()->text()));
        break;
    case PROMPT_TYPE_DATA_NOT_READED:
        promptList->addElement(new PromptElementDataNotReaded(promptList,pt, pi, pmp, nullptr));
        break;
    default:
        break;
    }
}

int PromptPanel::checkPrompt(PromptType pt, ProjectInfo *pi, FormatableDataField<ProjectMenagerParam>* fdf){
    uint listSize = promptList->getNumbOfElements();
    PromptElement **element = promptList->getPromptElements();
    for(uint i = 0; i < listSize; element++, i++){
        if((*element)->getType() == pt && (*element)->getProjectInfo() == pi && static_cast<PromptElementDisplayDataAvailable*>((*element))->getFDF() == fdf){
            return i;
        }
    }
    return -1;
}

void PromptPanel::removePrompt(PromptType pt, ProjectInfo *pi, FormatableDataField<ProjectMenagerParam>* fdf){
    uint listSize = promptList->getNumbOfElements();
    PromptElement **element = promptList->getPromptElements();
    for(uint i = 0; i < listSize; element++, i++){
        if((*element)->getType() == pt && (*element)->getProjectInfo() == pi && static_cast<PromptElementDisplayDataAvailable*>((*element))->getFDF() == fdf){
            promptList->deleteElement(i);
            listSize--;
            i--;
        }
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

void PromptPanel::removePrompt(ProjectInfo *pi){
    uint listSize = promptList->getNumbOfElements();
    PromptElement **element = promptList->getPromptElements();
    for(uint i = 0; i < listSize; element++, i++){
        if((*element)->getProjectInfo() == pi){
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
        case PROMPT_TYPE_DATA_NOT_SAVED:
            numbOfWarnings++;
            break;
        case PROMPT_TYPE_DISPLAY_DATA_AVAILABLE:
            numbOfInfos++;
            break;
        case PROMPT_TYPE_LONG_STRINGS:
            numbOfInfos++;
            break;
        }
    }
    minimizeButton->setNumbOfInfos(numbOfInfos);
    minimizeButton->setNumbOfWarnings(numbOfWarnings);
}
