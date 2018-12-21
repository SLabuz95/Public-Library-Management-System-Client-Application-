#ifndef PROMPTPANELMAXIMIZEBUTTON_HPP
#define PROMPTPANELMAXIMIZEBUTTON_HPP
#include<QFrame>

class PromptPanel;
class QLabel;
class PromptPanelMaximizeButton : public QFrame{
    Q_OBJECT
public:
    PromptPanelMaximizeButton(PromptPanel*);
    ~PromptPanelMaximizeButton();

private:
    // Parent
    PromptPanel *parent = nullptr;

    // Elementy
    QLabel *arrowPixmap = nullptr;

protected:
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
    PromptPanel* getParent();

    void repaint();
};

#endif // PROMPTPANELMAXIMIZEBUTTON_HPP
