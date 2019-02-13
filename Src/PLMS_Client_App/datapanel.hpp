#ifndef DATAPANEL_HPP
#define DATAPANEL_HPP
#include<QFrame>
#include"datapanelmode.hpp"
#include"mainmacros.hpp"
#include"windowmacros.hpp"

class DataPanel : public QFrame{
    Q_OBJECT
public:
    DataPanel(void* parent, DataPanelMode mode);
    ~DataPanel();

protected:
    // Parent
    void *parent = nullptr;

    DataPanelMode mode = REGISTER_MODE;

    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

public:
    // Get Functions
    void* getParent();
    DataPanelMode getMode();

    // -----------------
    // Set Functions

    // -----------------
    bool eventFilter(QObject* obj, QEvent* ev);

    virtual void reload(){}
    virtual bool eventMatching(QObject*, QEvent*){return true;}
    virtual void changeMode(DataPanelMode){}
};

#endif // DATAPANEL_HPP
