QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.


SOURCES += \
    src/charts/chart.cpp \
    src/charts/glyph.cpp \
    src/charts/measure.cpp \
    src/charts/midiplayer.cpp \
    src/charts/printingmodel.cpp \
    src/charts/workingchord.cpp \
    src/main.cpp \
    src/music/chord.cpp \
    src/ui/mainwindow.cpp \
    src/ui/scorewidget.cpp \
    src/ui/startupwindow.cpp

HEADERS += \
    src/charts/chart.h \
    src/charts/glyph.h \
    src/charts/measure.h \
    src/charts/midiplayer.h \
    src/charts/printingmodel.h \
    src/charts/workingchord.h \
    src/music/chord.h \
    src/music/meter.h \
    src/music/note.h \
    src/music/notes.h \
    src/music/scales.h \
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

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += fluidsynth


win32: LIBS += -L$$PWD/external/lib/ -lfluidsynth

INCLUDEPATH += $$PWD/external/include/fluidsynth
DEPENDPATH += $$PWD/external/include/fluidsynth
win32-g++: PRE_TARGETDEPS += $$PWD/external/lib/libfluidsynth.a

RESOURCES +=
