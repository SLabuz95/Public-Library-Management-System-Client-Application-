QT += core widgets
TEMPLATE = app
TARGET = "Aplikacja biblioteki publicznej"
VERSION_PE_HEADER = 1.0

HEADERS += \
    app.hpp \
    appwindow.hpp \
    appwindowstatenum.hpp \
    windowmacros.hpp

SOURCES += \
    app.cpp \
    main.cpp \
    appwindow.cpp