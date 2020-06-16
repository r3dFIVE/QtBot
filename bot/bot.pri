QT += websockets

INCLUDEPATH += $$PWD/src/.
DEPENDPATH += $$PWD/src/.

HEADERS += \
    $$PWD/src/bot.h \
    $$PWD/src/eventhandler.h \
    $$PWD/src/gateway.h \
    $$PWD/src/globals.h \
    $$PWD/src/lockingdeque.h \
    $$PWD/src/logging/logcontext.h \
    $$PWD/src/logging/logfactory.h \
    $$PWD/src/logging/logger.h \
    $$PWD/src/logging/logworker.h \
    $$PWD/src/payloads/activity.h \
    $$PWD/src/payloads/assets.h \
    $$PWD/src/payloads/emoji.h \
    $$PWD/src/payloads/gatewaypayload.h \
    $$PWD/src/lockingdeque.h \
    $$PWD/src/payloads/gatewaypayload.h \
    $$PWD/src/payloads/hello.h \
    $$PWD/src/payloads/gatewaypayload.h \
    $$PWD/src/payloads/hello.h \
    $$PWD/src/payloads/heartbeat.h \
    $$PWD/src/payloads/identify.h \
    $$PWD/src/payloads/jsonserializeable.h \
    $$PWD/src/payloads/party.h \
    $$PWD/src/payloads/properties.h \
    $$PWD/src/payloads/resume.h \
    $$PWD/src/payloads/secrets.h \
    $$PWD/src/payloads/timestamps.h \
    $$PWD/src/payloads/updatestatus.h \
    $$PWD/src/settings.h

DISTFILES += \
    $$PWD/settings.ini

SOURCES += \
    $$PWD/src/bot.cpp \
    $$PWD/src/eventhandler.cpp \
    $$PWD/src/gateway.cpp \
    $$PWD/src/logging/logfactory.cpp \
    $$PWD/src/logging/logger.cpp \
    $$PWD/src/logging/logworker.cpp \
    $$PWD/src/payloads/activity.cpp \
    $$PWD/src/payloads/assets.cpp \
    $$PWD/src/payloads/emoji.cpp \
    $$PWD/src/payloads/gatewaypayload.cpp \
    $$PWD/src/payloads/heartbeat.cpp \
    $$PWD/src/payloads/hello.cpp \
    $$PWD/src/payloads/identify.cpp \
    $$PWD/src/payloads/party.cpp \
    $$PWD/src/payloads/properties.cpp \
    $$PWD/src/payloads/resume.cpp \
    $$PWD/src/payloads/secrets.cpp \
    $$PWD/src/payloads/timestamps.cpp \
    $$PWD/src/payloads/updatestatus.cpp \
    $$PWD/src/settings.cpp
