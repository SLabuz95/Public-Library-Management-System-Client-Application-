#ifndef CONTROLBAR_HPP
#define CONTROLBAR_HPP

// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>
#include<QLabel>
// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class QLabel;
class OperationList;
// ----------------------------------------------------------------------

// ------------------ ControlBar Class ------------------------------------


class ControlBar : public QFrame{
    Q_OBJECT
public:
    ControlBar(OperationList*, bool, uint);
    ~ControlBar();

private:
    // Parent
    OperationList *parent = nullptr;

    // Elementy
    QLabel leftArrowLabel;
    QLabel rightArrowLabel;
    QLabel pageNumberLabel;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    void leftArrowButtonPressed();
    void rightArrowButtonPressed();
public:
    // Funkcje Get / Set
    OperationList* getParent();

    bool eventMatching(QObject* obj, QEvent* ev);
    // Funkcja odświeżenia informacji na podstawie stanu rodzica
    void repaint(bool, uint);
};

#endif // CONTROLBAR_HPP
