#ifndef OPERATIONLISTELEMENTBOOKS_HPP
#define OPERATIONLISTELEMENTBOOKS_HPP

#include"operationlistelement.hpp"
class Book;
class CommentList;
class OperationList;
class OperationListElementBooks : public OperationListElement{
    Q_OBJECT
public:
    OperationListElementBooks(OperationList*, Book*);
    ~OperationListElementBooks();

private:
    Book* book = nullptr;
    QLabel dataPanelButton;
    QLabel commentsButton;
    CommentList* commentList = nullptr;

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

    void dataPanelButtonPressed();
    void commentsButtonPressed();

protected:


    bool eventMatching(QObject*, QEvent*);

public:
    // Funkcja przeładowania elementu
    void reload(bool);
    Book* getBook();
};

#endif // OPERATIONLISTELEMENTBOOKS_HPP
