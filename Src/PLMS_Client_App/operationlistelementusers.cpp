#include"operationlistelementusers.hpp"
#include"operationlist.hpp"
#include<QEvent>
#include<QLabel>
#include"filteredlist.hpp"
#include"operationpanelfilteredlist.hpp"
#include"../PLMS_Server_App/user.hpp"
#include<QFontMetrics>
#include"dialog.hpp"
#include"operationpanelfilteredlist.hpp"
#include"appwindowloggedinpanel.hpp"
#include"appwindow.hpp"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include"promptpanel.hpp"
#include"server.hpp"
#include"app.hpp"

OperationListElementUsers::OperationListElementUsers(OperationList *parent, User* user)
    : OperationListElement(parent), user(user), bookMenagerButton(this), readerDataButton(this), removeUserButton(this){
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();

}

OperationListElementUsers::~OperationListElementUsers(){
    disconnectAll();
    deleteWidgets();
}

void OperationListElementUsers::init(){
    generateText();
    bookMenagerButton.setText("Panel książek");
    readerDataButton.setText("Dane użytkownika");
    removeUserButton.setText("Usuń użytkownika");
    bookMenagerButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    readerDataButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    removeUserButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
    if(user->getUserPermissions() == USER_PERMISSIONS_READER){
            bookMenagerButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(3), OPERATION_ELEMENT_BUTTON_HEIGHT);
            readerDataButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(3), OPERATION_ELEMENT_BUTTON_HEIGHT);
            removeUserButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(3), OPERATION_ELEMENT_BUTTON_HEIGHT);
    }else{
        removeUserButton.resize(OPERATION_ELEMENT_BUTTON_WIDTH_CALC(2), OPERATION_ELEMENT_BUTTON_HEIGHT);
    }
    bookMenagerButton.setAlignment(Qt::AlignCenter);
    readerDataButton.setAlignment(Qt::AlignCenter);
    removeUserButton.setAlignment(Qt::AlignCenter);
}

void OperationListElementUsers::setWindow(){
    resize(OPERATION_ELEMENT_WIDTH,generalInfoLabel.height() + 3 * OPERATION_ELEMENT_VERTICAL_OFFSET + OPERATION_ELEMENT_BUTTON_HEIGHT);
    }

void OperationListElementUsers::createWidgets(){
    // Brak
}

void OperationListElementUsers::createLayout(){
    if(user->getUserPermissions() == USER_PERMISSIONS_READER){
                bookMenagerButton.move(OPERATION_ELEMENT_BUTTON_WIDTH + OPERATION_ELEMENT_HORIZONTAL_OFFSET, generalInfoLabel.height() + 2 * OPERATION_ELEMENT_VERTICAL_OFFSET);
                readerDataButton.move(OPERATION_ELEMENT_BUTTON_WIDTH + OPERATION_ELEMENT_HORIZONTAL_OFFSET * 2 + bookMenagerButton.width() , bookMenagerButton.y());
                removeUserButton.move(OPERATION_ELEMENT_BUTTON_WIDTH + OPERATION_ELEMENT_HORIZONTAL_OFFSET * 3 + bookMenagerButton.width() + readerDataButton.width() , bookMenagerButton.y());
                bookMenagerButton.show();
                readerDataButton.show();
                removeUserButton.show();
            }else{
                readerDataButton.move(OPERATION_ELEMENT_BUTTON_WIDTH + OPERATION_ELEMENT_HORIZONTAL_OFFSET, generalInfoLabel.height() + OPERATION_ELEMENT_VERTICAL_OFFSET);
                removeUserButton.move(OPERATION_ELEMENT_BUTTON_WIDTH + OPERATION_ELEMENT_HORIZONTAL_OFFSET * 2 + readerDataButton.width() , readerDataButton.y());
                removeUserButton.show();
                bookMenagerButton.hide();
                readerDataButton.hide();
                if(user->getUserId() == parent->getParent()->getParent()->getParent()->getUser()->getUserId()){
                    removeUserButton.hide();                    
                    resize(OPERATION_ELEMENT_WIDTH,generalInfoLabel.height() + 2 * OPERATION_ELEMENT_VERTICAL_OFFSET);
                }
            }
}

void OperationListElementUsers::deleteWidgets(){
    // Brak
}

void OperationListElementUsers::connectAll(){
    bookMenagerButton.installEventFilter(parent->getParent());
    readerDataButton.installEventFilter(parent->getParent());
    removeUserButton.installEventFilter(parent->getParent());
}

void OperationListElementUsers::disconnectAll(){
    // Brak
}

void OperationListElementUsers::generateText(){
    QString userPerm;
    switch(user->getUserPermissions()){
    case USER_PERMISSIONS_ADMIN:
        userPerm = "Administrator";
        break;
    case USER_PERMISSIONS_READER:
        userPerm = "Czytelnik";
        break;
    case USER_PERMISSIONS_LIBRARIAN:
        userPerm = "Bibliotekarz";
        break;
    default:
        break;
    }    
    QString text = TEXT_GENERATOR_ELEMENT_USER;
    uint newHeight = generalInfoLabel.fontMetrics().boundingRect(0,0, OPERATION_ELEMENT_GENERAL_INFO_LABEL_WIDTH, 1200, Qt::TextWordWrap, text).height();
        generalInfoLabel.resize(OPERATION_ELEMENT_GENERAL_INFO_LABEL_WIDTH, (newHeight < OPERATION_ELEMENT_BUTTON_HEIGHT)? OPERATION_ELEMENT_ERROR_LABEL_HEIGHT + 2 : newHeight);
        generalInfoLabel.setText(text);
    }

void OperationListElementUsers::reload(){
    disconnectAll();
    deleteWidgets();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

bool OperationListElementUsers::eventMatching(QObject *obj, QEvent *ev){
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
        if(obj == &removeUserButton){
            removeUserButtonPressed();
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
        if(obj == &removeUserButton){
            removeUserButton.setStyleSheet(STYLESHEET_BUTTON_HIGHLIGHT);
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
        if(obj == &removeUserButton){
            removeUserButton.setStyleSheet(STYLESHEET_BUTTON_LOWLIGHT);
            break;
        }
    }
        break;
        default:
            break;

    }
    return false;
}

void OperationListElementUsers::bookMenagerButtonPressed(){
    Dialog dlg(BOOK_PANEL, user, parent->getParent()->getParent()->getParent());
    dlg.exec();
    parent->getParent()->reload(false);
}

void OperationListElementUsers::readerDataButtonPressed(){
    parent->getParent()->getParent()->getParent()->setAppWindowLoggedInStatus(LOGGED_IN_PANEL_USER_DATA_STAT, user);
}

void OperationListElementUsers::removeUserButtonPressed(){
    // Try to remove from server
    AppWindow* appWindow = parent->getParent()->getParent()->getParent()->getParent();
    parent->nextPageAvailable = false;
    Dialog dlg(QUESTION_DIALOG, QString("Usuwanie użytkownika"), QString("Jesteś pewny, że chcesz usunąć użytkownika?"), nullptr, QString("Tak"), QString("Nie"));
    switch(dlg.exec()){
    case FIRST_OPTION_RESULT:
    {
        // Try to remove account
                // Create Json User
                QJsonArray jA;
                QJsonObject userObj;
                user->writeJson(userObj);
                jA.append(userObj);
                userObj = QJsonObject();
                userObj.insert(USER_JSON_KEY_TEXT, jA);
                QJsonDocument jDoc(userObj);
                bool stop = false;
                while(!stop){
                    if(appWindow->getParent()->getServer().getServerReplyStatus())
                        return;
                ServerReplyStatus srs = appWindow->getParent()->getServer().setLastRequest(COMMAND_TYPE_CLIENT_REMOVE_TEXT, POST, jDoc);
                switch (srs) {
                case SERVER_NO_ERROR:
                {
                    appWindow->getPromptPanel().setServerStatusConnection();
                    QJsonObject obj = appWindow->getParent()->getServer().readAll();
                    if(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT) != QJsonValue::Undefined){
                        switch(static_cast<ReturnErrorType>(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt())){
                        case RETURN_ERROR_NO_ERROR:
                        {
                            // ______________________________________________________________________________________________________
                            appWindow->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_WARNING, QString("Usuwanie konta udane."));
                            parent->getParent()->reload(false);
                            // __________________________________________________________________
                        }
                            break;
                            // _PH_ Check other errors
                            default:
                            //  Prompt Server Error
                            appWindow->getPromptPanel().addPrompt(PROMPT_TYPE_STANDARD_ERROR, QString("Błąd serwera #" + QString::number(obj.value(RETURN_ERROR_JSON_VARIABLE_TEXT).toString().toUInt()) + " - Usuwanie konta nieudane."));
                            break;
                        }
                    }
                    // _____________________________________________________________________________________________________________
                   stop = true;
                   appWindow->getParent()->getServer().clearStatus();
                }
                    break;
                case SERVER_NETWORK_ERROR:
                {
                    // __________________________________________________________________________________
                    QNetworkReply::NetworkError error = appWindow->getParent()->getServer().getNetworkError();
                    if(error == QNetworkReply::ConnectionRefusedError || error == QNetworkReply::TimeoutError){
                        appWindow->getPromptPanel().setServerStatusNoConnection();
                    }
                    // ____________________________________________________________________________________
                    stop = true;
                    appWindow->getParent()->getServer().clearStatus();
                }
                    break;
                case SERVER_READY:
                    stop = true;
                    appWindow->getParent()->getServer().clearStatus();
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
    parent->getParent()->reload(false);
}
