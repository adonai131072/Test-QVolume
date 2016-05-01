TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    qvolumechanger.cpp

HEADERS += \
    qvolumechanger.h

win32 {
    SOURCES += qvolumechangerwin.cpp
    HEADERS += qvolumechangerwin.h
    LIBS += -lole32
}

unix {
    SOURCES += qvolumechangeralsa.cpp
    HEADERS += qvolumechangeralsa.h
    LIBS += -lasound
}

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)


