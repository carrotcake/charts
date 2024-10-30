QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.


SOURCES += \
    src/main.cpp \
    src/ui/mainwindow.cpp

HEADERS += \
    src/ui/mainwindow.h

FORMS += \
    src/ui/mainwindow.ui

TRANSLATIONS += \
    Charts_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
