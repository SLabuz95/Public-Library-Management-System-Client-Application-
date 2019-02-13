#ifndef OPERATIONLISTELEMENTMYBOOKS_HPP
#define OPERATIONLISTELEMENTMYBOOKS_HPP

#include"operationlistelement.hpp"
class Book;
class OperationList;
class CommentList;
class OperationListElementMyBooks : public OperationListElement{
    Q_OBJECT
public:
    OperationListElementMyBooks(OperationList*, Book*);
    ~OperationListElementMyBooks();

private:
    Book* book = nullptr;
    QLabel commentsButton;
    QLabel addCommentButton;
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

    void commentsButtonPressed();
    void addCommentButtonPressed();

protected:


    bool eventMatching(QObject*, QEvent*);


public:
    // Funkcja przeładowania elementu
    void reload(bool);
    Book* getBook();
};

#endif // OPERATIONLISTELEMENTMYBOOKS_HPP
