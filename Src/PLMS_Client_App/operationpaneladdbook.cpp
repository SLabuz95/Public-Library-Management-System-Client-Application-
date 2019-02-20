#include"operationpaneladdbook.hpp"
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

OperationPanelAddBook::OperationPanelAddBook(AppWindowLoggedInPanel* parent)
    : LoggedInOperationPanel(parent),
      addBookTitleLabel(this),
      scrollArea(this),
      dataPanel(this, nullptr, REGISTER_MODE),
      addButton(this),
      cancelButton(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

OperationPanelAddBook::~OperationPanelAddBook(){
    disconnectAll();
    deleteWidgets();
}

void OperationPanelAddBook::init(){
    // Empty
}

void OperationPanelAddBook::setWindow(){
    // Empty
}

void OperationPanelAddBook::createWidgets(){
    // Empty
}

void OperationPanelAddBook::createLayout(){
    // Register Title Label
    addBookTitleLabel.setText(OPERATION_PANEL_ADD_BOOK_TITLE_TEXT);
    addBookTitleLabel.setGeometry(OPERATION_PANEL_ADD_BOOK_TITLE_X, OPERATION_PANEL_ADD_BOOK_TITLE_Y, OPERATION_PANEL_ADD_BOOK_TITLE_WIDTH, OPERATION_PANEL_ADD_BOOK_TITLE_HEIGHT);
    addBookTitleLabel.setAlignment(Qt::AlignCenter);
    addBookTitleLabel.setStyleSheet(STYLESHEET_TITLE);

    // User Data Panel
    dataPanel.setGeometry(OPERATION_PANEL_ADD_BOOK_DATA_PANEL_X,OPERATION_PANEL_ADD_BOOK_DATA_PANEL_Y,OPERATION_PANEL_ADD_BOOK_DATA_PANEL_WIDTH,OPERATION_PANEL_ADD_BOOK_DATA_PANEL_HEIGHT);

    // Scroll Area
    scrollArea.setStyleSheet("QScrollArea{background-color: transparent;}");
    scrollArea.verticalScrollBar()->setStyleSheet("QScrollBar::vertical{background: transparent; width: 5px;} QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical, QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical, QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{border: none; background: none; color: none;} QScrollBar::handle:vertical{background-color: white; border: 1px solid black;}");
    scrollArea.setFrameShape(QFrame::NoFrame);
    scrollArea.setWidget(&dataPanel);
    scrollArea.setGeometry(OPERATION_PANEL_ADD_BOOK_DATA_PANEL_X,OPERATION_PANEL_ADD_BOOK_DATA_PANEL_Y,OPERATION_PANEL_ADD_BOOK_DATA_PANEL_WIDTH,OPERATION_PANEL_ADD_BOOK_DATA_PANEL_HEIGHT);
    scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea.show();

    // Add Book Button
    addButton.setGeometry(OPERATION_PANEL_ADD_BOOK_BUTTON_X, OPERATION_PANEL_ADD_BOOK_BUTTON_Y, OPERATION_PANEL_ADD_BOOK_BUTTON_WIDTH,OPERATION_PANEL_ADD_BOOK_BUTTON_HEIGHT);
    addButton.setText(OPERATION_PANEL_ADD_BOOK_ADD_BUTTON_TEXT);
    addButton.setAlignment(Qt::AlignCenter);
    addButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);

    // Cancel Button
    cancelButton.setText(OPERATION_PANEL_ADD_BOOK_CANCEL_BUTTON_TEXT);
    cancelButton.setGeometry(OPERATION_PANEL_ADD_BOOK_CANCEL_BUTTON_X,OPERATION_PANEL_ADD_BOOK_CANCEL_BUTTON_Y,OPERATION_PANEL_ADD_BOOK_CANCEL_BUTTON_WIDTH,OPERATION_PANEL_ADD_BOOK_CANCEL_BUTTON_HEIGHT);
    cancelButton.setAlignment(Qt::AlignCenter);
    cancelButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
}

void OperationPanelAddBook::deleteWidgets(){
    // Empty
}

void OperationPanelAddBook::connectAll(){
    // Register Button Connect
    addButton.installEventFilter(this);

    // Cancel Button Connect
    cancelButton.installEventFilter(this);

}

void OperationPanelAddBook::disconnectAll(){
    // Empty
}

void OperationPanelAddBook::reload(){
    createLayout();
}

bool OperationPanelAddBook::eventMatching(QObject* obj, QEvent* ev){
    switch (ev->type()) {
    case QEvent::MouseButtonRelease:
    {
        if(obj == &addButton){
            addButtonPressed();
            return true;
        }
        if(obj == &cancelButton){
            cancelButtonPressed();
            return true;
        }
    }
        break;
    case QEvent::Enter:
    {
        if(obj == &addButton){
            addButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
        if(obj == &cancelButton){
            cancelButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        if(obj == &addButton){
            addButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
        if(obj == &cancelButton){
            cancelButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, ev);
}

void OperationPanelAddBook::addButtonPressed(){
    if(!dataPanel.checkData()){
        Dialog dlg(QUESTION_DIALOG, QString("Błąd danych"), QString("Niepoprawnie wypełniony formularz."), nullptr, QString("Ok"));
        dlg.exec();
        return;
    }else{
        // Try to register
        Book* bookReg = dataPanel.getTempBook();
        // Create Json User
        {
            QJsonArray jA;
            QJsonArray jAUser;
            QJsonObject bookObj;
            bookReg->writeJson(bookObj);
            jA.append(bookObj);
            bookObj = QJsonObject();
            parent->getUser()->writeJson(bookObj);
            jAUser.append(bookObj);
            bookObj = QJsonObject();
            bookObj.insert(BOOK_JSON_KEY_TEXT, jA);
            bookObj.insert(USER_JSON_KEY_TEXT, jAUser);
            QJsonDocument jDoc(bookObj);
            bool stop = false;
            while(!stop){
                if(parent->getParent()->getParent()->getServer().getServerReplyStatus()){
                    SET_PTR_DO(bookReg, nullptr);
                    return;
                }
            ServerReplyStatus srs = parent->getParent()->getParent()->getServer().setLastRequest(COMMAND_TYPE_BOOK_ADD_TEXT, POST, jDoc);
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
                        if(obj.value(BOOK_JSON_KEY_TEXT) != QJsonValue::Undefined){
                            QJsonArray rjA = obj.value(BOOK_JSON_KEY_TEXT).toArray();
                            if(rjA.count() != 1){
                                //  Prompt Server Error
                                parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Podana książka już istnieje."));
                            }else{
                                Book* book = new Book(rjA.at(0).toObject());
                                if(book->getBookId() != 0 && book->checkBookParameters()){
                                    // Move to Logged In Stat
                                    parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_WARNING, QString("Dodano książkę o indeksie: ") + book->getParam(BOOK_ID));
                                    parent->setAppWindowLoggedInStatus(parent->getLastAppWindowLoggedInStat(), true);
                                }else{
                                    parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd przetwarzania danych - Dodawanie książki nieudane."));
                                }
                                SET_PTR_DO(book, nullptr);
                            }
                            // ______________________________________________________________________________________________________
                        }else{
                            //  Prompt Server Error
                            parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera - Dodawanie książki nieudane."));
                        }
                    }
                        break;
                        // _PH_ Check other errors
                    default:
                        //  Prompt Server Error
                        parent->getParent()->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - Dodawanie książki nieudane."));
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
        SET_PTR_DO(bookReg, nullptr);
    }
}

void OperationPanelAddBook::cancelButtonPressed(){
    parent->setAppWindowLoggedInStatus(parent->getLastAppWindowLoggedInStat(), true);
}

