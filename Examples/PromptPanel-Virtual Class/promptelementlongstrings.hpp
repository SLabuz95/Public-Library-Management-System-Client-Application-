#ifndef PROMPTELEMENTLONGSTRINGS_HPP
#define PROMPTELEMENTLONGSTRINGS_HPP

#include"promptelement.hpp"

class PromptList;
template <typename ParamName> class FormatableData;
template <typename ParamName> class FormatableDataField;
class PromptElementLongStrings : public PromptElement{
    Q_OBJECT
public:
    PromptElementLongStrings(PromptList*, PromptType, QString);
    ~PromptElementLongStrings();

private:
    QString text;

    // Funkcje zarządzania działaniem konstuktora
    void init(QString&);
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();


    // Generator tesktu (głównego i rozszerzonego dla nadklasy)
    void generateText();
    void generateText(QString&);

protected:
    // Funkcja przeładowania elementu
    void reload();

    bool eventMatching(QObject*, QEvent*);

    void expandButtonReleased();
    void closeButtonReleased();
    virtual void expand();
    virtual void minimize();
};

#endif // PROMPTELEMENTLONGSTRINGS_HPP
