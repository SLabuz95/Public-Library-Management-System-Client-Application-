#ifndef COMMENTLISTELEMENT_HPP
#define COMMENTLISTELEMENT_HPP

#include<QLabel>
class Book;
class CommentList;
class CommentListElement : public QFrame{
    Q_OBJECT
public:
    CommentListElement(CommentList*, Book*, uint);
    ~CommentListElement();

private:
    CommentList* parent = nullptr;
    unsigned long long userId = 0;
    QLabel commentLabel;
    QLabel deleteButton;
    Book* book = nullptr;

    // Funkcje zarządzania działaniem konstuktora
    void init(Book&, uint);
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    // Generator tesktu (głównego i rozszerzonego dla nadklasy)
    void generateText(QString& str);
    void deleteButtonPressed();

protected:
    // Funkcja przeładowania elementu
    void reload();

public:
    CommentList* getParent();
    bool eventMatching(QObject*, QEvent*);

};

#endif // COMMENTLISTELEMENT_HPP
