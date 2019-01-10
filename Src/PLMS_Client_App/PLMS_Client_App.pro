QT += core widgets network
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
    server.hpp \
    ../PLMS_Server_App/bookparameters.hpp \
    ../PLMS_Server_App/commandtype.hpp \
    ../PLMS_Server_App/filetypeenum.hpp \
    ../PLMS_Server_App/messagetype.hpp \
    ../PLMS_Server_App/readfilerules.hpp \
    ../PLMS_Server_App/returnerrortype.hpp \
    ../PLMS_Server_App/user.hpp \
    ../PLMS_Server_App/userparametersenum.hpp

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
    server.cpp \
    ../PLMS_Server_App/user.cpp

RESOURCES += \
    icons.qrc
