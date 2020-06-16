QT += websockets

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

HEADERS += \
    $$PWD/bot.h \
    $$PWD/eventhandler.h \
    $$PWD/gateway.h \
    $$PWD/globals.h \
    $$PWD/lockingdeque.h \
    $$PWD/logging/logcontext.h \
    $$PWD/logging/logfactory.h \
    $$PWD/logging/logger.h \
    $$PWD/logging/logworker.h \
    $$PWD/payloads/activity.h \
    $$PWD/payloads/assets.h \
    $$PWD/payloads/emoji.h \
    $$PWD/payloads/gatewaypayload.h \
    $$PWD/lockingdeque.h \
    $$PWD/payloads/gatewaypayload.h \
    $$PWD/payloads/hello.h \
    $$PWD/payloads/gatewaypayload.h \
    $$PWD/payloads/hello.h \
    $$PWD/payloads/heartbeat.h \
    $$PWD/payloads/identify.h \
    $$PWD/payloads/jsonserializeable.h \
    $$PWD/payloads/party.h \
    $$PWD/payloads/properties.h \
    $$PWD/payloads/resume.h \
    $$PWD/payloads/secrets.h \
    $$PWD/payloads/timestamps.h \
    $$PWD/payloads/updatestatus.h \
    $$PWD/settings.h

DISTFILES += \
    $$PWD/settings.ini

SOURCES += \
    $$PWD/bot.cpp \
    $$PWD/eventhandler.cpp \
    $$PWD/gateway.cpp \
    $$PWD/logging/logfactory.cpp \
    $$PWD/logging/logger.cpp \
    $$PWD/logging/logworker.cpp \
    $$PWD/settings.cpp
