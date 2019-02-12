#include"filteredlist.hpp"
#include"filterpanel.hpp"
#include"operationlist.hpp"
#include"operationpanelfilteredlist.hpp"
#include<QEvent>

FilteredList::FilteredList(OperationPanelFilteredList *parent, FileType filterType)
    : QFrame(parent), parent(parent), filterType(filterType)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    setStyleSheet("FilteredList{background-color: transparent;}");
}

FilteredList::~FilteredList(){
    disconnectAll();
    deleteWidgets();
}

void FilteredList::init(){
    // Empty
}

void FilteredList::setWindow(){
    resize(FILTERED_LIST_WIDTH, FILTERED_LIST_HEIGHT);
}

void FilteredList::createWidgets(){
    // Filter Panel
    SET_PTR_DO(filterPanel, new FilterPanel(this));

    // Operation Panel
    SET_PTR_DO(operationList, new OperationList(this));
    filterPanel->show();
    operationList->show();
}

void FilteredList::createLayout(){
    // Operation List
    if(operationList && filterPanel){
        operationList->move(0, filterPanel->height());
        resize(FILTERED_LIST_WIDTH, filterPanel->height() + operationList->height());
    }
}

void FilteredList::deleteWidgets(){
    SET_PTR_DO(filterPanel, nullptr);
    SET_PTR_DO(operationList, nullptr);
}

void FilteredList::connectAll(){
    // Empty
}

void FilteredList::disconnectAll(){
    // Empty
}

OperationPanelFilteredList* FilteredList::getParent(){
    return parent;
}

void FilteredList::reload(bool reloadSA){
    if(reloadSA){
        setWindow();
        createLayout();
    }else{
        setWindow();
        createWidgets();
        createLayout();
    }
    show();
}

bool FilteredList::eventFilter(QObject *obj, QEvent *ev){
    switch(ev->type()){
    case QEvent::MouseButtonRelease:
    case QEvent::Enter:
    case QEvent::Leave:
    case QEvent::KeyPress:
        if(filterPanel && filterPanel->eventMatching(obj, ev))
            return true;
        if(operationList && operationList->eventMatching(obj, ev))
            return true;
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, ev);
}

FileType FilteredList::getFilterType(){
    return filterType;
}
