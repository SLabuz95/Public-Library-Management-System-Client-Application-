#ifndef OPERATIONLISTELEMENTUSERS_HPP
#define OPERATIONLISTELEMENTUSERS_HPP

#include"operationlistelement.hpp"
class User;
class OperationList;
class OperationListElementUsers : public OperationListElement{
    Q_OBJECT
public:
    OperationListElementUsers(OperationList*, User*);
    ~OperationListElementUsers();

private:
    User* user = nullptr;

    QLabel bookMenagerButton;
    QLabel readerDataButton;
    QLabel removeUserButton;

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

    // Obsługa przycisków
    void bookMenagerButtonPressed();
    void readerDataButtonPressed();
    void removeUserButtonPressed();

protected:
    // Funkcja przeładowania elementu
    void reload();

    bool eventMatching(QObject*, QEvent*);


};

#endif // OPERATIONLISTELEMENTUSERS_HPP
