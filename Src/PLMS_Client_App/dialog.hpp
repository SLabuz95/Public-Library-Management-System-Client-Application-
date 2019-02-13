#ifndef DIALOG_HPP
#define DIALOG_HPP

// ------------------ Macros --------------------------------------------
#define YES_NO_BUTTON_WIDTH (90)
#define BUTTONS_HEIGHT (25)
#define HORIZONTAL_OFFSET (10)
#define VERTICAL_BORDER_OFFSET (10)
#define VERTICAL_OFFSET (5)
#define MIN_REFERENCE_WIDTH (250)
#define MAX_TEST_RECT_HEIGHT (200)

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"

// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QKeyEvent>
#include"dialogtypeenum.hpp"
#include"dialogresultenum.hpp"
// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class QScrollArea;
class User;
class ChangePasswordPanel;
class BookPanel;
class Book;
class AddCommentPanel;
class CheckPasswordPanel;
// ----------------------------------------------------------------------

// ------------------ Dialog Class ------------------------------------

class Dialog : public QDialog{
    Q_OBJECT
public:
    // Contructor for types: CHANGE_PASSWORD, CHECK_PASSWORD, BOOK_PANEL
    Dialog(DialogType setType, User* user, QWidget* setParent);
    // Contructor for types: ADD_COMMENT
    Dialog(DialogType setType, Book* book, unsigned long long userId, QWidget* setParent);
    // Constuctor for types:  YES_NO_QUESTION
    Dialog(DialogType setType, QString title, QString content, QWidget* setParent);
    // Constuctor for types: QUESTION
    Dialog(DialogType setType, QString title, QString content, QWidget* setParent, QString setFirstOption, QString setSecondOption = QString(), QString setThirdOption = QString());

    // Destructor
    ~Dialog();
private:
    // Parent
    QWidget* parent = nullptr;
    // Dla Typów CHANGE_PASSWORD Cast do AppWindow
    // Type
    DialogType type;

    // Elements
    // For types: YES_NO_QUESTION, QUESTION
    QLabel* titleLabel = nullptr;
    QLabel* questionLabel = nullptr;
    QLabel* yesButton = nullptr;
    QLabel* noButton = nullptr;
    QLabel* firstOptionLabel = nullptr;
    QLabel* secondOptionLabel = nullptr;
    QLabel* thirdOptionLabel = nullptr;

    // For types: CHANGE_PASSWORD
    union DialogPanel{
        ChangePasswordPanel* changePasswordPanel = nullptr;
        BookPanel* bookPanel;
        AddCommentPanel* addCommentPanel;
        CheckPasswordPanel* checkPasswordPanel;
    } dialogPanel;

    // Dialog Answer
    DialogResult *exitCode = nullptr;

    // Control Functions
    void createDialog();
public:
    // Event Functions
    void acceptButtonReleased();
    void cancelButtonReleased();
    void yesButtonReleased();
    void noButtonReleased();
    void firstOptionLabelReleased();
    void secondOptionLabelReleased();
    void thirdOptionLabelReleased();

public:
    DialogType getType();
    void setExitCode(DialogResult*);    
    QWidget* getParent();
    bool eventFilter(QObject* obj, QEvent* ev);
};


#endif // DIALOG_HPP
