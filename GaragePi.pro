QT -= gui
LIBS += -lbcm2835
CONFIG += c++17 console
CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        src/main.cpp \
    src/outletsensor.cpp \
    src/garagepi.cpp \
    src/doormonitor.cpp
    src/main.cpp \


HEADERS += \
    src/outletsensor.h \
    src/garagepi.h \
    src/doormonitor.h \
    src/pins.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    outletsensor.h \
    garagepi.h \
    defines.h \
    doormonitor.h
