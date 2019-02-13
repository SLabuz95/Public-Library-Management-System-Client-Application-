#ifndef BOOKDATAPANEL_HPP
#define BOOKDATAPANEL_HPP

#include"datapanel.hpp"
#include"emptyenum.hpp"
#include<QLabel>
#include<QCheckBox>
#include<QComboBox>
#include"formatabledatafield.hpp"
#include"../PLMS_Server_App/book.hpp"

class Book;
class QComboBox;
class BookDataPanel : public DataPanel{
public:
    BookDataPanel(void* parent, Book* book, DataPanelMode mode);
    ~BookDataPanel();

private:
    Book* book = nullptr;
    QLabel bookTitleLabel;
    FormatableDataField<Empty> bookTitleField;
    bool bookTitleFieldOk = false;
    QLabel bookAuthorLabel;
    FormatableDataField<Empty> bookAuthorField;
    bool bookAuthorFieldOk = false;
    QLabel bookPublisherLabel;
    FormatableDataField<Empty> bookPublisherField;
    bool bookPublisherFieldOk = false;
    QLabel bookEditionLabel;
    FormatableDataField<Empty> bookEditionField;
    bool bookEditionFieldOk = false;
    QLabel bookTypeLabel;
    QLabel* bookTypeValueLabel = nullptr;
    QComboBox* bookTypeCB = nullptr;
    QLabel bookIdLabel;
    QLabel bookIdValueLabel;
    QLabel bookStatusLabel;
    QLabel bookStatusValueLabel;
    QLabel *dateLabel = nullptr;
    QLabel *dateValueLabel = nullptr;

    // Funkcje zarządzania działaniem konstuktora
    void init();
    void setWindow();
    void createWidgets();
    void createLayout();
    void deleteWidgets();
    void connectAll();
    void disconnectAll();

    bool bookTitleFieldKeyPressed(QKeyEvent* ev);
    bool bookAuthorFieldKeyPressed(QKeyEvent* ev);
    bool bookPublisherFieldKeyPressed(QKeyEvent* ev);
    bool bookEditionFieldKeyPressed(QKeyEvent* ev);
    bool standardFieldKeyPressed(QKeyEvent* ev, FormatableDataField<Empty>* fdf, BookParameters bP);
    void switchFormatableFields();

protected:

    // Funkcja przeładowania elementu
    void reload();

    bool eventMatching(QObject*, QEvent*);

public:
    bool checkData();

    Book* getBook();
    Book* getTempBook();
    void changeMode(DataPanelMode);

};

#endif // BOOKDATAPANEL_HPP
