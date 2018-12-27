#ifndef PROMPTLIST_HPP
#define PROMPTLIST_HPP
// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"
#include "windowmacros.hpp"
// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QFrame>
#include"prompttypeenum.hpp"

// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------
class PromptElement;
class PromptPanel;
// ----------------------------------------------------------------------

// ------------------ PromptList Class ------------------------------------

class PromptList : public QFrame
{
    Q_OBJECT
public:
  // Constructors
  PromptList(PromptPanel*);

  // Destructors
  ~PromptList();

private:
  // Parent
  PromptPanel *parent = nullptr;

  // List of PromptElements
  PromptElement **promptElements = nullptr;

  // Numb of list elements
  uint numbOfElements = 0;

   // Control Functions
  void init();
  void createWidgets();
  void createLayout();
  void deleteWidgets();
  void setWindow();
  void connectAll();
  void disconnectAll();

  public:
  // Get Functions--------------------
  PromptPanel* getParent();
  PromptElement** getPromptElements();
  uint getNumbOfElements();
  // -----------------------------
  // Set Function--------------------

  // -----------------------------

  // Add Element
  void addElement(PromptElement*);
  // Delete element by index number
  void deleteElement(uint);
  // Delete element by element address
  void deleteElement(PromptElement*);
  // Get actual height of list and resize
  void reallocate();
  // Function for events control of list elements
  void matchEvents(QObject*, QEvent*);
};

#endif // PROMPTLIST_HPP

