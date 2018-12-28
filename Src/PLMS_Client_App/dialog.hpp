#ifndef DIALOG_HPP
#define DIALOG_HPP

#define YES_NO_BUTTON_WIDTH (90)
#define BUTTONS_HEIGHT (25)
#define HORIZONTAL_OFFSET (10)
#define VERTICAL_BORDER_OFFSET (10)
#define VERTICAL_OFFSET (5)
#define MIN_REFERENCE_WIDTH (250)
#define MAX_TEST_RECT_HEIGHT (200)

#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QKeyEvent>
#include"dialogtypeenum.hpp"
#include"dialogresultenum.hpp"

class QScrollArea;
class Dialog : public QDialog{
    Q_OBJECT
public:
    // Konstruktor dla typu YES_NO_QUESTION
    Dialog(DialogType setType, QString title, QString content, QWidget* setParent);
    // Konstruktor dla typu QUESTION
    Dialog(DialogType setType, QString title, QString content, QString setFirstOption, QString setSecondOption, QString setThirdOption,QWidget* setParent);

    // Destruktor
    ~Dialog();
private:
    // Parent
    QWidget* parent = nullptr;

    // Type
    DialogType type;

    // Elementy
    // Dla typu QUESTION
    QLabel* titleLabel = nullptr;
    QLabel* questionLabel = nullptr;
    QLabel* yesButton = nullptr;
    QLabel* noButton = nullptr;
    QLabel* firstOptionLabel = nullptr;
    QLabel* secondOptionLabel = nullptr;
    QLabel* thirdOptionLabel = nullptr;

    DialogResult *exitCode = nullptr;

    // Funkcje sterujące
    void createDialog();
public:
    // Eventy
    void acceptButtonReleased();
    void cancelButtonReleased();
    void yesButtonReleased();
    void noButtonReleased();
    void firstOptionLabelReleased();
    void secondOptionLabelReleased();
    void thirdOptionLabelReleased();

public:
    QLabel* getAcceptButton();
    QLabel* getCancelButton();
    QLabel* getYesButton();
    QLabel* getNoButton();
    QLabel* getFirstOptionLabel();
    QLabel* getSecondOptionLabel();
    QLabel* getThirdOptionLabel();

    DialogType getType();
    void setExitCode(DialogResult*);    

    bool eventFilter(QObject* obj, QEvent* ev);
};


#endif // DIALOG_HPP
