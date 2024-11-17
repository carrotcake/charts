QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.


SOURCES += \
    external/midifile/src/Binasc.cpp \
    external/midifile/src/MidiEvent.cpp \
    external/midifile/src/MidiEventList.cpp \
    external/midifile/src/MidiFile.cpp \
    external/midifile/src/MidiMessage.cpp \
    src/charts/chart.cpp \
    src/charts/midiplayer.cpp \
    src/charts/midisequence.cpp \
    src/charts/segment.cpp \
    src/charts/workingchord.cpp \
    src/main.cpp \
    src/music/chord.cpp \
    src/ui/barlineitem.cpp \
    src/ui/chartscene.cpp \
    src/ui/chartwidget.cpp \
    src/ui/chorditem.cpp \
    src/ui/labelitem.cpp \
    src/ui/mainwindow.cpp \
    src/ui/startupwindow.cpp
HEADERS += \
    external/fluidsynth/include/fluidsynth.h \
    external/fluidsynth/include/audio.h \
    external/fluidsynth/include/event.h \
    external/fluidsynth/include/gen.h \
    external/fluidsynth/include/ladspa.h \
    external/fluidsynth/include/log.h \
    external/fluidsynth/include/midi.h \
    external/fluidsynth/include/misc.h \
    external/fluidsynth/include/mod.h \
    external/fluidsynth/include/seq.h \
    external/fluidsynth/include/seqbind.h \
    external/fluidsynth/include/settings.h \
    external/fluidsynth/include/sfont.h \
    external/fluidsynth/include/shell.h \
    external/fluidsynth/include/synth.h \
    external/fluidsynth/include/types.h \
    external/fluidsynth/include/version.h \
    external/fluidsynth/include/voice.h \
    external/midifile/include/Binasc.h \
    external/midifile/include/MidiEvent.h \
    external/midifile/include/MidiEventList.h \
    external/midifile/include/MidiFile.h \
    external/midifile/include/MidiMessage.h \
    src/charts/chart.h \
    src/charts/midiplayer.h \
    src/charts/midisequence.h \
    src/charts/segment.h \
    src/charts/workingchord.h \
    src/music/chord.h \
    src/music/meter.h \
    src/music/notes.h \
    src/music/pitchednote.h \
    src/music/scales.h \
    src/ui/barlineitem.h \
    src/ui/chartscene.h \
    src/ui/chartwidget.h \
    src/ui/chorditem.h \
    src/ui/labelitem.h \
    src/ui/mainwindow.h \
    src/ui/startupwindow.h
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

INCLUDEPATH += $$PWD/external/fluidsynth/include \
$$PWD/external/midifile/include
DEPENDPATH += $$PWD/external/include
win32-g++: PRE_TARGETDEPS += $$PWD/external/lib/libfluidsynth.a

RESOURCES +=
