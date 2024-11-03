QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.


SOURCES += \
    src/chordparser.cpp \
    src/main.cpp \
    src/music/chart.cpp \
    src/music/chord.cpp \
    src/music/note.cpp \
    src/ui/mainwindow.cpp \
    src/ui/scorewidget.cpp \
    src/ui/startupwindow.cpp

HEADERS += \
    src/chordparser.h \
    src/music/chart.h \
    src/music/chord.h \
    src/music/meter.h \
    src/music/note.h \
    src/music/notes.h \
    src/ui/mainwindow.h \
    src/ui/scorewidget.h \
    src/ui/startupwindow.h \
    external/include/fluidsynth.h
FORMS += \
    src/ui/mainwindow.ui \
    src/ui/startupwindow.ui

TRANSLATIONS += \
    Charts_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    design/models/activity.qmodel \
    design/models/object.qmodel \
    design/models/usecase.qmodel
