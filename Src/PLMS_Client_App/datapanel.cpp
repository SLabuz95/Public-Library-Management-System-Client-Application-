#include"datapanel.hpp"


DataPanel::DataPanel(void *parent, DataPanelMode mode)
    : QFrame(static_cast<QWidget*>(parent)), parent(parent), mode(mode){
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    setStyleSheet("DataPanel{background-color: transparent;}");
}

DataPanel::~DataPanel(){
    disconnectAll();
    deleteWidgets();
}

void DataPanel::init(){
    // Empty
}

void DataPanel::setWindow(){
    // Empty
}

void DataPanel::createWidgets(){
    // Empty
}

void DataPanel::createLayout(){
    // Empty
}

void DataPanel::deleteWidgets(){
    // EMPTY
}

void DataPanel::connectAll(){
    // Empty
}

void DataPanel::disconnectAll(){
    // Empty
}

void* DataPanel::getParent(){
    return parent;
}

DataPanelMode DataPanel::getMode(){
    return mode;
}

bool DataPanel::eventFilter(QObject *obj, QEvent *ev){
    return eventMatching(obj, ev);
}
