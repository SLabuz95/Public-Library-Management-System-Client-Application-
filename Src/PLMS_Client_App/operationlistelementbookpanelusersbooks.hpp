#ifndef OPERATIONLISTELEMENTBOOKPANELUSERSBOOKS_HPP
#define OPERATIONLISTELEMENTBOOKPANELUSERSBOOKS_HPP

#include"operationlistelement.hpp"
class Book;
class CommentList;
class OperationList;
class OperationListElementBookPanelUsersBooks : public OperationListElement{
    Q_OBJECT
public:
    OperationListElementBookPanelUsersBooks(OperationList*, Book*);
    ~OperationListElementBookPanelUsersBooks();

private:
    Book* book = nullptr;
    QLabel actionButton;

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

    void actionButtonPressed();

protected:
    // Funkcja przeładowania elementu


    bool eventMatching(QObject*, QEvent*);
public:
    Book* getBook();
    void reload(bool);
};

#endif // OPERATIONLISTELEMENTBOOKPANELUSERSBOOKS_HPP
