#include"bookdatapanel.hpp"
#include<QKeyEvent>
#include<QLineEdit>
#include<QComboBox>
#include"../PLMS_Server_App/book.hpp"

BookDataPanel::BookDataPanel(void* parent, Book* book, DataPanelMode mode)
    : DataPanel (parent, mode),
      book(book),
      bookTitleLabel(this),
      bookTitleField(((mode < DATA_MODE)? true : false), nullptr, false, this, QString(), false),
      bookAuthorLabel(this),
      bookAuthorField(((mode < DATA_MODE)? true : false), nullptr, false, this, QString(), false),
      bookPublisherLabel(this),
      bookPublisherField(((mode < DATA_MODE)? true : false), nullptr, false, this, QString(), false),
      bookEditionLabel(this),
      bookEditionField(((mode < DATA_MODE)? true : false), nullptr, false, this, QString(), false),
      bookTypeLabel(this),
      bookIdLabel(this),
      bookIdValueLabel(this),
      bookStatusLabel(this),
      bookStatusValueLabel(this)

{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

BookDataPanel::~BookDataPanel(){
    disconnectAll();
    deleteWidgets();
}

void BookDataPanel::init(){
    if(book){
        if(mode < DATA_MODE){
            bookTitleField.getDataUTextEdit()->setText(book->getParam(BOOK_TITLE));
            bookAuthorField.getDataUTextEdit()->setText(book->getParam(BOOK_AUTHOR));
            bookPublisherField.getDataUTextEdit()->setText(book->getParam(BOOK_PUBLISHER));
            bookEditionField.getDataUTextEdit()->setText(book->getParam(BOOK_EDITION));
        }else{
            bookTitleField.getDataULabel()->setText(book->getParam(BOOK_TITLE));
            bookTitleField.getDataULabel()->setStyleSheet(STYLESHEET_DATA_LABEL);
            bookAuthorField.getDataULabel()->setText(book->getParam(BOOK_AUTHOR));
            bookAuthorField.getDataULabel()->setStyleSheet(STYLESHEET_DATA_LABEL);
            bookIdLabel.setText("Indeks: ");
            bookIdLabel.setGeometry(BOOK_DATA_PANEL_BOOK_ID_LABEL_X,BOOK_DATA_PANEL_BOOK_ID_LABEL_Y,BOOK_DATA_PANEL_BOOK_ID_LABEL_WIDTH(false),BOOK_DATA_PANEL_BOOK_ID_LABEL_HEIGHT);
            bookIdLabel.setStyleSheet(STYLESHEET_DATA_LABEL);
            bookIdValueLabel.setStyleSheet(STYLESHEET_DATA_LABEL);
            bookIdValueLabel.setGeometry(BOOK_DATA_PANEL_BOOK_ID_FIELD_X(false),BOOK_DATA_PANEL_BOOK_ID_FIELD_Y,BOOK_DATA_PANEL_BOOK_ID_FIELD_WIDTH(false),BOOK_DATA_PANEL_BOOK_ID_FIELD_HEIGHT);
            bookIdValueLabel.setText(book->getParam(BOOK_ID));
            bookPublisherField.getDataULabel()->setText(book->getParam(BOOK_PUBLISHER));
            bookPublisherField.getDataULabel()->setStyleSheet(STYLESHEET_DATA_LABEL);
            bookEditionField.getDataULabel()->setText(book->getParam(BOOK_EDITION));
            bookEditionField.getDataULabel()->setStyleSheet(STYLESHEET_DATA_LABEL);
        }
        bookTitleFieldOk = true;
        bookPublisherFieldOk = true;
        bookEditionFieldOk = true;
        bookAuthorFieldOk = true;
        switch (book->getBookStatus()) {
        case BOOK_STATUS_FREE:
            bookStatusValueLabel.setText("Dostępna");
            break;
        case BOOK_STATUS_EXPIRED:
            bookStatusValueLabel.setText("Do oddania");
            break;
        case BOOK_STATUS_RESERVED:
            bookStatusValueLabel.setText("Zarezerwowana");
            break;
        case BOOK_STATUS_CHECKED_OUT:
            bookStatusValueLabel.setText("Wypożyczona");
            break;
        default:
            break;
        }
    }
}

void BookDataPanel::setWindow(){
    // Empty
}

void BookDataPanel::createWidgets(){
    if(mode < DATA_MODE){
            SET_PTR_DO(bookTypeCB, new QComboBox(this));
        }else{
            SET_PTR_DO(bookTypeValueLabel, new QLabel(this));
        }
    if(book){
        if(book->getBookStatus() != BOOK_STATUS_FREE){
            SET_PTR_DO(dateLabel, new QLabel(this));
            SET_PTR_DO(dateValueLabel, new QLabel(this));
        }
    }
}

void BookDataPanel::createLayout(){
    // Book Name Label
    bookTitleLabel.setGeometry(BOOK_DATA_PANEL_BOOK_TITLE_LABEL_X, BOOK_DATA_PANEL_BOOK_TITLE_LABEL_Y, BOOK_DATA_PANEL_BOOK_TITLE_LABEL_WIDTH(false), BOOK_DATA_PANEL_BOOK_TITLE_LABEL_HEIGHT);
    bookTitleLabel.setText(BOOK_DATA_PANEL_BOOK_TITLE_TEXT);
    bookTitleLabel.setStyleSheet(STYLESHEET_DATA_LABEL);

    // Book Name Field
    bookTitleField.setGeometry(BOOK_DATA_PANEL_BOOK_TITLE_FIELD_X(false), BOOK_DATA_PANEL_BOOK_TITLE_FIELD_Y, BOOK_DATA_PANEL_BOOK_TITLE_FIELD_WIDTH(false), BOOK_DATA_PANEL_BOOK_TITLE_FIELD_HEIGHT);

    // Book Author Label
    bookAuthorLabel.setGeometry(BOOK_DATA_PANEL_BOOK_AUTHOR_LABEL_X,BOOK_DATA_PANEL_BOOK_AUTHOR_LABEL_Y,BOOK_DATA_PANEL_BOOK_AUTHOR_LABEL_WIDTH(false),BOOK_DATA_PANEL_BOOK_AUTHOR_LABEL_HEIGHT);
    bookAuthorLabel.setText(BOOK_DATA_PANEL_BOOK_AUTHOR_TEXT);
    bookAuthorLabel.setStyleSheet(STYLESHEET_DATA_LABEL);

    // Book Name Field
    bookAuthorField.setGeometry(BOOK_DATA_PANEL_BOOK_AUTHOR_FIELD_X(false),BOOK_DATA_PANEL_BOOK_AUTHOR_FIELD_Y,BOOK_DATA_PANEL_BOOK_AUTHOR_FIELD_WIDTH(false),BOOK_DATA_PANEL_BOOK_AUTHOR_FIELD_HEIGHT);

    // Book First Name Label
    bookPublisherLabel.setGeometry(BOOK_DATA_PANEL_BOOK_PUBLISHER_LABEL_X, BOOK_DATA_PANEL_BOOK_PUBLISHER_LABEL_Y, BOOK_DATA_PANEL_BOOK_PUBLISHER_LABEL_WIDTH(false), BOOK_DATA_PANEL_BOOK_PUBLISHER_LABEL_HEIGHT);
    bookPublisherLabel.setText(BOOK_DATA_PANEL_PUBLISHER_TEXT);
    bookPublisherLabel.setStyleSheet(STYLESHEET_DATA_LABEL);
    // Book First Name Field
    bookPublisherField.setGeometry(BOOK_DATA_PANEL_BOOK_PUBLISHER_FIELD_X(false), BOOK_DATA_PANEL_BOOK_PUBLISHER_FIELD_Y, BOOK_DATA_PANEL_BOOK_PUBLISHER_FIELD_WIDTH(false), BOOK_DATA_PANEL_BOOK_PUBLISHER_FIELD_HEIGHT);

    // Book Edition Label
    bookEditionLabel.setGeometry(BOOK_DATA_PANEL_BOOK_EDITION_LABEL_X, BOOK_DATA_PANEL_BOOK_EDITION_LABEL_Y, BOOK_DATA_PANEL_BOOK_EDITION_LABEL_WIDTH(false), BOOK_DATA_PANEL_BOOK_EDITION_LABEL_HEIGHT);
    bookEditionLabel.setText(BOOK_DATA_PANEL_EDITION_TEXT);
    bookEditionLabel.setStyleSheet(STYLESHEET_DATA_LABEL);
    // Book Edition Field
    bookEditionField.setGeometry(BOOK_DATA_PANEL_BOOK_EDITION_FIELD_X(false), BOOK_DATA_PANEL_BOOK_EDITION_FIELD_Y, BOOK_DATA_PANEL_BOOK_EDITION_FIELD_WIDTH(false), BOOK_DATA_PANEL_BOOK_EDITION_FIELD_HEIGHT);

    if(mode < DATA_MODE){
        SET_PTR_DO(bookTypeCB, new QComboBox(this));
    }else{
        SET_PTR_DO(bookTypeValueLabel, new QLabel(this));
    }

    // Book Type Label
    bookTypeLabel.setGeometry(BOOK_DATA_PANEL_BOOK_TYPE_LABEL_X,BOOK_DATA_PANEL_BOOK_TYPE_LABEL_Y,BOOK_DATA_PANEL_BOOK_TYPE_LABEL_WIDTH(false), BOOK_DATA_PANEL_BOOK_TYPE_LABEL_HEIGHT);
    bookTypeLabel.setText(BOOK_DATA_PANEL_BOOK_TYPE_TEXT);
    bookTypeLabel.setStyleSheet(STYLESHEET_DATA_LABEL);

    // Book Type Field
    if(mode >= DATA_MODE){
        bookTypeValueLabel->setGeometry(BOOK_DATA_PANEL_BOOK_TYPE_FIELD_X(false),BOOK_DATA_PANEL_BOOK_TYPE_FIELD_Y,BOOK_DATA_PANEL_BOOK_TYPE_FIELD_WIDTH(false),BOOK_DATA_PANEL_BOOK_TYPE_FIELD_HEIGHT);
        bookTypeValueLabel->setStyleSheet(STYLESHEET_DATA_LABEL);
        bookTypeValueLabel->show();
        switch (book->getBookType()) {
        case BOOK_CRIME:
            bookTypeValueLabel->setText("Kryminał");
            break;
        case BOOK_DRAMA:
            bookTypeValueLabel->setText("Dramat");
            break;
        case BOOK_GUIDE:
            bookTypeValueLabel->setText("Przewodnik");
            break;
        case BOOK_SATIR:
            bookTypeValueLabel->setText("Satyra");
            break;
        case BOOK_HORROR:
            bookTypeValueLabel->setText("Groza");
            break;
        case BOOK_POETRY:
            bookTypeValueLabel->setText("Poezja");
            break;
        case BOOK_FANTASY:
            bookTypeValueLabel->setText("Fantastyka");
            break;
        case BOOK_HISTORY:
            bookTypeValueLabel->setText("Historyczna");
            break;
        case BOOK_JOURNAL:
            bookTypeValueLabel->setText("Czasopismo");
            break;
        case BOOK_ROMANCE:
            bookTypeValueLabel->setText("Romans");
            break;
        case BOOK_SCIENCE:
            bookTypeValueLabel->setText("Nauka");
            break;
        case BOOK_THRILLER:
            bookTypeValueLabel->setText("Thriller");
            break;
        case BOOK_BIOGRAPHY:
            bookTypeValueLabel->setText("Biografia");
            break;
        case BOOK_COMIC_BOOK:
            bookTypeValueLabel->setText("Komiks");
            break;
        case BOOK_DICTIONARY:
            bookTypeValueLabel->setText("Słownik");
            break;
        case BOOK_FAIRY_TALE:
            bookTypeValueLabel->setText("Bajka");
            break;
        case BOOK_ENCYCLOPEDIA:
            bookTypeValueLabel->setText("Encyklopedia");
            break;
        case BOOK_AUTOBIOGRAPHY:
            bookTypeValueLabel->setText("Autobiografia");
            break;
        case BOOK_SCIENCE_FICTION:
            bookTypeValueLabel->setText("Fantastyka naukowa");
            break;
        case BOOK_CHILDREN_LITERATURE:
            bookTypeValueLabel->setText("Literatura dziecięca");
            break;
        default:
            break;
        }
    }else{
        bookTypeCB->setGeometry(BOOK_DATA_PANEL_BOOK_TYPE_FIELD_X(false),BOOK_DATA_PANEL_BOOK_TYPE_FIELD_Y,BOOK_DATA_PANEL_BOOK_TYPE_FIELD_WIDTH(false),BOOK_DATA_PANEL_BOOK_TYPE_FIELD_HEIGHT);
        bookTypeCB->addItem("Autobiografia");
        bookTypeCB->addItem("Biografia");
        bookTypeCB->addItem("Słownik");
        bookTypeCB->addItem("Encyklopedia");
        bookTypeCB->addItem("Historyczna");
        bookTypeCB->addItem("Czasopismo");
        bookTypeCB->addItem("Przewodnik");
        bookTypeCB->addItem("Nauka");
        bookTypeCB->addItem("Kryminał");
        bookTypeCB->addItem("Romans");
        bookTypeCB->addItem("Fantastyka naukowa");
        bookTypeCB->addItem("Dramat");
        bookTypeCB->addItem("Bajka");
        bookTypeCB->addItem("Fantastyka");
        bookTypeCB->addItem("Poezja");
        bookTypeCB->addItem("Satyra");
        bookTypeCB->addItem("Komiks");
        bookTypeCB->addItem("Groza");
        bookTypeCB->addItem("Thriller");
        bookTypeCB->addItem("Literatura dziecięca");
        if(book)
        bookTypeCB->setCurrentIndex(book->getBookType());
        bookTypeCB->show();
    }


    // Book Status Label
    bookStatusLabel.setGeometry(BOOK_DATA_PANEL_BOOK_STATUS_LABEL_X, BOOK_DATA_PANEL_BOOK_STATUS_LABEL_Y, BOOK_DATA_PANEL_BOOK_STATUS_LABEL_WIDTH(false), BOOK_DATA_PANEL_BOOK_STATUS_LABEL_HEIGHT);
    bookStatusLabel.setText(BOOK_DATA_PANEL_STATUS_TEXT);
    bookStatusLabel.setStyleSheet(STYLESHEET_DATA_LABEL);
    // Book Status
    bookStatusValueLabel.setGeometry(BOOK_DATA_PANEL_BOOK_STATUS_FIELD_X(false), BOOK_DATA_PANEL_BOOK_STATUS_FIELD_Y, BOOK_DATA_PANEL_BOOK_STATUS_FIELD_WIDTH(false), BOOK_DATA_PANEL_BOOK_STATUS_FIELD_HEIGHT);
    bookStatusValueLabel.setStyleSheet(STYLESHEET_DATA_LABEL);
    if(mode == REGISTER_MODE){
        bookStatusLabel.hide();
        bookStatusValueLabel.hide();
    }

    if(book && book->getBookStatus() == BOOK_STATUS_RESERVED){
    // Book Pesel Label
    dateLabel->setGeometry(BOOK_DATA_PANEL_BOOK_DATE_LABEL_X,BOOK_DATA_PANEL_BOOK_DATE_LABEL_Y,BOOK_DATA_PANEL_BOOK_DATE_LABEL_WIDTH(false),BOOK_DATA_PANEL_BOOK_DATE_LABEL_HEIGHT);
    dateLabel->setText(BOOK_DATA_PANEL_RESERVED_DATE_TEXT);
    dateLabel->setStyleSheet(STYLESHEET_DATA_LABEL);
    dateLabel->show();
    // Book Pesel Field
    dateValueLabel->setGeometry(BOOK_DATA_PANEL_BOOK_DATE_FIELD_X(false),BOOK_DATA_PANEL_BOOK_DATE_FIELD_Y,BOOK_DATA_PANEL_BOOK_DATE_FIELD_WIDTH(false),BOOK_DATA_PANEL_BOOK_DATE_FIELD_HEIGHT);
    dateValueLabel->setStyleSheet(STYLESHEET_DATA_LABEL);
    dateValueLabel->show();
    }

    if(mode == REGISTER_MODE){
        bookTitleField.getDataUTextEdit()->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
        bookAuthorField.getDataUTextEdit()->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
        bookEditionField.getDataUTextEdit()->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
        bookPublisherField.getDataUTextEdit()->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
    }
}

void BookDataPanel::deleteWidgets(){
    SET_PTR_DO(dateValueLabel, nullptr);
    SET_PTR_DO(dateValueLabel, nullptr);
    SET_PTR_DO(bookTypeCB, nullptr);
    SET_PTR_DO(bookTypeValueLabel, nullptr);
}

void BookDataPanel::connectAll(){
    // Book Name Field
    bookTitleField.installEventFilter(this);

    // Book Author Field
    bookAuthorField.installEventFilter(this);

    // Book First Name Field
    bookPublisherField.installEventFilter(this);

    // Book Second Name Field
    bookEditionField.installEventFilter(this);


}

void BookDataPanel::disconnectAll(){
    // Empty
}

bool BookDataPanel::bookTitleFieldKeyPressed(QKeyEvent* ev){
    return standardFieldKeyPressed(ev, &bookTitleField, BOOK_TITLE);
}

bool BookDataPanel::bookPublisherFieldKeyPressed(QKeyEvent* ev){
    return standardFieldKeyPressed(ev, &bookPublisherField, BOOK_PUBLISHER);
}

bool BookDataPanel::bookAuthorFieldKeyPressed(QKeyEvent *ev){
    return standardFieldKeyPressed(ev, &bookAuthorField, BOOK_AUTHOR);
}

bool BookDataPanel::bookEditionFieldKeyPressed(QKeyEvent* ev){
    return standardFieldKeyPressed(ev, &bookEditionField, BOOK_EDITION);
}

bool BookDataPanel::standardFieldKeyPressed(QKeyEvent* ev, FormatableDataField<Empty>* fdf, BookParameters bP){
    QLineEdit* le = fdf->getDataUTextEdit();
    uint len = le->text().length();
    if(len > 59){
        switch(ev->key()){
        case Qt::Key_Left:
            return false;
        case Qt::Key_Right:
            return false;
        case Qt::Key_Backspace:
            le->backspace();
            break;
        case Qt::Key_Delete:
            le->del();
            break;
        default:
            return true;
        }
    }
    else{
        switch(ev->key()){
        case Qt::Key_Left:
            return false;
        case Qt::Key_Right:
            return false;
        case Qt::Key_Enter:
            return true;
        case Qt::Key_Tab:
            return true;
        case Qt::Key_Slash:
            return true;
        case Qt::Key_Backslash:
            return true;
        case Qt::Key_Return:
            return true;
        case Qt::Key_Colon:
            return true;
        case Qt::Key_Asterisk:
            return true;
        case Qt::Key_Less:
            return true;
        case Qt::Key_Greater:
            return true;
        case Qt::Key_QuoteDbl:
            return true;
        case Qt::Key_Question:
            return true;
        case Qt::Key_Bar:
            return true;
        case Qt::Key_Alt:
            return true;
        case Qt::Key_Shift:
            return true;
        case Qt::Key_Control:
            return true;
        case Qt::Key_Space:
            le->insert(ev->text());
            break;
        case Qt::Key_Backspace:
            le->backspace();
            break;
        case Qt::Key_Delete:
            le->del();
            break;
        default:
            le->insert(ev->text());
            break;
        }
    }
    fdf->multiSpaceKeyDetection();
    len = le->text().length();
    if(le->text().isEmpty() || len > 60){
        le->setStyleSheet(STYLESHEET_LINE_EDIT_WRONG_DATA);
        switch (bP) {
        case BOOK_TITLE:
            bookTitleFieldOk = false;
            break;
        case BOOK_AUTHOR:
            bookAuthorFieldOk = false;
            break;
        case BOOK_EDITION:
            bookEditionFieldOk = false;
            break;
        case BOOK_PUBLISHER:
            bookPublisherFieldOk = false;
            break;
        default:
            break;
        }
    }
    else{
        le->setStyleSheet("");
        switch (bP) {
        case BOOK_TITLE:
            bookTitleFieldOk = true;
            break;
        case BOOK_AUTHOR:
            bookAuthorFieldOk = true;
            break;
        case BOOK_EDITION:
            bookEditionFieldOk = true;
            break;
        case BOOK_PUBLISHER:
            bookPublisherFieldOk = true;
            break;
        default:
            break;
        }
    }
    return true;
}

void BookDataPanel::reload(){
    disconnectAll();
    deleteWidgets();
    createWidgets();
    createLayout();
    connectAll();
}

bool BookDataPanel::eventMatching(QObject* obj, QEvent* ev){
    switch (ev->type()) {
    case QEvent::KeyPress:
    {
        if(obj == bookTitleField.getDataUTextEdit()){
            if(bookTitleFieldKeyPressed(static_cast<QKeyEvent*>(ev)))
                return true;
            else {
                break;
            }
        }
        if(obj == bookAuthorField.getDataUTextEdit()){
            if(bookAuthorFieldKeyPressed(static_cast<QKeyEvent*>(ev))){
                return true;
            }else{
                break;
            }
        }
        if(obj == bookPublisherField.getDataUTextEdit()){
            if(bookPublisherFieldKeyPressed(static_cast<QKeyEvent*>(ev)))
                return true;
            else {
                break;
            }
        }
        if(obj == bookEditionField.getDataUTextEdit()){
            if(bookEditionFieldKeyPressed(static_cast<QKeyEvent*>(ev)))
                return true;
            else {
                break;
            }
        }
    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, ev);
}

bool BookDataPanel::checkData(){
    return bookTitleFieldOk && bookPublisherFieldOk && bookEditionFieldOk && bookAuthorFieldOk;
}

Book* BookDataPanel::getBook(){
    return book;
}

Book* BookDataPanel::getTempBook(){
    Book* tempBook = new Book();
    tempBook->setParam(BOOK_TITLE, bookTitleField.getDataUTextEdit()->text());
    tempBook->setParam(BOOK_PUBLISHER, bookPublisherField.getDataUTextEdit()->text());
    tempBook->setParam(BOOK_AUTHOR, bookAuthorField.getDataUTextEdit()->text());
    tempBook->setParam(BOOK_TYPE, QString::number(bookTypeCB->currentIndex()));
    tempBook->setParam(BOOK_EDITION, bookEditionField.getDataUTextEdit()->text());
    if(mode == REGISTER_MODE)
        tempBook->setParam(BOOK_STATUS, QString::number(BOOK_STATUS_FREE));
    else{
        tempBook->setParam(BOOK_STATUS, book->getParam(BOOK_STATUS));
    }
    if(mode == EDITABLE_MODE || mode == REGISTER_MODE){
        tempBook->setParam(BOOK_TYPE, QString::number(bookTypeCB->currentIndex()));
    }
    return tempBook;
}

void BookDataPanel::changeMode(DataPanelMode newMode){
    if(newMode < DATA_MODE){
        if(mode < DATA_MODE)
            return;
        mode = newMode;
        switchFormatableFields();
        reload();
        init();
    }else{
        if(mode < DATA_MODE){
            mode = newMode;
            switchFormatableFields();
            reload();
            init();
        }
    }
}

void BookDataPanel::switchFormatableFields(){
    bookTitleField.switchDisplayForm(false);
    bookAuthorField.switchDisplayForm(false);
    bookPublisherField.switchDisplayForm(false);
    bookEditionField.switchDisplayForm(false);
}
