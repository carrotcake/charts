QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.


SOURCES += \
    src/charts/chart.cpp \
    src/charts/chartscene.cpp \
    src/charts/midiplayer.cpp \
    src/charts/segment.cpp \
    src/charts/workingchord.cpp \
    src/main.cpp \
    src/music/chord.cpp \
    src/ui/barlineitem.cpp \
    src/ui/chartwidget.cpp \
    src/ui/chorditem.cpp \
    src/ui/mainwindow.cpp \
    src/ui/startupwindow.cpp

HEADERS += \
    src/charts/chart.h \
    src/charts/chartscene.h \
    src/charts/midiplayer.h \
    src/charts/segment.h \
    src/charts/workingchord.h \
    src/music/chord.h \
    src/music/meter.h \
    src/music/notes.h \
    src/music/pitchednote.h \
    src/music/scales.h \
    src/ui/barlineitem.h \
    src/ui/chartwidget.h \
    src/ui/chorditem.h \
    src/ui/mainwindow.h \
    src/ui/startupwindow.h \
    external/include/fluidsynth.h
FORMS += \
    src/ui/mainwindow.ui \
    src/ui/startupwindow.ui

APP_SF2_FILE.files = tools/fs/GU-GS.sf2


TRANSLATIONS += \
    Charts_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations
macx:{
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 14
    APP_SF2_FILE.path = Contents/MacOS/
    QMAKE_BUNDLE_DATA += APP_SF2_FILE
    }
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
