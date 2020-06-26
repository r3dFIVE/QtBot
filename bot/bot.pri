QT += websockets

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

HEADERS += \
    $$PWD/payloads/activityemoji.h \
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
    $$PWD/payloads/invalidsession.h \
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
    $$PWD/payloads/ready.h \
    $$PWD/payloads/resume.h \
    $$PWD/payloads/role.h \
    $$PWD/payloads/updatestatus.h \
    $$PWD/payloads/user.h \
    $$PWD/jsonutils.h \
    $$PWD/payloads/voicestate.h \
    $$PWD/settings.h

DISTFILES += \
    $$PWD/settings.ini

SOURCES += \
    $$PWD/payloads/activityemoji.cpp \
    $$PWD/bot.cpp \
    $$PWD/eventhandler.cpp \
    $$PWD/gateway.cpp \
    $$PWD/jsonutils.cpp \
    $$PWD/logging/logfactory.cpp \
    $$PWD/logging/logger.cpp \
    $$PWD/logging/logworker.cpp \
    $$PWD/payloads/activity.cpp \
    $$PWD/payloads/activityassets.cpp \
    $$PWD/payloads/activityparty.cpp \
    $$PWD/payloads/activitysecrets.cpp \
    $$PWD/payloads/activitytimestamps.cpp \
    $$PWD/payloads/channel.cpp \
    $$PWD/payloads/clientstatus.cpp \
    $$PWD/payloads/emoji.cpp \
    $$PWD/payloads/gatewaypayload.cpp \
    $$PWD/payloads/guild.cpp \
    $$PWD/payloads/guildmember.cpp \
    $$PWD/payloads/heartbeat.cpp \
    $$PWD/payloads/hello.cpp \
    $$PWD/payloads/identify.cpp \
    $$PWD/payloads/identifyproperties.cpp \
    $$PWD/payloads/invalidsession.cpp \
    $$PWD/payloads/jsonserializable.cpp \
    $$PWD/payloads/permissionoverwrite.cpp \
    $$PWD/payloads/presenceupdate.cpp \
    $$PWD/payloads/ready.cpp \
    $$PWD/payloads/resume.cpp \
    $$PWD/payloads/role.cpp \
    $$PWD/payloads/updatestatus.cpp \
    $$PWD/payloads/user.cpp \
    $$PWD/payloads/voicestate.cpp \
    $$PWD/settings.cpp
