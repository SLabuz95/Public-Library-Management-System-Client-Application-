#ifndef USER_HPP
#define USER_HPP
// ------------------ Macros --------------------------------------------

// Include macros
#include "mainmacros.hpp"

// ----------------------------------------------------------------------

// ------------------ Includes ------------------------------------------
#include<QString>
// ----------------------------------------------------------------------

// ------------------ Predefinitions ------------------------------------

// ----------------------------------------------------------------------

// ------------------ User Class ------------------------------------

class User{
public:
    // Constructor
    User(QString);

    // Destructor
    ~User();

private:
    // User Data
    unsigned long userId = 0;   // if 0, unidentified
    // User Name
    QString userName;
public:
    // Create New User Class
    void createUser();

    // Get Functions
    QString getUserName();
};


#endif // USER_HPP
