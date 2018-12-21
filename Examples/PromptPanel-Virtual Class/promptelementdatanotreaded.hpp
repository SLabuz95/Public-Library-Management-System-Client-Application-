#ifndef PROMPTELEMENTDATANOTREADED_HPP
#define PROMPTELEMENTDATANOTREADED_HPP

#include"promptelement.hpp"

class PromptList;
template <typename ParamName> class FormatableData;
template <typename ParamName> class FormatableDataField;
class PromptElementDataNotReaded : public PromptElement{
    Q_OBJECT
public:
    PromptElementDataNotReaded(PromptList*, PromptType, ProjectInfo*, ProjectMenagerParam, QString);
    ~PromptElementDataNotReaded();

private:
    // Parametr którego dotyczy komunikat
    ProjectMenagerParam projectParam = NONE_PARAM;

    // Błędna wartość parametru
    QString wrongData;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    // Sprawdzanie istnienia parametru projektu
    QString getParamName();

    // Generator tesktu (głównego i rozszerzonego dla nadklasy)
    void generateText();

protected:
    // Funkcja przeładowania elementu
    void reload();

    bool eventMatching(QObject*, QEvent*);

    void expandButtonReleased();
    void closeButtonReleased();
    virtual void expand();
    virtual void minimize();
};

#endif // PROMPTELEMENTDATANOTREADED_HPP
