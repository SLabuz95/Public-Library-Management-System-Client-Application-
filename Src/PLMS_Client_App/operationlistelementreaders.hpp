#ifndef OPERATIONLISTELEMENTREADERS_HPP
#define OPERATIONLISTELEMENTREADERS_HPP

#include"operationlistelement.hpp"

class User;
class OperationList;
class OperationListElementReaders : public OperationListElement{
    Q_OBJECT
public:
    OperationListElementReaders(OperationList*, User*);
    ~OperationListElementReaders();

private:
    QLabel bookMenagerButton;
    QLabel readerDataButton;
    User* user = nullptr;

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
    void bookMenagerButtonPressed();
    void readerDataButtonPressed();

protected:
    // Funkcja przeładowania elementu
    void reload();

    bool eventMatching(QObject*, QEvent*);


};

#endif // OPERATIONLISTELEMENTREADERS_HPP
