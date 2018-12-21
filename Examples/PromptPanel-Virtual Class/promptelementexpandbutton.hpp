#ifndef PROMPTPANELEXPANDELEMENTBUTTON_HPP
#define PROMPTPANELEXPANDELEMENTBUTTON_HPP
#include<QFrame>
class QLabel;
class PromptElement;
class PromptElementExpandButton : public QFrame{
public:
    PromptElementExpandButton(PromptElement*);
    ~PromptElementExpandButton();

private:
    // Parent
    PromptElement *parent = nullptr;

    // Elementy
    QLabel *expandPixmap = nullptr;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    // Funkcje Get / Set
public:
    PromptElement* getParent();
    void repaint();
};


#endif // PROMPTPANELEXPANDELEMENTBUTTON_HPP
