#ifndef OPERATIONLISTELEMENTBOOKLOG_HPP
#define OPERATIONLISTELEMENTBOOKLOG_HPP

#include"operationlistelement.hpp"
class BookLog;
class OperationList;
class OperationListElementBookLog : public OperationListElement{
    Q_OBJECT
public:
    OperationListElementBookLog(OperationList*, BookLog*);
    ~OperationListElementBookLog();

private:
    BookLog* bookLog = nullptr;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    // Generator tesktu (głównego i rozszerzonego dla nadklasy)
    void generateText();

protected:
    // Funkcja przeładowania elementu
    void reload();

    bool eventMatching(QObject*, QEvent*);

};

#endif // OPERATIONLISTELEMENTBOOKLOG_HPP
