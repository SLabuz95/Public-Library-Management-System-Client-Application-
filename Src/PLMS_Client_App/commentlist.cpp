#include"commentlist.hpp"
#include"commentlistelement.hpp"
#include"operationlistelement.hpp"
#include"../PLMS_Server_App/book.hpp"



CommentList::CommentList(Book* book,OperationListElement *parent)
    : QFrame(parent), parent(parent), book(book)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    setStyleSheet("CommentList{background-color: transparent;}");
}

CommentList::~CommentList(){
    disconnectAll();
    deleteWidgets();
}

void CommentList::init(){
    // Empty
}

void CommentList::setWindow(){

}

void CommentList::createWidgets(){
    for(uint i = 0; i < book->getNumbOfBookComments(); i++)
        addElement(new CommentListElement(this, book, i));
}

void CommentList::createLayout(){

}

void CommentList::deleteWidgets(){
    for(uint i = 0; i < numbOfElements; i++)
        SET_PTR_DO((*(elements +i)), nullptr);
    SET_PTR_DOA(elements, nullptr);
}

void CommentList::connectAll(){
    // Empty
}

void CommentList::disconnectAll(){
    // Empty
}

OperationListElement* CommentList::getParent(){
    return parent;
}

bool CommentList::eventFilter(QObject *obj, QEvent *ev){
    uint i = 0;
    uint numbOfElement = numbOfElements;
    if(numbOfElement > 0)
        while(!(*(elements + i))->eventMatching(obj, ev) && ++i < numbOfElement);
    if(i < numbOfElement)
        return true;
    else {
        return QObject::eventFilter(obj, ev);
    }
}

void CommentList::addElement(CommentListElement *newElement){
    if(elements){
        CommentListElement **temp = new CommentListElement*[numbOfElements + 1];
        for(uint i = 0; i < numbOfElements; i++)
            (*(temp + i)) = (*(elements + i));
        (*(temp + numbOfElements)) = newElement;
        delete []elements;
        elements = temp;
        numbOfElements++;
    }else{
        elements = new CommentListElement*[1];
        *elements = newElement;
        numbOfElements++;
    }
    reallocate();
}

void CommentList::removeElement(CommentListElement *delElem){
    if(elements){
        if(numbOfElements > 1){
            bool removed = false;
            CommentListElement** temp = new CommentListElement*[numbOfElements - 1];
            for(uint i = 0; i < numbOfElements; i++)
                if(removed){
                    (*(temp + i - 1)) = (*(elements + i));
                }else{
                    if(*(elements + i) == delElem ){
                        delete (*(elements + i));
                        (*(elements + i)) = nullptr;
                        removed = true;
                    }else{
                        (*(temp + i)) = *(elements + i);
                    }
                }
            delete []elements;
            elements = temp;
        }else{
            delete (*elements);
            delete []elements;
            elements = nullptr;
        }
        numbOfElements--;
        reallocate();
    }
}

void CommentList::reallocate(){
    elementsHeight = OPERATION_ELEMENT_VERTICAL_SIDE_OFFSET;
    for(uint i = 0; i < numbOfElements; i++){
        (*(elements + i))->setGeometry(OPERATION_ELEMENT_HORIZONTAL_SIDE_OFFSET, elementsHeight, COMMENT_ELEMENT_WIDTH, (*(elements + i))->height());
        elementsHeight += (*(elements + i))->height() + OPERATION_ELEMENT_VERTICAL_SIDE_OFFSET;
        (*(elements + i))->show();
    }
    resize(COMMENT_LIST_WIDTH, elementsHeight);
    parent->reload(true);
}

