#ifndef PROMPTELEMENT_HPP
#define PROMPTELEMENT_HPP
#include<QFrame>
#include"projectmenagerparamenum.hpp"
#include"prompttypeenum.hpp"
class ProjectInfo;
class QLabel;
class PromptElementDisplayDataAvailable;
class PromptElementExpandButton;
class PromptList;
class PromptElement : public QFrame{

public:
    PromptElement(PromptList*, PromptType, ProjectInfo*);
    virtual ~PromptElement();

protected:
    // Parent
    PromptList *parent = nullptr;

    // Adres Projektu (ProjectInfo)
    ProjectInfo *project = nullptr;

    // Typ
    PromptType type = PROMPT_TYPE_DEFAULT;

    // Czy element jest rozwinięty (Wszystko jest widoczne)
    bool expanded = false;

    // Elementy dla wersji podstawowej
    PromptElementExpandButton *expandButton = nullptr;
    QLabel *closeButton = nullptr;
    QLabel *errorTypeLabel = nullptr;
    QLabel *generalInfoLabel = nullptr;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    // Funkcje sterowania widokiem okna
    virtual void expand(){}
    virtual void minimize(){}

public:
    PromptElementExpandButton* getExpandButton();
    QLabel* getCloseButton();
    QLabel* getGeneralInfoLabel();
    ProjectInfo* getProjectInfo();
    uint textHeight = 0;
    PromptList* getParent();

    bool isExpanded();
    PromptType getType();

    virtual void reload(){}
    virtual void generateText(){}
    virtual bool eventMatching(QObject*, QEvent*){return true;}

    virtual void closeButtonReleased(){}
    virtual void expandButtonReleased(){}
};

#endif // PROMPTELEMENT_HPP
