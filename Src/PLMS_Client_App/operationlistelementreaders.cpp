#include"operationlistelementreaders.hpp"
#include"operationlist.hpp"
#include"filteredlist.hpp"
#include"../PLMS_Server_App/user.hpp"
#include<QEvent>
#include<QLabel>
#include"dialog.hpp"
#include"operationpanelfilteredlist.hpp"
#include"appwindowloggedinpanel.hpp"
#include"appwindow.hpp"


OperationListElementReaders::OperationListElementReaders(OperationList *parent, User* user)
    : OperationListElement(parent), user(user), bookMenagerButton(this), readerDataButton(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationListElementReaders::~OperationListElementReaders(){
    disconnectAll();
    deleteWidgets();
}

void OperationListElementReaders::init(){
    generateText();
    bookMenagerButton.setText("Panel książek");
    readerDataButton.setText("Dane czytelnika");
    bookMenagerButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    readerDataButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    bookMenagerButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(2), OPERATION_ELEMENT_BUTTON_HEIGHT);
    readerDataButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(2), OPERATION_ELEMENT_BUTTON_HEIGHT);
    bookMenagerButton.setAlignment(Qt::AlignCenter);
    readerDataButton.setAlignment(Qt::AlignCenter);
}

void OperationListElementReaders::setWindow(){
    resize(OPERATION_ELEMENT_WIDTH,generalInfoLabel.height() + 3 * OPERATION_ELEMENT_VERTICAL_OFFSET + OPERATION_ELEMENT_BUTTON_HEIGHT);
}

void OperationListElementReaders::createWidgets(){
    // Brak
}

void OperationListElementReaders::createLayout(){
    // Brak
    bookMenagerButton.move(OPERATION_ELEMENT_BUTTON_WIDTH + OPERATION_ELEMENT_HORIZONTAL_OFFSET, generalInfoLabel.height() + 2 * OPERATION_ELEMENT_VERTICAL_OFFSET);
        readerDataButton.move(OPERATION_ELEMENT_BUTTON_WIDTH + OPERATION_ELEMENT_HORIZONTAL_OFFSET * 2 + bookMenagerButton.width() , bookMenagerButton.y());
        bookMenagerButton.show();
        readerDataButton.show();    
}

void OperationListElementReaders::deleteWidgets(){
    // Brak
}

void OperationListElementReaders::connectAll(){
    bookMenagerButton.installEventFilter(parent->getParent());
    readerDataButton.installEventFilter(parent->getParent());

}

void OperationListElementReaders::disconnectAll(){
    // Brak
}

void OperationListElementReaders::generateText(){
    QString text = TEXT_GENERATOR_ELEMENT_READER;
    uint newHeight = generalInfoLabel.fontMetrics().boundingRect(0,0, OPERATION_ELEMENT_GENERAL_INFO_LABEL_WIDTH, 1200, Qt::TextWordWrap, text).height();
        generalInfoLabel.resize(OPERATION_ELEMENT_GENERAL_INFO_LABEL_WIDTH, (newHeight < OPERATION_ELEMENT_BUTTON_HEIGHT)? OPERATION_ELEMENT_BUTTON_HEIGHT + 2 : newHeight);
        generalInfoLabel.setText(text);    
}

void OperationListElementReaders::reload(){
    disconnectAll();
    deleteWidgets();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

bool OperationListElementReaders::eventMatching(QObject *obj, QEvent *ev){
    switch(ev->type()){
        case QEvent::MouseButtonRelease:
        if(obj == &bookMenagerButton){
            bookMenagerButtonPressed();
            return true;
        }
        if(obj == &readerDataButton){
            readerDataButtonPressed();
            return true;
        }
            break;
    case QEvent::Enter:
    {
        if(obj == &bookMenagerButton){
            bookMenagerButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
        if(obj == &readerDataButton){
            readerDataButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &bookMenagerButton){
            bookMenagerButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
        if(obj == &readerDataButton){
            readerDataButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
    }
        break;
        default:
            break;

    }
    return false;
}

void OperationListElementReaders::bookMenagerButtonPressed(){
    Dialog dlg(BOOK_PANEL, user, parent->getParent()->getParent()->getParent());
    dlg.exec();
    generateText();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

void OperationListElementReaders::readerDataButtonPressed(){
    parent->getParent()->getParent()->getParent()->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_USER_DATA_STAT, user);
}
