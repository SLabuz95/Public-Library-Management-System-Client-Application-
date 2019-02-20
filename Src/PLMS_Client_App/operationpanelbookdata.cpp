#include"operationpanelbookdata.hpp"
#include<QLineEdit>
#include<QKeyEvent>
#include"appwindowloggedinpanel.hpp"
#include"app.hpp"
#include<QScrollBar>
#include"dialog.hpp"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include"../PLMS_Server_App/book.hpp"
#include"../PLMS_Server_App/user.hpp"

OperationPanelBookData::OperationPanelBookData(AppWindowLoggedInPanel* parent)
    : LoggedInOperationPanel(parent),
      bookDataTitleLabel(this),
      scrollArea(this),
      dataPanel(this, parent->getBookDataPtr(), DATA_MODE),
      changeDataButton(this),
      removeButton(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationPanelBookData::~OperationPanelBookData(){
    disconnectAll();
    deleteWidgets();
}

void OperationPanelBookData::init(){
    // Empty
}

void OperationPanelBookData::setWindow(){
    // Empty
}

void OperationPanelBookData::createWidgets(){
    // Empty
}

void OperationPanelBookData::createLayout(){
    // Register Title Label
    bookDataTitleLabel.setText(OPERATION_PANEL_BOOK_DATA_TITLE_TEXT);
    bookDataTitleLabel.setGeometry(OPERATION_PANEL_BOOK_DATA_TITLE_X,OPERATION_PANEL_BOOK_DATA_TITLE_Y,OPERATION_PANEL_BOOK_DATA_TITLE_WIDTH,OPERATION_PANEL_BOOK_DATA_TITLE_HEIGHT);
    bookDataTitleLabel.setStyleSheet(STYLESHEET_TITLE);
    bookDataTitleLabel.setAlignment(Qt::AlignCenter);

    // Book Data Panel
    dataPanel.setGeometry(OPERATION_PANEL_BOOK_DATA_PANEL_X,OPERATION_PANEL_BOOK_DATA_PANEL_Y,OPERATION_PANEL_BOOK_DATA_PANEL_WIDTH,OPERATION_PANEL_BOOK_DATA_PANEL_HEIGHT);

    // Scroll Area
    scrollArea.setStyleSheet("QScrollArea{background-color: transparent;}");
    scrollArea.verticalScrollBar()->setStyleSheet("QScrollBar::vertical{background: transparent; width: 5px;} QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical, QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical, QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{border: none; background: none; color: none;} QScrollBar::handle:vertical{background-color: white; border: 1px solid black;}");
    scrollArea.setFrameShape(QFrame::NoFrame);
    scrollArea.setWidget(&dataPanel);
    scrollArea.setGeometry(OPERATION_PANEL_BOOK_DATA_PANEL_X,OPERATION_PANEL_BOOK_DATA_PANEL_Y,OPERATION_PANEL_BOOK_DATA_PANEL_WIDTH,OPERATION_PANEL_BOOK_DATA_PANEL_HEIGHT);
    scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea.show();

    // Change Data Button
    changeDataButton.setGeometry(OPERATION_PANEL_CHANGE_DATA_BOOK_DATA_BUTTON_X,OPERATION_PANEL_CHANGE_DATA_BOOK_DATA_BUTTON_Y,OPERATION_PANEL_CHANGE_DATA_BOOK_DATA_BUTTON_WIDTH,OPERATION_PANEL_CHANGE_DATA_BOOK_DATA_BUTTON_HEIGHT);
    changeDataButton.setText(OPERATION_PANEL_CHANGE_DATA_USER_DATA_BUTTON_TEXT);
    changeDataButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    changeDataButton.setAlignment(Qt::AlignCenter);

    // Remove Button
    removeButton.setText(OPERATION_PANEL_REMOVE_BOOK_DATA_BUTTON_TEXT);
    removeButton.setGeometry(OPERATION_PANEL_BOOK_DATA_CANCEL_BUTTON_X,OPERATION_PANEL_BOOK_DATA_CANCEL_BUTTON_Y,OPERATION_PANEL_BOOK_DATA_CANCEL_BUTTON_WIDTH,OPERATION_PANEL_BOOK_DATA_CANCEL_BUTTON_HEIGHT);
    removeButton.setAlignment(Qt::AlignCenter);
    removeButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
}

void OperationPanelBookData::deleteWidgets(){
    // Empty
}

void OperationPanelBookData::connectAll(){
    // Register Button Connect
    changeDataButton.installEventFilter(this);

    // Remove Button Connect
    removeButton.installEventFilter(this);

}

void OperationPanelBookData::disconnectAll(){
    // Empty
}

void OperationPanelBookData::reload(){
    createLayout();
}

bool OperationPanelBookData::eventMatching(QObject* obj, QEvent* ev){
    switch (ev->type()) {
    case QEvent::MouseButtonRelease:
    {
        if(obj == &changeDataButton){
            changeDataButtonPressed();
            return true;
        }
        if(obj == &removeButton){
            removeButtonPressed();
            return true;
        }
    }
        break;
    case QEvent::Enter:
    {
        if(obj == &changeDataButton){
            changeDataButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
        if(obj == &removeButton){
            removeButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &changeDataButton){
            changeDataButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
        if(obj == &removeButton){
            removeButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, ev);
}

void OperationPanelBookData::changeDataButtonPressed(){
    if(dataPanel.getMode() < DATA_MODE){
        if(!dataPanel.checkData()){
            Dialog dlg(QUESTION_DIALOG, QString("Błąd danych"), QString("Niepoprawnie wypełniony formularz."), nullptr, QString("Ok"));
            dlg.exec();
            return;
        }else{
            // Try to register
            Book* bookEdit = dataPanel.getTempBook();
            if(dataPanel.getBook()){
                bookEdit->setBookId(dataPanel.getBook()->getBookId());
            }else {
                Dialog dlg(QUESTION_DIALOG, QString("Błąd programu"), QString("Błąd pamięci programu"), nullptr, QString("Ok"));
                dlg.exec();
                SET_PTR_DO(bookEdit, nullptr);
                return;
            }
            // Create Json User
            {
                QJsonArray jA;
                QJsonObject bookObj;
                bookEdit->writeJson(bookObj);
                jA.append(bookObj);
                bookObj = QJsonObject();
                bookObj.insert(BOOK_JSON_KEY_TEXT, jA);
                QJsonDocument jDoc(bookObj);
                bool stop = false;
                while(!stop){
                    if(parent->getParent()->getParent()->getServer().getServerReplyStatus()){
                        SET_PTR_DO(bookEdit, nullptr);
                        return;
                    }
                ServerReplyStatus srs = parent->getParent()->getParent()->getServer().setLastRequest(COMMAND_TYPE_BOOK_EDIT_TEXT, POST, jDoc);
                switch (srs) {
                case SERVER_NO_ERROR:
                {
                    parent->getParent()->getPromptPanel().setServerStatusConnection();
                    QJsonObject obj = parent->getParent()->getParent()->getServer().readAll();
                    if(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT) != QJsonValue::Undefined){
                        switch(static_cast<ReturnErrorType>(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt())){
                        case RETURN_ERROR_NO_ERROR:
                        {
                            // ______________________________________________________________________________________________________
                            parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_WARNING, QString("Edycja danych udana."));
                            if(dataPanel.getBook())
                                dataPanel.getBook()->merge(*bookEdit);
                            changeDataButton.setText(OPERATION_PANEL_CHANGE_DATA_BOOK_DATA_BUTTON_TEXT);
                            removeButton.setText(OPERATION_PANEL_REMOVE_BOOK_DATA_BUTTON_TEXT);
                            dataPanel.changeMode(DATA_MODE);
                            // ______________________________________________________________________________________________________

                        }
                            break;
                            // _PH_ Check other errors
                        default:
                            //  Prompt Server Error
                            parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - Edycja książki nieudana."));
                            break;
                        }
                    }
                    // _____________________________________________________________________________________________________________
                   stop = true;
                   parent->getParent()->getParent()->getServer().clearStatus();
                }
                    break;
                case SERVER_NETWORK_ERROR:
                {
                    // __________________________________________________________________________________
                    QNetworkReply::NetworkError error = parent->getParent()->getParent()->getServer().getNetworkError();
                    if(error == QNetworkReply::ConnectionRefusedError || error == QNetworkReply::TimeoutError){
                        parent->getParent()->getPromptPanel().setServerStatusNoConnection();
                    }
                    // ____________________________________________________________________________________
                    stop = true;
                    parent->getParent()->getParent()->getServer().clearStatus();
                }
                    break;
                case SERVER_READY:
                    stop = true;
                    parent->getParent()->getParent()->getServer().clearStatus();
                    break;
                default:
                    break;
                }
               }
            }
            SET_PTR_DO(bookEdit, nullptr);
        }
    }else{
        changeDataButton.setText(OPERATION_PANEL_BOOK_DATA_ACCEPT_BUTTON_TEXT);
        removeButton.setText(OPERATION_PANEL_BOOK_DATA_CANCEL_BUTTON_TEXT);
        dataPanel.changeMode(EDITABLE_MODE);
    }
}

void OperationPanelBookData::removeButtonPressed(){
    if(dataPanel.getMode() == EDITABLE_MODE){
        changeDataButton.setText(OPERATION_PANEL_CHANGE_DATA_BOOK_DATA_BUTTON_TEXT);
        removeButton.setText(OPERATION_PANEL_REMOVE_BOOK_DATA_BUTTON_TEXT);
        dataPanel.changeMode(DATA_MODE);
    }else{
        // Try to remove account
        Dialog dlg(QUESTION_DIALOG, QString("Usuwanie książki"), QString("Jesteś pewny, że chcesz usunąć książkę?"), nullptr, QString("Tak"), QString("Nie"));
        switch(dlg.exec()){
        case FIRST_OPTION_RESULT:
        {
            // Try to remove account
            Book *bookRem = nullptr;
            if(dataPanel.getBook())
                bookRem = dataPanel.getBook();
            else {
                Dialog dlg(QUESTION_DIALOG, QString("Błąd programu"), QString("Błąd pamięci programu"), nullptr, QString("Ok"));
                dlg.exec();
                return;
            }
                // Create Json User
                    QJsonArray jA;
                    QJsonArray jAUser;
                    QJsonObject userObj;
                    bookRem->writeJson(userObj);
                    jA.append(userObj);
                    userObj = QJsonObject();
                    parent->getUser()->writeJson(userObj);
                    jAUser.append(userObj);
                    userObj = QJsonObject();
                    userObj.insert(BOOK_JSON_KEY_TEXT, jA);
                    userObj.insert(USER_JSON_KEY_TEXT, jAUser);
                    QJsonDocument jDoc(userObj);
                    bool stop = false;
                    while(!stop){
                        if(parent->getParent()->getParent()->getServer().getServerReplyStatus())
                            return;
                    ServerReplyStatus srs = parent->getParent()->getParent()->getServer().setLastRequest(COMMAND_TYPE_BOOK_REMOVE_TEXT, POST, jDoc);
                    switch (srs) {
                    case SERVER_NO_ERROR:
                    {
                        parent->getParent()->getPromptPanel().setServerStatusConnection();
                        QJsonObject obj = parent->getParent()->getParent()->getServer().readAll();
                        if(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT) != QJsonValue::Undefined){
                            switch(static_cast<ReturnErrorType>(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt())){
                            case RETURN_ERROR_NO_ERROR:
                            {
                                // ______________________________________________________________________________________________________
                                parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_WARNING, QString("Usuwanie książki udane."));
                                // Logout Application
                                parent->setAppWindowLoggedInStatus(parent->getLastAppWindowLoggedInStat(), true);
                                // __________________________________________________________________
                            }
                                break;
                                // _PH_ Check other errors
                                default:
                                //  Prompt Server Error
                                parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - Usuwanie książki nieudane."));
                                break;
                            }
                        }
                        // _____________________________________________________________________________________________________________
                       stop = true;
                       parent->getParent()->getParent()->getServer().clearStatus();
                    }
                        break;
                    case SERVER_NETWORK_ERROR:
                    {
                        // __________________________________________________________________________________
                        QNetworkReply::NetworkError error = parent->getParent()->getParent()->getServer().getNetworkError();
                        if(error == QNetworkReply::ConnectionRefusedError || error == QNetworkReply::TimeoutError){
                            parent->getParent()->getPromptPanel().setServerStatusNoConnection();
                        }
                        // ____________________________________________________________________________________
                        stop = true;
                        parent->getParent()->getParent()->getServer().clearStatus();
                    }
                        break;
                    case SERVER_READY:
                        stop = true;
                        parent->getParent()->getParent()->getServer().clearStatus();
                        break;
                    default:
                        break;
                    }
                   }
        }
            break;
        case SECOND_OPTION_RESULT:
        {
            return;
        }
        default:
            break;
        }
    }
}

