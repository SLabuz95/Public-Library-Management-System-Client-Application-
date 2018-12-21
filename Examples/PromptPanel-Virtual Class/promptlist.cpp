#include"promptlist.hpp"
#include"promptpanel.hpp"
#include"windowmacros.hpp"
#include"promptelement.hpp"


PromptList::PromptList(PromptPanel *parent)
    : parent(parent){
 init();
 setWindow();
 createWidgets();
 createLayout();
 connectAll();
}

PromptList::~PromptList(){
    disconnectAll();
    deleteWidgets();
}

void PromptList::init(){

}

void PromptList::setWindow(){

}

void PromptList::createWidgets(){
    // Brak
}

void PromptList::createLayout(){
    // Brak
}

void PromptList::deleteWidgets(){
    if(promptElements){
        while(numbOfElements-- == 0)
            delete (*(promptElements + numbOfElements));
        delete []promptElements;
        promptElements = nullptr;
    }
}

void PromptList::connectAll(){
    // Brak
}

void PromptList::disconnectAll(){
    // Brak
}

PromptPanel* PromptList::getParent(){
    return parent;
}

PromptElement** PromptList::getPromptElements(){
    return promptElements;
}

uint PromptList::getNumbOfElements(){
    return numbOfElements;
}

void PromptList::addElement(PromptElement *newElement){
    if(promptElements){
        PromptElement **temp = new PromptElement*[numbOfElements + 1];
        for(uint i = 0; i < numbOfElements; i++)
            (*(temp + i + 1)) = (*(promptElements + i));
        (*temp) = newElement;
        delete []promptElements;
        promptElements = temp;
        numbOfElements++;
    }else{
        promptElements = new PromptElement*[1];
        *promptElements = newElement;
        numbOfElements++;
    }
    reallocate();
    parent->reload(true);
    parent->writeNumbOfPrompts();
}

void PromptList::deleteElement(PromptElement *delElem){
    if(promptElements){
        if(numbOfElements > 1){
            bool removed = false;
            PromptElement** temp = new PromptElement*[numbOfElements - 1];
            for(uint i = 0; i < numbOfElements; i++)
                if(removed){
                    (*(temp + i - 1)) = (*(promptElements + i));
                }else{
                    if(*(promptElements + i) == delElem ){
                        delete (*(promptElements + i));
                        (*(promptElements + i)) = nullptr;
                        removed = true;
                    }else{
                        (*(temp + i)) = *(promptElements + i);
                    }
                }
            delete []promptElements;
            promptElements = temp;
        }else{
            delete (*promptElements);
            delete []promptElements;
            promptElements = nullptr;
        }
        numbOfElements--;
        reallocate();
    }
    parent->writeNumbOfPrompts();
}

void PromptList::deleteElement(uint index){
    if(promptElements){
        if(numbOfElements > 1){
            PromptElement** temp = new PromptElement*[numbOfElements - 1];
            for(uint i = 0; i < numbOfElements; i++)
                if(i < index){
                    (*(temp + i)) = *(promptElements + i);
                }else{
                    if(i != index){
                        (*(temp + i - 1)) = (*(promptElements + i));
                   }
                    else{
                        delete (*(promptElements + i));
                        (*(promptElements + i)) = nullptr;
                    }
                }
            delete []promptElements;
            promptElements = temp;
         }else{
            delete (*promptElements);
            delete []promptElements;
            promptElements = nullptr;
         }
        numbOfElements--;
        reallocate();
    }
    parent->writeNumbOfPrompts();
}

void PromptList::reallocate(){
    uint y = 0;
    for(uint i = 0; i < numbOfElements; i++){
        (*(promptElements + i))->setGeometry(0, y, PROMPT_ELEMENT_WIDTH, (*(promptElements + i))->height());
        y += (*(promptElements + i))->height();
        (*(promptElements + i))->show();
    }
    if(y == 0){
        parent->setStatus(PROMPT_PANEL_HIDDEN);
    }else{
       resize(PROMPT_LIST_WIDTH, y);
    }
}

void PromptList::matchEvents(QObject *obj, QEvent *ev){
    uint i = 0;
    while(!(*(promptElements + i))->eventMatching(obj, ev) && i++ < numbOfElements);
}
