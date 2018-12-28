#include"dialog.hpp"
#include<QTimer>
#include"appwindow.hpp"

/* _PH_ Uncomment If need to make custom dialog with this constructor
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

Dialog::Dialog(DialogType setType, QString title, QString content, QString setFirstOption, QString setSecondOption, QString setThirdOption, QWidget *setParent){
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
    default:
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

QLabel* Dialog::getYesButton(){
    return yesButton;
}

QLabel* Dialog::getNoButton(){
    return noButton;
}

QLabel* Dialog::getFirstOptionLabel(){
    return firstOptionLabel;
}

QLabel* Dialog::getSecondOptionLabel(){
    return secondOptionLabel;
}

QLabel* Dialog::getThirdOptionLabel(){
    return thirdOptionLabel;
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
        default:
            break;
        }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, ev);
}
