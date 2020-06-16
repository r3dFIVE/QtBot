QT = websockets

TARGET = echoserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    echoserver.cpp

HEADERS += \
    echoserver.h


target.path = $$[QT_INSTALL_EXAMPLES]/websockets/echoserver
INSTALLS += target

include(../bot/bot.pri)
