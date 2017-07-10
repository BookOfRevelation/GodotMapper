#-------------------------------------------------
#
# Project created by QtCreator 2017-01-14T18:40:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GodotMapping
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    menu.cpp \
    newmap.cpp \
    contexte.cpp \
    mapper.cpp \
    mainscene.cpp \
    mainview.cpp \
    tileview.cpp \
    tilescene.cpp \
    rigthdocker.cpp \
    drawmodewidget.cpp \
    layerselection.cpp \
    action.cpp

HEADERS  += mainwidget.h \
    menu.h \
    newmap.h \
    contexte.h \
    mapper.h \
    mainscene.h \
    mainview.h \
    tileview.h \
    tilescene.h \
    rigthdocker.h \
    drawmodewidget.h \
    layerselection.h \
    action.h

FORMS    += mainwidget.ui \
    menu.ui \
    newmap.ui
