#include"dialog.hpp"
#include<QTimer>
#include"appwindow.hpp"
#include"changepasswordpanel.hpp"
#include"bookpanel.hpp"
#include"addcommentpanel.hpp"
#include"checkpasswordpanel.hpp"
#include"../PLMS_Server_App/user.hpp"

/* Uncomment If need to make custom dialog with this constructor
  Dialog::Dialog(DialogType setType, QWidget *setParent){
    parent = setParent;
    type = setType;
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setStyleSheet("Dialog{border: 2px ridge grey;}");
    createDialog();
    show();
}*/

Dialog::Dialog(DialogType setType, QString title, QString content, QWidget* setParent){
    parent = setParent;
    type = setType;
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setStyleSheet("Dialog{border: 2px ridge grey;}");
    createDialog();
    QFontMetrics titleMetrics(QFont("Comic Sans MS",12, QFont::Medium));
    QFontMetrics contentMetrics(font());
    titleLabel->setWordWrap(true);
    titleLabel->setFont(QFont("Comic Sans MS",12, QFont::Medium));
    questionLabel->setWordWrap(true);
    int referenceWidth = MIN_REFERENCE_WIDTH;
    int numbOfButtons = 2;
    int buttonWidth = YES_NO_BUTTON_WIDTH;
    referenceWidth += HORIZONTAL_OFFSET + referenceWidth;
    setFixedWidth(referenceWidth + 2 * HORIZONTAL_OFFSET);
    int horizontalOffset = (width() - numbOfButtons * buttonWidth ) / (numbOfButtons + 1);
    if(!title.isEmpty())
    {
        titleLabel->setGeometry(HORIZONTAL_OFFSET, VERTICAL_BORDER_OFFSET, referenceWidth, titleMetrics.boundingRect(0, 0, referenceWidth, MAX_TEST_RECT_HEIGHT, Qt::AlignHCenter | Qt::TextWordWrap, title).height() + 5);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setText(title);
        questionLabel->setAlignment(Qt::AlignCenter);
        questionLabel->setGeometry(HORIZONTAL_OFFSET, titleLabel->y() + titleLabel->height() + VERTICAL_OFFSET, referenceWidth, contentMetrics.boundingRect(0, 0, referenceWidth, MAX_TEST_RECT_HEIGHT, Qt::AlignHCenter | Qt::TextWordWrap, content).height() + 5);
        yesButton->setAlignment(Qt::AlignCenter);
        yesButton->setGeometry(horizontalOffset , questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
        yesButton->setStyleSheet("border: 1px solid grey; background-color: rgba(219, 217, 217, 0.9); border-radius: 5px;");
        noButton->setAlignment(Qt::AlignCenter);
        noButton->setGeometry(width() - horizontalOffset - buttonWidth, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
        noButton->setStyleSheet("border: 1px solid grey; background-color: rgba(219, 217, 217, 0.9); border-radius: 5px;");
        setFixedHeight(yesButton->y() + BUTTONS_HEIGHT + VERTICAL_BORDER_OFFSET);
    }else{
        delete titleLabel;
        titleLabel = nullptr;
        questionLabel->setAlignment(Qt::AlignCenter);
        questionLabel->setGeometry(HORIZONTAL_OFFSET, VERTICAL_BORDER_OFFSET, referenceWidth, contentMetrics.boundingRect(0, 0, referenceWidth, MAX_TEST_RECT_HEIGHT, Qt::AlignHCenter | Qt::TextWordWrap, content).height() + 5);
        yesButton->setAlignment(Qt::AlignCenter);
        yesButton->setGeometry(horizontalOffset, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
        yesButton->setStyleSheet("border: 1px solid grey; background-color: rgba(219, 217, 217, 0.9); border-radius: 5px;");
        noButton->setAlignment(Qt::AlignCenter);
        noButton->setGeometry(width() - horizontalOffset - buttonWidth, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
        noButton->setStyleSheet("border: 1px solid grey; background-color: rgba(219, 217, 217, 0.9); border-radius: 5px;");
        setFixedHeight(yesButton->y() + BUTTONS_HEIGHT + VERTICAL_BORDER_OFFSET);
    }
    yesButton->installEventFilter(this);
    noButton->installEventFilter(this);
    show();
}

Dialog::Dialog(DialogType setType, QString title, QString content, QWidget *setParent, QString setFirstOption, QString setSecondOption, QString setThirdOption){
    parent = setParent;
    type = setType;
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setStyleSheet("Dialog{border: 2px ridge grey;}");
    createDialog();
    QFontMetrics titleMetrics(QFont("Comic Sans MS",12, QFont::Medium));
    QFontMetrics contentMetrics(font());
    titleLabel->setWordWrap(true);
    titleLabel->setFont(QFont("Comic Sans MS",12, QFont::Medium));
    questionLabel->setWordWrap(true);
        int referenceWidth = 0;
        int numbOfButtons = 0;
        int buttonWidth = 0;
        if(!setFirstOption.isEmpty()){
            if(!setSecondOption.isEmpty()){
                if(!setThirdOption.isEmpty()){
                    numbOfButtons = 3;
                    referenceWidth = contentMetrics.horizontalAdvance(setThirdOption);
                }else{
                    numbOfButtons = 2;
                }
                int tempHA = contentMetrics.horizontalAdvance(setSecondOption);
                if(referenceWidth < tempHA)
                    referenceWidth = tempHA;
            }else{
                numbOfButtons = 1;
            }
            int tempHA = contentMetrics.horizontalAdvance(setFirstOption);
            if(referenceWidth < tempHA)
               referenceWidth = tempHA;
        }
        referenceWidth += 15;
        switch(numbOfButtons){
        case 2:
            referenceWidth += HORIZONTAL_OFFSET + referenceWidth;
            break;
        case 3:
            referenceWidth += 2* HORIZONTAL_OFFSET + 2* referenceWidth;
            break;
        default:
            break;
        }
        if(referenceWidth < MIN_REFERENCE_WIDTH){
            if((buttonWidth = (referenceWidth - (numbOfButtons - 1) * HORIZONTAL_OFFSET) / numbOfButtons) < 40)
                buttonWidth = 40;
            referenceWidth = MIN_REFERENCE_WIDTH;
        }
        else{
            buttonWidth = (referenceWidth - (numbOfButtons - 1) * HORIZONTAL_OFFSET) / numbOfButtons;
        }
        setFixedWidth(referenceWidth + 2 * HORIZONTAL_OFFSET);
        int horizontalOffset = (width() - numbOfButtons * buttonWidth ) / (numbOfButtons + 1);
        if(!title.isEmpty())
        {
            titleLabel->setGeometry(HORIZONTAL_OFFSET, VERTICAL_BORDER_OFFSET, referenceWidth, titleMetrics.boundingRect(0, 0, referenceWidth, MAX_TEST_RECT_HEIGHT, Qt::AlignHCenter | Qt::TextWordWrap, title).height() + 5);
            titleLabel->setAlignment(Qt::AlignCenter);
            titleLabel->setText(title);
            questionLabel->setAlignment(Qt::AlignCenter);
            questionLabel->setGeometry(HORIZONTAL_OFFSET, titleLabel->y() + titleLabel->height() + VERTICAL_OFFSET, referenceWidth, contentMetrics.boundingRect(0, 0, referenceWidth, MAX_TEST_RECT_HEIGHT, Qt::AlignHCenter | Qt::TextWordWrap, content).height() + 5);
            firstOptionLabel->setAlignment(Qt::AlignCenter);
            firstOptionLabel->setStyleSheet("border: 1px solid grey; background-color: rgba(219, 217, 217, 0.9); border-radius: 5px;");
            secondOptionLabel->setAlignment(Qt::AlignCenter);
            secondOptionLabel->setStyleSheet("border: 1px solid grey; background-color: rgba(219, 217, 217, 0.9); border-radius: 5px;");
            thirdOptionLabel->setAlignment(Qt::AlignCenter);
            thirdOptionLabel->setStyleSheet("border: 1px solid grey; background-color: rgba(219, 217, 217, 0.9); border-radius: 5px;");
            switch(numbOfButtons){
            case 1:
                delete secondOptionLabel;
                secondOptionLabel = nullptr;
                delete thirdOptionLabel;
                thirdOptionLabel = nullptr;
                firstOptionLabel->setGeometry(horizontalOffset, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
                break;
            case 2:
                delete thirdOptionLabel;
                thirdOptionLabel = nullptr;
                firstOptionLabel->setGeometry(horizontalOffset, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
                secondOptionLabel->setGeometry(width() - horizontalOffset -  buttonWidth, questionLabel->y() + questionLabel->height() + VERTICAL_OFFSET, buttonWidth, BUTTONS_HEIGHT);
                break;
            case 3:
                firstOptionLabel->setGeometry(horizontalOffset, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
                secondOptionLabel->setGeometry(2 * horizontalOffset + buttonWidth, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
                thirdOptionLabel->setGeometry(width() - horizontalOffset - buttonWidth, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
                break;
            }
            setFixedHeight(firstOptionLabel->y() + BUTTONS_HEIGHT + VERTICAL_BORDER_OFFSET);
        }else{
            delete titleLabel;
            titleLabel = nullptr;
            questionLabel->setAlignment(Qt::AlignCenter);
            questionLabel->setGeometry(HORIZONTAL_OFFSET, VERTICAL_BORDER_OFFSET, referenceWidth, contentMetrics.boundingRect(0, 0, referenceWidth, MAX_TEST_RECT_HEIGHT, Qt::AlignHCenter | Qt::TextWordWrap, content).height() + 5);
            firstOptionLabel->setAlignment(Qt::AlignCenter);
            firstOptionLabel->setStyleSheet("border: 1px solid grey; background-color: rgba(219, 217, 217, 0.9); border-radius: 5px;");
            secondOptionLabel->setAlignment(Qt::AlignCenter);
            secondOptionLabel->setStyleSheet("border: 1px solid grey; background-color: rgba(219, 217, 217, 0.9); border-radius: 5px;");
            thirdOptionLabel->setAlignment(Qt::AlignCenter);
            thirdOptionLabel->setStyleSheet("border: 1px solid grey; background-color: rgba(219, 217, 217, 0.9); border-radius: 5px;");
            switch(numbOfButtons){
            case 1:
                delete secondOptionLabel;
                secondOptionLabel = nullptr;
                delete thirdOptionLabel;
                thirdOptionLabel = nullptr;
                firstOptionLabel->setGeometry(horizontalOffset, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
                break;
            case 2:
                delete thirdOptionLabel;
                thirdOptionLabel = nullptr;
                firstOptionLabel->setGeometry(horizontalOffset, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
                secondOptionLabel->setGeometry(width() - horizontalOffset -  buttonWidth, questionLabel->y() + questionLabel->height() + VERTICAL_OFFSET, buttonWidth, BUTTONS_HEIGHT);
                break;
            case 3:
                firstOptionLabel->setGeometry(horizontalOffset, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
                secondOptionLabel->setGeometry(2 * horizontalOffset + buttonWidth, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
                thirdOptionLabel->setGeometry(width() - horizontalOffset -  buttonWidth, questionLabel->y() + questionLabel->height() + VERTICAL_BORDER_OFFSET, buttonWidth, BUTTONS_HEIGHT);
                break;
            }
            setFixedHeight(firstOptionLabel->y() + BUTTONS_HEIGHT + VERTICAL_BORDER_OFFSET);
        }
        questionLabel->setText(content);
        firstOptionLabel->setText(setFirstOption);
        firstOptionLabel->installEventFilter(this);
        if(secondOptionLabel){
            secondOptionLabel->setText(setSecondOption);
            secondOptionLabel->installEventFilter(this);
        }
        if(thirdOptionLabel){
            thirdOptionLabel->setText(setThirdOption);
            thirdOptionLabel->installEventFilter(this);
        }            
}

Dialog::Dialog(DialogType setType, User* user, QWidget* setParent){
    parent = setParent;
    type = setType;
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setStyleSheet("Dialog{border: 2px ridge grey;}");
    setWindowModality(Qt::ApplicationModal);
    switch(type){
    case CHANGE_PASSWORD:
        dialogPanel.changePasswordPanel = new ChangePasswordPanel(this, user);
        dialogPanel.changePasswordPanel->setGeometry(DIALOG_CHANGE_PASSWORD_PANEL_X, DIALOG_CHANGE_PASSWORD_PANEL_Y, DIALOG_CHANGE_PASSWORD_PANEL_WIDTH, DIALOG_CHANGE_PASSWORD_PANEL_HEIGHT);
    break;
    case BOOK_PANEL:
        dialogPanel.bookPanel = new BookPanel(this, user);
        dialogPanel.bookPanel->setGeometry(DIALOG_BOOK_PANEL_X, DIALOG_BOOK_PANEL_Y, DIALOG_BOOK_PANEL_WIDTH, DIALOG_BOOK_PANEL_HEIGHT);
        break;
    case CHECK_PASSWORD:
        dialogPanel.checkPasswordPanel = new CheckPasswordPanel(this, user);
        dialogPanel.checkPasswordPanel->setGeometry(DIALOG_CHECK_PASSWORD_PANEL_X, DIALOG_CHECK_PASSWORD_PANEL_Y, DIALOG_CHECK_PASSWORD_PANEL_WIDTH, DIALOG_CHECK_PASSWORD_PANEL_HEIGHT);
        break;
    default:
        break;
    }
        show();
}

Dialog::Dialog(DialogType setType, Book* book, unsigned long long userId, QWidget* setParent){
    parent = setParent;
    type = setType;
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setStyleSheet("Dialog{border: 2px ridge grey;}");
    setWindowModality(Qt::ApplicationModal);
    switch(type){
    case ADD_COMMENT:
        dialogPanel.addCommentPanel = new AddCommentPanel(this, book, userId);
        dialogPanel.addCommentPanel->setGeometry(DIALOG_ADD_COMMENT_PANEL_X,DIALOG_ADD_COMMENT_PANEL_Y,DIALOG_ADD_COMMENT_PANEL_WIDTH,DIALOG_ADD_COMMENT_PANEL_HEIGHT);
        break;
    default:
        break;
    }
        show();
}

Dialog::~Dialog(){
    switch(type){
    case QUESTION_DIALOG:
        delete titleLabel;
        delete questionLabel;
        delete firstOptionLabel;
        delete secondOptionLabel;
        delete thirdOptionLabel;
        break;
    case YES_NO_QUESTION:
        delete titleLabel;
        delete questionLabel;
        delete yesButton;
        delete noButton;
        break;
    case CHANGE_PASSWORD:
        SET_PTR_DO(dialogPanel.changePasswordPanel, nullptr);
        break;
    case BOOK_PANEL:
        SET_PTR_DO(dialogPanel.bookPanel, nullptr);
        break;
    case ADD_COMMENT:
        SET_PTR_DO(dialogPanel.addCommentPanel, nullptr);
        break;
    case CHECK_PASSWORD:
        SET_PTR_DO(dialogPanel.checkPasswordPanel, nullptr);
        break;
    }
}

void Dialog::createDialog(){
    QFont f("Comic Sans MS", 14, QFont::Medium);
    switch(type){
    case QUESTION_DIALOG:
            titleLabel = new QLabel(this);
            titleLabel->show();
            questionLabel = new QLabel(this);
            questionLabel->show();
            firstOptionLabel = new QLabel(this);
            firstOptionLabel->show();
            secondOptionLabel = new QLabel(this);
            secondOptionLabel->show();
            thirdOptionLabel = new QLabel(this);
            thirdOptionLabel->show();
        break;
    case YES_NO_QUESTION:
        titleLabel = new QLabel(this);
        titleLabel->show();
        questionLabel = new QLabel(this);
        questionLabel->show();
        yesButton = new QLabel("Tak", this);
        yesButton->show();
        noButton =  new QLabel("Nie", this);
        noButton->show();
    break;
    default:
        break;
    }
}

void Dialog::yesButtonReleased(){
    done(YES_RESULT);
}

void Dialog::noButtonReleased(){
    done(NO_RESULT);
}

void Dialog::firstOptionLabelReleased(){
    done(FIRST_OPTION_RESULT);
}

void Dialog::secondOptionLabelReleased(){
    done(SECOND_OPTION_RESULT);
}

void Dialog::thirdOptionLabelReleased(){
    done(THIRD_OPTION_RESULT);
}

DialogType Dialog::getType(){
    return type;
}

void Dialog::setExitCode(DialogResult* dlgExitCode){
    if(exitCode != nullptr)
        delete exitCode;
    exitCode = dlgExitCode;
}

bool Dialog::eventFilter(QObject* obj, QEvent* ev){
    switch(ev->type()){
    case QEvent::KeyPress:
        switch(type){
        case ADD_COMMENT:
            if(dialogPanel.addCommentPanel && dialogPanel.addCommentPanel->eventMatching(obj, ev))
             return true;
            break;
        case CHECK_PASSWORD:
            if(dialogPanel.checkPasswordPanel && dialogPanel.checkPasswordPanel->eventMatching(obj, ev))
                return true;
            break;
        case CHANGE_PASSWORD:
            if(dialogPanel.changePasswordPanel && dialogPanel.changePasswordPanel->eventMatching(obj, ev))
                return true;
            break;
        default:
            break;
        }
       break;
    case QEvent::MouseButtonRelease:
        switch(type){
        case QUESTION_DIALOG:
            if(firstOptionLabel == obj){
                firstOptionLabelReleased();
                return true;
            }
            if(secondOptionLabel == obj){
                secondOptionLabelReleased();
                return true;
            }
            if(thirdOptionLabel == obj){
                thirdOptionLabelReleased();
                return true;
            }
            break;
        case YES_NO_QUESTION:
            if(yesButton == obj){
                yesButtonReleased();
                return true;
            }
            if(noButton == obj){
                noButtonReleased();
                return true;
            }
        break;
        case CHANGE_PASSWORD:
            if(dialogPanel.changePasswordPanel && dialogPanel.changePasswordPanel->eventMatching(obj, ev))
                return true;
            break;        
        case BOOK_PANEL:
            if(dialogPanel.bookPanel && dialogPanel.bookPanel->eventMatching(obj, ev))
                return true;
            break;
        case ADD_COMMENT:
            if(dialogPanel.addCommentPanel && dialogPanel.addCommentPanel->eventMatching(obj, ev))
                return true;
            break;
        case CHECK_PASSWORD:
            if(dialogPanel.checkPasswordPanel && dialogPanel.checkPasswordPanel->eventMatching(obj, ev))
                return true;
            break;
        }
        break;
    case QEvent::Enter:
    {
        switch(type){
        case CHANGE_PASSWORD:
            if(dialogPanel.changePasswordPanel && dialogPanel.changePasswordPanel->eventMatching(obj, ev))
                return true;
            break;
        case BOOK_PANEL:
            if(dialogPanel.bookPanel && dialogPanel.bookPanel->eventMatching(obj, ev))
                return true;
            break;
        case ADD_COMMENT:
            if(dialogPanel.addCommentPanel && dialogPanel.addCommentPanel->eventMatching(obj, ev))
                return true;
            break;
        case CHECK_PASSWORD:
            if(dialogPanel.checkPasswordPanel && dialogPanel.checkPasswordPanel->eventMatching(obj, ev))
                return true;
            break;
        default:
            break;
        }
    }
        break;
    case QEvent::Leave:
    {
        switch(type){
        case CHANGE_PASSWORD:
            if(dialogPanel.changePasswordPanel && dialogPanel.changePasswordPanel->eventMatching(obj, ev))
                return true;
            break;
        case BOOK_PANEL:
            if(dialogPanel.bookPanel && dialogPanel.bookPanel->eventMatching(obj, ev))
                return true;
            break;
        case ADD_COMMENT:
            if(dialogPanel.addCommentPanel && dialogPanel.addCommentPanel->eventMatching(obj, ev))
                return true;
            break;
        case CHECK_PASSWORD:
            if(dialogPanel.checkPasswordPanel && dialogPanel.checkPasswordPanel->eventMatching(obj, ev))
                return true;
            break;
        default:
            break;
        }
    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, ev);
}

QWidget* Dialog::getParent(){
    return parent;
}
