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
    $$PWD/payloads/activityassets.h \
    $$PWD/payloads/activityemoji.h \
    $$PWD/payloads/activityparty.h \
    $$PWD/payloads/activitysecrets.h \
    $$PWD/payloads/activitytimestamps.h \
    $$PWD/payloads/channel.h \
    $$PWD/payloads/clientstatus.h \
    $$PWD/payloads/emoji.h \
    $$PWD/payloads/gatewaypayload.h \
    $$PWD/lockingdeque.h \
    $$PWD/payloads/gatewaypayload.h \
    $$PWD/payloads/guild.h \
    $$PWD/payloads/guildmember.h \
    $$PWD/payloads/hello.h \
    $$PWD/payloads/gatewaypayload.h \
    $$PWD/payloads/hello.h \
    $$PWD/payloads/heartbeat.h \
    $$PWD/payloads/identify.h \
    $$PWD/payloads/identifyproperties.h \
    $$PWD/payloads/jsonserializable.h \
    $$PWD/payloads/permissionoverwrite.h \
    $$PWD/payloads/presenceupdate.h \
    $$PWD/payloads/resume.h \
    $$PWD/payloads/role.h \
    $$PWD/payloads/updatestatus.h \
    $$PWD/payloads/user.h \
    $$PWD/jsonutils.h \
    $$PWD/payloads/voicestate.h \
    $$PWD/typefactory.h \
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
    $$PWD/payloads/activity.cpp \
    $$PWD/settings.cpp
