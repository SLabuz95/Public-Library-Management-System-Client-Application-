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
// ----------------------------------------------------------------------

// ------------------ Dialog Class ------------------------------------

class Dialog : public QDialog{
    Q_OBJECT
public:
    // Constuctor for types:  YES_NO_QUESTION
    Dialog(DialogType setType, QString title, QString content, QWidget* setParent);
    // Constuctor for types: QUESTION
    Dialog(DialogType setType, QString title, QString content, QWidget* setParent, QString setFirstOption, QString setSecondOption = QString(), QString setThirdOption = QString());

    // Destructor
    ~Dialog();
private:
    // Parent
    QWidget* parent = nullptr;

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

    bool eventFilter(QObject* obj, QEvent* ev);
};


#endif // DIALOG_HPP
