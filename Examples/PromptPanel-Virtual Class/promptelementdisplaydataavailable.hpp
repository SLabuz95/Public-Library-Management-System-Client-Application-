#ifndef PROMPTELEMENTDISPLAYDATAAVAILABLE_HPP
#define PROMPTELEMENTDISPLAYDATAAVAILABLE_HPP
#include"promptelement.hpp"

class PromptList;
template <typename ParamName> class FormatableData;
template <typename ParamName> class FormatableDataField;
class PromptElementDisplayDataAvailable : public PromptElement{
    Q_OBJECT
public:
    PromptElementDisplayDataAvailable(PromptList*, PromptType, ProjectInfo*, ProjectMenagerParam, FormatableDataField<ProjectMenagerParam>*);
    ~PromptElementDisplayDataAvailable();

private:
    // Parametr którego dotyczy komunikat
    ProjectMenagerParam projectParam = NONE_PARAM;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    // FormatableDataField do modyfikacji
    FormatableDataField<ProjectMenagerParam> *element = nullptr;

    // Sprawdzanie istnienia parametru projektu
    FormatableData<ProjectMenagerParam>* checkValueExistance(bool);

    // Generator tesktu (głównego i rozszerzonego dla nadklasy)
    void generateText();

    // Elementy dla wersji rozszerzonej (Expanded)
    QLabel *lastSavedValueButton = nullptr;
    QLabel *interpolatedValueButton = nullptr;

public:
    FormatableDataField<ProjectMenagerParam>* getFDF();
    bool checkValidity();
protected:
    // Funkcja przeładowania elementu
    void reload();

    bool eventMatching(QObject*, QEvent*);

    void expandButtonReleased();
    void closeButtonReleased();
    void lastSavedValueButtonReleased();
    void interpolatedValueButtonReleased();
    virtual void expand();
    virtual void minimize();
};


#endif // PROMPTELEMENTDISPLAYDATAAVAILABLE_HPP
