QT -= gui
LIBS += -lbcm2835
CONFIG += c++11 console
CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
    outletsensor.cpp \
    garagepi.cpp \
    doormonitor.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    outletsensor.h \
    garagepi.h \
    defines.h \
    doormonitor.h
