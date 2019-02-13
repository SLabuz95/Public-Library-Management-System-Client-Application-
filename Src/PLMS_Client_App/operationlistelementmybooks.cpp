#include"operationlistelementmybooks.hpp"
#include"operationlist.hpp"
#include<QEvent>
#include<QLabel>
#include"commentlist.hpp"
#include"filteredlist.hpp"
#include"dialog.hpp"
#include"operationpanelfilteredlist.hpp"
#include"appwindowloggedinpanel.hpp"
#include"appwindow.hpp"
#include"../PLMS_Server_App/user.hpp"
#include"../PLMS_Server_App/book.hpp"

OperationListElementMyBooks::OperationListElementMyBooks(OperationList *parent, Book* book)
    : OperationListElement(parent), book(book), commentsButton(this), addCommentButton(this){
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationListElementMyBooks::~OperationListElementMyBooks(){
    disconnectAll();
    deleteWidgets();
}

void OperationListElementMyBooks::init(){
    generateText();
    addCommentButton.setText("Skomentuj");
    commentsButton.setText(QString("Komentarze(") + QString::number(book->getNumbOfBookComments()) + QString(")"));
    addCommentButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    commentsButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    addCommentButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(2), OPERATION_ELEMENT_BUTTON_HEIGHT);
    commentsButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(2), OPERATION_ELEMENT_BUTTON_HEIGHT);
    addCommentButton.setAlignment(Qt::AlignCenter);
    commentsButton.setAlignment(Qt::AlignCenter);
}

void OperationListElementMyBooks::setWindow(){
    if(commentList && book->getNumbOfBookComments() == 0){
        SET_PTR_DO(commentList, nullptr);
    }
    resize(OPERATION_ELEMENT_WIDTH,generalInfoLabel.height() + 3 *OPERATION_ELEMENT_VERTICAL_OFFSET + OPERATION_ELEMENT_BUTTON_HEIGHT + ((commentList)? commentList->height() + OPERATION_ELEMENT_VERTICAL_OFFSET : 0));
}

void OperationListElementMyBooks::createWidgets(){
    // Brak
}

void OperationListElementMyBooks::createLayout(){
    // Brak
    addCommentButton.move(OPERATION_ELEMENT_BUTTON_WIDTH + OPERATION_ELEMENT_HORIZONTAL_OFFSET , generalInfoLabel.height() + OPERATION_ELEMENT_VERTICAL_OFFSET * 2);
        commentsButton.move(OPERATION_ELEMENT_BUTTON_WIDTH + OPERATION_ELEMENT_HORIZONTAL_OFFSET * 2+ addCommentButton.width() , addCommentButton.y());
        if(commentList){
            commentList->move(0, generalInfoLabel.height() + 2 * OPERATION_ELEMENT_VERTICAL_OFFSET + OPERATION_ELEMENT_BUTTON_HEIGHT);
            commentList->show();
        }
        addCommentButton.show();
        commentsButton.show();
    parent->reallocate(true);
}

void OperationListElementMyBooks::deleteWidgets(){
    // Brak
}

void OperationListElementMyBooks::connectAll(){
    commentsButton.installEventFilter(parent->getParent());
    addCommentButton.installEventFilter(parent->getParent());
}

void OperationListElementMyBooks::disconnectAll(){
    // Brak
}

void OperationListElementMyBooks::generateText(){
    QString bookType = QString("\nGatunek: ");
    switch (book->getBookType()) {
    case BOOK_CRIME:
        bookType.append("Kryminał");
        break;
    case BOOK_DRAMA:
        bookType.append("Dramat");
        break;
    case BOOK_GUIDE:
        bookType.append("Przewodnik");
        break;
    case BOOK_SATIR:
        bookType.append("Satyra");
        break;
    case BOOK_HORROR:
        bookType.append("Groza");
        break;
    case BOOK_POETRY:
        bookType.append("Poezja");
        break;
    case BOOK_FANTASY:
        bookType.append("Fantastyka");
        break;
    case BOOK_HISTORY:
        bookType.append("Historyczna");
        break;
    case BOOK_JOURNAL:
        bookType.append("Czasopismo");
        break;
    case BOOK_ROMANCE:
        bookType.append("Romans");
        break;
    case BOOK_SCIENCE:
        bookType.append("Nauka");
        break;
    case BOOK_THRILLER:
        bookType.append("Thriller");
        break;
    case BOOK_BIOGRAPHY:
        bookType.append("Biografia");
        break;
    case BOOK_COMIC_BOOK:
        bookType.append("Komiks");
        break;
    case BOOK_DICTIONARY:
        bookType.append("Słownik");
        break;
    case BOOK_FAIRY_TALE:
        bookType.append("Bajka");
        break;
    case BOOK_ENCYCLOPEDIA:
        bookType.append("Encyklopedia");
        break;
    case BOOK_AUTOBIOGRAPHY:
        bookType.append("Autobiografia");
        break;
    case BOOK_SCIENCE_FICTION:
        bookType.append("Fantastyka naukowa");
        break;
    case BOOK_CHILDREN_LITERATURE:
        bookType.append("Literatura dziecięca");
        break;
    default:
        break;
    }
    QString additionalText = QString("\nStatus książki: ");
    switch(book->getBookStatus()){
    case BOOK_STATUS_FREE:
        additionalText.append("Dostępna");
        break;
    case BOOK_STATUS_RESERVED:
        additionalText.append("Zarezerwowana");
        break;
    case BOOK_STATUS_CHECKED_OUT:
        additionalText.append("Wypożyczona");
        break;
    case BOOK_STATUS_EXPIRED:
        additionalText.append("Do oddania");
        break;
    default:
        break;
    }

    switch(book->getBookStatus()){
    case BOOK_STATUS_RESERVED:
        additionalText.append(QString("\nRezerwacja wygasa: ") + book->getParam(BOOK_DATE));
        break;
    case BOOK_STATUS_CHECKED_OUT:
        additionalText.append(QString("\nNależy oddać do: ") + book->getParam(BOOK_DATE));
        break;
    case BOOK_STATUS_EXPIRED:
        additionalText.append(QString("\nWygasła z dniem: ") + book->getParam(BOOK_DATE));
        break;
    default:
        break;
    }
    QString text = TEXT_GENERATOR_ELEMENT_MY_BOOKS;
    uint newHeight = generalInfoLabel.fontMetrics().boundingRect(0,0, OPERATION_ELEMENT_GENERAL_INFO_LABEL_WIDTH, 1200, Qt::TextWordWrap, text).height();
        generalInfoLabel.resize(OPERATION_ELEMENT_GENERAL_INFO_LABEL_WIDTH, (newHeight < OPERATION_ELEMENT_BUTTON_HEIGHT)? OPERATION_ELEMENT_BUTTON_HEIGHT + 2 : newHeight);
        generalInfoLabel.setText(text);
}

void OperationListElementMyBooks::reload(bool reloadLayout)
{
    if(reloadLayout){
        setWindow();
        createWidgets();
        createLayout();
    }else{
    disconnectAll();
    deleteWidgets();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    }
}

bool OperationListElementMyBooks::eventMatching(QObject *obj, QEvent *ev){
    switch(ev->type()){
        case QEvent::MouseButtonRelease:
        if(obj == &commentsButton){
            commentsButtonPressed();
            return true;
        }
        if(obj == &addCommentButton){
            addCommentButtonPressed();
            return true;
        }
            break;
    case QEvent::Enter:
    {
        if(obj == &commentsButton){
            commentsButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
        if(obj == &addCommentButton){
            addCommentButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &commentsButton){
            commentsButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
        if(obj == &addCommentButton){
            addCommentButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
    }
        break;
        default:
            break;

    }
    return false;
}


void OperationListElementMyBooks::commentsButtonPressed(){
    if(commentList){
        SET_PTR_DO(commentList, nullptr);
    }else{
        if(book->getNumbOfBookComments() > 0){
            SET_PTR_DO(commentList, new CommentList(book, this));
        }else{
            return;
        }
    }
    reload(true);
    parent->reallocate(true);
}

void OperationListElementMyBooks::addCommentButtonPressed(){
    Dialog dlg(ADD_COMMENT, book, parent->getParent()->getParent()->getParent()->getUser()->getUserId(), parent->getParent()->getParent()->getParent()->getParent());
    dlg.exec();
    SET_PTR_DO(commentList, new CommentList(book, this));
    reload(true);
    parent->reallocate(true);
}

Book* OperationListElementMyBooks::getBook(){
    return book;
}
