
QT += websockets gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/bot.cpp \
    src/eventservice.cpp \
    src/gatewayservice.cpp \
    src/jsonserializer.cpp \
    src/main.cpp \
    src/payloads/gatewaypayload.cpp \
    src/bot.cpp \
    src/jsonserializer.cpp \
    src/main.cpp \
    src/payloads/gatewaypayload.cpp \
    src/payloads/gatewaypayload.cpp \
    src/payloads/heartbeat.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/src/.
DEPENDPATH += $$PWD/src/.

DISTFILES += \
    settings.ini

HEADERS += \
    src/bot.h \
    src/eventservice.h \
    src/gatewayservice.h \
    src/globals.h \
    src/jsonserializeable.h \
    src/jsonserializer.h \
    src/lockingdeque.h \
    src/opcodes/gatewayopcodes.h \
    src/payloads/gatewaypayload.h \
    src/bot.h \
    src/jsonserializeable.h \
    src/jsonserializer.h \
    src/lockingdeque.h \
    src/payloads/gatewaypayload.h \
    src/payloads/hello.h \
    src/payloads/gatewaypayload.h \
    src/payloads/hello.h \
    src/payloads/heartbeat.h
