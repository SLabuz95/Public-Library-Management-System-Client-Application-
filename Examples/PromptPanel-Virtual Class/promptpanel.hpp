#ifndef PROMPTPANEL_HPP
#define PROMPTPANEL_HPP

#include<QFrame>
#include"prompttypeenum.hpp"
#include"promptpanelstatusenum.hpp"
#include"projectmenagerparamenum.hpp"
class QScrollArea;
class ProjectInfo;
class AppWindow;
class PromptElement;
class PromptElementDisplayDataAvailable;
class PromptElementLongStrings;
class PromptElementDataNotSaved;
class PromptElementDataNotReaded;
class PromptPanelCatchEvents;
class PromptPanelMaximizeButton;
class PromptPanelMinimizeButton;
class PromptList;
template <typename ParamName> class FormatableDataField;
class PromptPanel : public QFrame{
public:
    // Konstruktor
    PromptPanel(AppWindow*);

    // Destruktor
    ~PromptPanel();

private:
    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    AppWindow *parent = nullptr;
    PromptPanelCatchEvents *catchEvents = nullptr;
    PromptPanelMaximizeButton *maximizeButton = nullptr;
    PromptPanelMinimizeButton *minimizeButton = nullptr;
    QScrollArea *promptSA = nullptr;
    PromptList *promptList = nullptr;
    PromptPanelStatus *status = nullptr;

public:
    PromptPanelMaximizeButton* getMaximizeButton();
    PromptPanelMinimizeButton* getMinimizeButton();
    PromptList* getPromptList();
    PromptPanelCatchEvents* getCatchEvents();
    PromptPanelStatus* getStatus();
    void setStatus(PromptPanelStatus);
    void reload(bool);

    void addPrompt(PromptType, ProjectInfo*, ProjectMenagerParam, FormatableDataField<ProjectMenagerParam>*);
    void addPrompt(PromptType, QString);
    int checkPrompt(PromptType, ProjectInfo*, FormatableDataField<ProjectMenagerParam>*);
    void removePrompt(PromptType, ProjectInfo*, FormatableDataField<ProjectMenagerParam>*);
    void removePrompt(PromptType);
    void removePrompt(ProjectInfo*);
    void writeNumbOfPrompts();
};

#endif // PROMPTPANEL_HPP
