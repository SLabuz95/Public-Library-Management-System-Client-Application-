QT += core widgets
TEMPLATE = app
TARGET = "Aplikacja biblioteki publicznej"
VERSION_PE_HEADER = 1.0

HEADERS += \
    app.hpp \
    appwindow.hpp \
    appwindowstatenum.hpp \
    windowmacros.hpp \
    menu.hpp \
    mainmacros.hpp \
    toolbar.hpp \
    promptelement.hpp \
    promptlist.hpp \
    promptpanel.hpp \
    promptpanelmaximizebutton.hpp \
    promptpanelminimizebutton.hpp \
    promptpanelstatusenum.hpp \
    prompttypeenum.hpp \
    promptelementexpandbutton.hpp \
    dialogresultenum.hpp \
    dialogtypeenum.hpp \
    dialog.hpp \
    tabbar.hpp \
    usertab.hpp \
    user.hpp

SOURCES += \
    app.cpp \
    main.cpp \
    appwindow.cpp \
    menu.cpp \
    toolbar.cpp \
    promptelement.cpp \
    promptlist.cpp \
    promptpanel.cpp \
    promptpanelmaximizebutton.cpp \
    promptpanelminimizebutton.cpp \
    promptelementexpandbutton.cpp \
    dialog.cpp \
    tabbar.cpp \
    usertab.cpp \
    user.cpp

RESOURCES += \
    icons.qrc
