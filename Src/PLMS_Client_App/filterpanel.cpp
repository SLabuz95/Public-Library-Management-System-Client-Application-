#include"filterpanel.hpp"
#include"filteredlist.hpp"
#include"filterpanelelement.hpp"
#include"appwindowloggedinpanel.hpp"
#include"bookpanel.hpp"
#include"operationpanelfilteredlist.hpp"
#include"loggedinoperationpanel.hpp"
#include<QTimer>
#include<QEvent>

FilterPanel::FilterPanel(FilteredList *parent)
    : QFrame(parent), parent(parent),filterTitle(this), addFilterButton(this), findButton(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
    setStyleSheet("FilterPanel{background-color: transparent;}");
}

FilterPanel::~FilterPanel(){
    switch(parent->getFilterType()){
    case FILE_TYPE_BOOKS_FILE:
    {
        BookFiltersLoggedInSave* savedBookFilters = nullptr;
        if(parent->getParent()->getBookPanelParent()){
            SET_PTR_NDO(savedBookFilters, parent->getParent()->getBookPanelParent()->getSavedBookFilters());
        }else{
            SET_PTR_NDO(savedBookFilters, parent->getParent()->getParent()->getSavedBookFilters());
        }
        for(uint i = 0; i < numbOfElements; i++){
            if(!(*(elements + i))->isCorrect())
            {
                removeElement((*(elements + i)));
                i--;
            }
        }
        savedBookFilters->numbOfFilters = numbOfElements;
        if(numbOfElements > 0){
            SET_PTR_DOA(savedBookFilters->bookFilters, new BooksFileFilter[numbOfElements]);
        }
        for(uint i = 0; i < numbOfElements; i++){
            (*(savedBookFilters->bookFilters + i)) = (*(elements + i))->getBookFileFilter();
        }
    }
        break;
    case FILE_TYPE_CLIENTS_FILE:
    {
        UserFiltersLoggedInSave* savedUserFilters = nullptr;
        SET_PTR_NDO(savedUserFilters, parent->getParent()->getParent()->getSavedUserFilters());
        for(uint i = 0; i < numbOfElements; i++){
            if(!(*(elements + i))->isCorrect())
            {
                removeElement((*(elements + i)));
                i--;
            }
        }
        savedUserFilters->numbOfFilters = numbOfElements;
        if(numbOfElements > 0){
            SET_PTR_DOA(savedUserFilters->userFilters, new ClientsFileFilter[numbOfElements]);
        }
        for(uint i = 0; i < numbOfElements; i++){
           (*(savedUserFilters->userFilters + i)) = (*(elements + i))->getClientFileFilter();
        }
    }
        break;
    case FILE_TYPE_BOOK_LOG_FILE:
    {
        BookLogFiltersLoggedInSave* savedBookLogFilters = nullptr;
        SET_PTR_NDO(savedBookLogFilters, parent->getParent()->getParent()->getSavedBookLogFilters());
        for(uint i = 0; i < numbOfElements; i++){
            if(!(*(elements + i))->isCorrect())
            {
                removeElement((*(elements + i)));
                i--;
            }
        }
        savedBookLogFilters->numbOfFilters = numbOfElements;
        if(numbOfElements > 0){
            SET_PTR_DOA(savedBookLogFilters->bookLogFilters, new BookLogsFileFilter[numbOfElements]);
        }
        for(uint i = 0; i < numbOfElements; i++){
           (*(savedBookLogFilters->bookLogFilters + i)) = (*(elements + i))->getBookLogFileFilter();
        }
    }
        break;
    default:
        break;
    }
    disconnectAll();
    deleteWidgets();
}

void FilterPanel::init(){
    // Empty
}

void FilterPanel::setWindow(){
    resize(FILTER_PANEL_WIDTH,FILTER_TITLE_HEIGHT + 2 * FILTER_ELEMENT_VERTICAL_OFFSET + FILTER_ELEMENT_BUTTON_HEIGHT + elementsHeight);
}

void FilterPanel::createWidgets(){
    // Create Elements
    switch(parent->getFilterType()){
    case FILE_TYPE_BOOKS_FILE:
    {
        BookFiltersLoggedInSave* savedBookFilters = nullptr;
        if(parent->getParent()->getBookPanelParent()){
            SET_PTR_NDO(savedBookFilters, parent->getParent()->getBookPanelParent()->getSavedBookFilters());
        }else{
            SET_PTR_NDO(savedBookFilters, parent->getParent()->getParent()->getSavedBookFilters());
        }
        uint numbOfElement = savedBookFilters->numbOfFilters;
        for(uint i = 0; i < numbOfElement; i++){
            addElement(new FilterPanelElement(this, i, savedBookFilters->bookFilters + i));
        }
    }
        break;
    case FILE_TYPE_CLIENTS_FILE:
    {
        UserFiltersLoggedInSave* savedUserFilters = nullptr;
        SET_PTR_NDO(savedUserFilters,parent->getParent()->getParent()->getSavedUserFilters());
        uint numbOfElement = savedUserFilters->numbOfFilters;
        for(uint i = 0; i < numbOfElement; i++){
            addElement(new FilterPanelElement(this, i, savedUserFilters->userFilters +i));
        }
    }
        break;
    case FILE_TYPE_BOOK_LOG_FILE:
    {
        BookLogFiltersLoggedInSave* savedBookLogFilters = nullptr;
        SET_PTR_NDO(savedBookLogFilters, parent->getParent()->getParent()->getSavedBookLogFilters());
        uint numbOfElement = savedBookLogFilters->numbOfFilters;
        for(uint i = 0; i < numbOfElement; i++){
            addElement(new FilterPanelElement(this, i, savedBookLogFilters->bookLogFilters +i));
        }
    }
        break;
    default:
        break;
    }
}

void FilterPanel::createLayout(){
    // Title
    filterTitle.setText(FILTER_TITLE_TEXT);
    filterTitle.setGeometry(FILTER_TITLE_X, FILTER_TITLE_Y,FILTER_TITLE_WIDTH,FILTER_TITLE_HEIGHT);
    filterTitle.setAlignment(Qt::AlignCenter);
    filterTitle.setStyleSheet(STYLESHEET_TITLE);

    // Add Button
    addFilterButton.setText(FILTER_ADD_FILTER_BUTTON_TEXT);
    addFilterButton.setGeometry(FILTER_ELEMENT_BUTTON_WIDTH + FILTER_ELEMENT_HORIZONTAL_OFFSET, FILTER_TITLE_HEIGHT + elementsHeight + FILTER_ELEMENT_VERTICAL_OFFSET, FILTER_ELEMENT_BUTTON_WIDTH_CALC(2), FILTER_ELEMENT_BUTTON_HEIGHT);
    addFilterButton.setAlignment(Qt::AlignCenter);
    addFilterButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);

    // Find Button
    findButton.setText(FILTER_FIND_BUTTON_TEXT);
    findButton.setGeometry(FILTER_ELEMENT_BUTTON_WIDTH + 2 * FILTER_ELEMENT_HORIZONTAL_OFFSET + addFilterButton.width(), FILTER_TITLE_HEIGHT + elementsHeight + FILTER_ELEMENT_VERTICAL_OFFSET, FILTER_ELEMENT_BUTTON_WIDTH_CALC(2), FILTER_ELEMENT_BUTTON_HEIGHT);
    findButton.setAlignment(Qt::AlignCenter);
    findButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
}

void FilterPanel::deleteWidgets(){
    for(uint i = 0; i < numbOfElements; i++)
        SET_PTR_DO((*(elements + i)), nullptr);
    SET_PTR_DOA(elements, nullptr);
}

void FilterPanel::connectAll(){
    addFilterButton.installEventFilter(parent);
    findButton.installEventFilter(parent);
}

void FilterPanel::disconnectAll(){
    // Empty
}

FilteredList* FilterPanel::getParent(){
    return parent;
}

void FilterPanel::addElement(FilterPanelElement *newElement){
    if(elements){
        FilterPanelElement **temp = new FilterPanelElement*[numbOfElements + 1];
        for(uint i = 0; i < numbOfElements; i++)
            (*(temp + i)) = (*(elements + i));
        (*(temp + numbOfElements)) = newElement;
        delete []elements;
        elements = temp;
        numbOfElements++;
    }else{
        elements = new FilterPanelElement*[1];
        *elements = newElement;
        numbOfElements++;
    }
    reallocate();
}


void FilterPanel::removeElement(FilterPanelElement *delElem){
    if(elements){
        if(numbOfElements > 1){
            bool removed = false;
            FilterPanelElement** temp = new FilterPanelElement*[numbOfElements - 1];
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

void FilterPanel::reallocate(){
    elementsHeight = 0;
    for(uint i = 0; i < numbOfElements; i++){
        (*(elements + i))->setGeometry(0, FILTER_TITLE_HEIGHT + elementsHeight, FILTER_ELEMENT_WIDTH, (*(elements + i))->height());
        elementsHeight += (*(elements + i))->height();
        (*(elements + i))->show();
    }
    setWindow();
    createLayout();
    parent->reload(true);

}

bool FilterPanel::eventMatching(QObject *obj, QEvent *ev){
    switch(ev->type()){
    case QEvent::MouseButtonRelease:
    {
        if(obj == &addFilterButton){
            addFilterButtonPressed();
            return true;
        }
        if(obj == &findButton){
            findButtonPressed();
            return true;
        }
        uint i = 0;
        uint numbOfElement = numbOfElements;
        if(numbOfElement > 0)
            while(!(*(elements + i))->eventMatching(obj, ev) && ++i < numbOfElement);
        if(i < numbOfElement)
            return true;
        else {
            return false;
        }
    }
    case QEvent::Enter:
    {
        if(obj == &addFilterButton){
            addFilterButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
        if(obj == &findButton){
            findButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
        uint i = 0;
        uint numbOfElement = numbOfElements;
        if(numbOfElement > 0)
            while(!(*(elements + i))->eventMatching(obj, ev) && ++i < numbOfElement);
        if(i < numbOfElement)
            return true;
        else {
            return false;
        }
    }
    case QEvent::KeyPress:
    case QEvent::Leave:
    {
        if(obj == &addFilterButton){
            addFilterButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
        if(obj == &findButton){
            findButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
        uint i = 0;
        uint numbOfElement = numbOfElements;
        if(numbOfElement > 0)
            while(!(*(elements + i))->eventMatching(obj, ev) && ++i < numbOfElement);
        if(i < numbOfElement)
            return true;
        else {
            return false;
        }
    }
    default:
        break;
    }
    return false;
}

void FilterPanel::addFilterButtonPressed(){
    for(uint i = 0; i < numbOfElements; i++)
        if(!(*(elements + i))->isCorrect()){
            blinkFilterElement(i);
            return;
        }
    addElement(new FilterPanelElement(this,numbOfElements));
}

void FilterPanel::findButtonPressed(){
    blinkPossible = false;
    switch(parent->getFilterType()){
    case FILE_TYPE_BOOKS_FILE:
    {
        BookFiltersLoggedInSave* savedBookFilters = nullptr;
        if(parent->getParent()->getBookPanelParent()){
            SET_PTR_NDO(savedBookFilters, parent->getParent()->getBookPanelParent()->getSavedBookFilters());
        }else{
            SET_PTR_NDO(savedBookFilters, parent->getParent()->getParent()->getSavedBookFilters());
        }
        for(uint i = 0; i < numbOfElements; i++){
            if(!(*(elements + i))->isCorrect())
            {
                removeElement((*(elements + i)));
                i--;
            }
        }
        savedBookFilters->numbOfFilters = numbOfElements;
        if(numbOfElements > 0){
            SET_PTR_DOA(savedBookFilters->bookFilters, new BooksFileFilter[numbOfElements]);
        }
        for(uint i = 0; i < numbOfElements; i++){
            (*(savedBookFilters->bookFilters + i)) = (*(elements + i))->getBookFileFilter();
        }
    }
        break;
    case FILE_TYPE_CLIENTS_FILE:
    {
        UserFiltersLoggedInSave* savedUserFilters = nullptr;
        SET_PTR_NDO(savedUserFilters, parent->getParent()->getParent()->getSavedUserFilters());
        for(uint i = 0; i < numbOfElements; i++){
            if(!(*(elements + i))->isCorrect())
            {
                removeElement((*(elements + i)));
                i--;
            }
        }
        savedUserFilters->numbOfFilters = numbOfElements;
        if(numbOfElements > 0){
            SET_PTR_DOA(savedUserFilters->userFilters, new ClientsFileFilter[numbOfElements]);
        }
        for(uint i = 0; i < numbOfElements; i++){
           (*(savedUserFilters->userFilters + i)) = (*(elements + i))->getClientFileFilter();
        }
    }
        break;
    case FILE_TYPE_BOOK_LOG_FILE:
    {
        BookLogFiltersLoggedInSave* savedBookLogFilters = nullptr;
        SET_PTR_NDO(savedBookLogFilters, parent->getParent()->getParent()->getSavedBookLogFilters());
        for(uint i = 0; i < numbOfElements; i++){
            if(!(*(elements + i))->isCorrect())
            {
                removeElement((*(elements + i)));
                i--;
            }
        }
        savedBookLogFilters->numbOfFilters = numbOfElements;
        if(numbOfElements > 0){
            SET_PTR_DOA(savedBookLogFilters->bookLogFilters, new BookLogsFileFilter[numbOfElements]);
        }
        for(uint i = 0; i < numbOfElements; i++){
           (*(savedBookLogFilters->bookLogFilters + i)) = (*(elements + i))->getBookLogFileFilter();
        }
    }
        break;
    default:
        break;
    }
    setWindow();
    createLayout();
    if(parent->getParent()->getBookPanelParent())
        parent->getParent()->getBookPanelParent()->reload(false);
    else
        parent->reload(false);

}

void FilterPanel::blinkFilterElement(uint index){
    blinkPossible = true;
    (*(elements + index))->setStyleSheet("FilterPanelElement{background-color: white;}");
    QTimer::singleShot(500, this, [this, index](){this->lowlightFilterElement(index);});
}

void FilterPanel::lowlightFilterElement(uint index){
    if(blinkPossible){
        (*(elements + index))->setStyleSheet("FilterPanelElement{}");
    }
}
