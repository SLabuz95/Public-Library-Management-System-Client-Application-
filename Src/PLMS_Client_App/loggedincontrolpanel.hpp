#ifndef LOGGEDINCONTROLPANEL_HPP
#define LOGGEDINCONTROLPANEL_HPP
#include<QFrame>
#include"loggedincontrolpanellibrarianfunc.hpp"
#include"loggedincontrolpanelreaderfunc.hpp"
#include"loggedinpaneladminfunc.hpp"

class AppWindowLoggedInPanel;
class QLabel;
class LoggedInControlPanel : public QFrame
{
public:
    LoggedInControlPanel(AppWindowLoggedInPanel* parent);
    ~LoggedInControlPanel();

private:
    AppWindowLoggedInPanel* parent = nullptr;

    QLabel* elements = nullptr;
    uint activeIndex = 0;

    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

public:
    uint getActiveIndex();
    void setActiveIndex(uint);
    QLabel* getElements();
    void reload();

    bool eventMatching(QObject* obj, QEvent* ev);
};

#endif // LOGGEDINCONTROLPANEL_HPP
