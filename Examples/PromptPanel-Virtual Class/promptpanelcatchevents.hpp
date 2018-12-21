#ifndef PROMPTPANELCATCHEVENTS_HPP
#define PROMPTPANELCATCHEVENTS_HPP
#include<QObject>

class PromptPanel;
class PromptPanelCatchEvents : public QObject{
public:
    //Konstruktor
    PromptPanelCatchEvents(PromptPanel*);
    ~PromptPanelCatchEvents();
private:
    // Parent
    PromptPanel* parent = nullptr;
protected:
    bool eventFilter(QObject*, QEvent*);
};

#endif // PROMPTPANELCATCHEVENTS_HPP
