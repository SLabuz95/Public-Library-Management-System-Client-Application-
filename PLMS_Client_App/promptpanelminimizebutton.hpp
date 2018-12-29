#ifndef PROMPTPANELMINIMIZEBUTTON_HPP
#define PROMPTPANELMINIMIZEBUTTON_HPP
// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>
// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class QLabel;
class PromptPanel;
// ----------------------------------------------------------------------

// ------------------ PromptPanelMinimizeButton Class ------------------------------------


class PromptPanelMinimizeButton : public QFrame{
    Q_OBJECT
public:
    PromptPanelMinimizeButton(PromptPanel*);
    ~PromptPanelMinimizeButton();

private:
    // Parent
    PromptPanel *parent = nullptr;

    // Elementy
    QLabel *serverStatusLabel = nullptr;
    QLabel *arrowPixmap = nullptr;
    QLabel *warningPixmap = nullptr;
    QLabel *numberOfWarnings = nullptr;
    QLabel *informationPixmap = nullptr;
    QLabel *numberOfInformations = nullptr;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

public:
    // Funkcje Get / Set
    QLabel* getNumberOfWarnings();
    QLabel* getNumberOfInformations();
    void setNumbOfWarnings(uint);
    void setNumbOfInfos(uint);
    PromptPanel* getParent();
    void setServerStatus(QString);

    // Funkcja odświeżenia informacji na podstawie stanu rodzica
    void repaint();    
};

#endif // PROMPTPANELMINIMIZEBUTTON_HPP
