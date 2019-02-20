#ifndef OPERATIONLISTELEMENT_HPP
#define OPERATIONLISTELEMENT_HPP

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

// ------------------ OperationListElement Class ------------------------------------

class OperationListElement : public QFrame{
    Q_OBJECT
public:
    // Constructor
    OperationListElement(OperationList*);

    // Destructor
    virtual ~OperationListElement();

protected:
    // Parent
    OperationList *parent = nullptr;

    // Virtual Element's widgets
    QLabel numberLabel;
    QLabel generalInfoLabel;

    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

public:
    // Get Functions
    QLabel& getGeneralInfoLabel();
    QLabel& getNumberLabel();
    uint textHeight = 0;
    OperationList* getParent();

    // Set Functions

    // -----------------

    virtual void reload(bool repaint){
        if(repaint){
            setWindow();
            createLayout();
        }else{
            setWindow();
            createWidgets();
            createLayout();

        }
    }
    virtual void generateText(){}
    virtual bool eventMatching(QObject*, QEvent*){return true;}

};


#endif // OPERATIONLISTELEMENT_HPP
