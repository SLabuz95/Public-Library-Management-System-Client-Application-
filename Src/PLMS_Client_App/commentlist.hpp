#ifndef COMMENTLIST_HPP
#define COMMENTLIST_HPP

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

class Book;
class OperationListElement;
class CommentListElement;
// ----------------------------------------------------------------------

// ------------------ CommentList Class ------------------------------------

class CommentList : public QFrame
{
    Q_OBJECT
public:
  // Constructors
  CommentList(Book*, OperationListElement*);

  // Destructors
  ~CommentList();

private:
  OperationListElement* parent = nullptr;

  Book* book = nullptr;
  // List of Comment Element
  CommentListElement **elements = nullptr;

  // Numb of list elements
  uint numbOfElements = 0;

  uint elementsHeight = 0;
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
  CommentListElement** getElements();
  uint getNumbOfElements();
  OperationListElement* getParent();
  // -----------------------------
  // Set Function--------------------

  // -----------------------------

  // Add Element
  void addElement(CommentListElement*);
  // Delete element by element address
  void removeElement(CommentListElement*);
  // Get actual height of list and resize
  void reallocate();
  // Function for events control of list elements
  bool eventFilter(QObject*, QEvent*);

};


#endif // COMMENTLIST_HPP
