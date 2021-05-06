TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        card.cpp \
        main.cpp \
        mainwindow.cpp \
        player.cpp

HEADERS += \
    card.hh \
    mainwindow.hh \
    player.hh

DISTFILES += \
    instructions.txt

FORMS += \
    mainwindow.ui
