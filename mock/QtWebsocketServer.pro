QT = websockets

TARGET = echoserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    jsonserializer.cpp \
    main.cpp \
    echoserver.cpp

HEADERS += \
    echoserver.h \
    gatewaypayload.h \
    globals.h \
    heartbeat.h \
    hello.h \
    jsonserializeable.h \
    jsonserializer.h


target.path = $$[QT_INSTALL_EXAMPLES]/websockets/echoserver
INSTALLS += target
