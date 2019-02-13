#ifndef OPERATIONLISTELEMENTLIBRARY_HPP
#define OPERATIONLISTELEMENTLIBRARY_HPP

#include"operationlistelement.hpp"

class CommentList;
class Book;
class OperationList;
class OperationListElementLibrary : public OperationListElement{
    Q_OBJECT
public:
    OperationListElementLibrary(OperationList*, Book*);
    ~OperationListElementLibrary();

private:
    Book* book = nullptr;
    QLabel reserveBookButton;
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

    void reserveBookButtonPressed();
    void commentsButtonPressed();
    void addCommentButtonPressed();
protected:
    // Funkcja przeładowania elementu
    void reload(bool);

    bool eventMatching(QObject*, QEvent*);

public:
    Book* getBook();
};

#endif // OPERATIONLISTELEMENTLIBRARY_HPP
