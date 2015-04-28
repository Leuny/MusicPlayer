#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T17:07:58
#
#-------------------------------------------------

QT       += core gui
QT        += phonon
TARGET = MusicPlayer
TEMPLATE = app


SOURCES += main.cpp\
        musicplayer.cpp \
    playlist.cpp \
    musiclrc.cpp \
    IconButton.cpp \
    setwidget.cpp

HEADERS  += musicplayer.h \
    playlist.h \
    musiclrc.h \
    iconButton.h \
    setwidget.h

FORMS    += \
    musicplayer.ui \
    setWidget.ui

RESOURCES += \
    images.qrc

OTHER_FILES += \
    app.rc

RC_FILE= app.rc
