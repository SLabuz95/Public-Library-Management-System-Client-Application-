#ifndef PROMPTLIST_HPP
#define PROMPTLIST_HPP
#include<QFrame>

class PromptElement;
class PromptPanel;
class PromptList : public QFrame
{
    Q_OBJECT
public:
  // Konstruktor
  PromptList(PromptPanel*);

  // Destruktor
  ~PromptList();

private:
  // Parent (PromptPanel)
  PromptPanel *parent = nullptr;

  // Zmienna przechowująca elementy PromptList (PromptElement)
  PromptElement **promptElements = nullptr;

  // Liczba elementów listy
  uint numbOfElements = 0;

   //Funkcje sterujące
  void init();
  void createWidgets();
  void createLayout();
  void deleteWidgets();
  void setWindow();
  void connectAll();
  void disconnectAll();

  public:
  PromptPanel* getParent();
  PromptElement** getPromptElements();
  uint getNumbOfElements();

  void addElement(PromptElement*);
  void deleteElement(uint);
  void deleteElement(PromptElement*);
  void reallocate();
  void matchEvents(QObject*, QEvent*);
};

#endif // PROMPTLIST_HPP

