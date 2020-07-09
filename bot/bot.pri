QT += websockets sql qml

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.


HEADERS += \
    $$PWD/httpclient.h \
    $$PWD/payloads/activityemoji.h \
    $$PWD/bot.h \
    $$PWD/eventhandler.h \
    $$PWD/gateway.h \
    $$PWD/logging/logcontext.h \
    $$PWD/logging/logfactory.h \
    $$PWD/logging/logger.h \
    $$PWD/logging/logworker.h \
    $$PWD/payloads/activity.h \
    $$PWD/payloads/activityassets.h \
    $$PWD/payloads/attachment.h \
    $$PWD/payloads/channelmention.h \
    $$PWD/payloads/embed.h \
    $$PWD/payloads/embedauthor.h \
    $$PWD/payloads/embedfield.h \
    $$PWD/payloads/embedfooter.h \
    $$PWD/payloads/embedimage.h \
    $$PWD/payloads/embedprovider.h \
    $$PWD/payloads/embedthumbnail.h \
    $$PWD/payloads/embedvideo.h \
    $$PWD/payloads/invalidsession.h \
    $$PWD/payloads/activityparty.h \
    $$PWD/payloads/activitysecrets.h \
    $$PWD/payloads/activitytimestamps.h \
    $$PWD/payloads/channel.h \
    $$PWD/payloads/clientstatus.h \
    $$PWD/payloads/emoji.h \
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
    $$PWD/payloads/message.h \
    $$PWD/payloads/messageactivity.h \
    $$PWD/payloads/messageapplication.h \
    $$PWD/payloads/messagereference.h \
    $$PWD/payloads/permissionoverwrite.h \
    $$PWD/payloads/presenceupdate.h \
    $$PWD/payloads/reaction.h \
    $$PWD/payloads/ready.h \
    $$PWD/payloads/resume.h \
    $$PWD/payloads/role.h \
    $$PWD/payloads/updatestatus.h \
    $$PWD/payloads/user.h \
    $$PWD/payloads/voicestate.h \
    $$PWD/qml/botscript.h \
    $$PWD/qml/bsqldatabase.h \
    $$PWD/qml/eventcontext.h \
    $$PWD/routes/createmessage.h \
    $$PWD/routes/route.h \
    $$PWD/qml/scriptfactory.h \
    $$PWD/qml/scriptregistrar.h \
    $$PWD/util/function.h \
    $$PWD/util/settings.h \
    $$PWD/util/globals.h \
    $$PWD/util/lockingdeque.h \
    $$PWD/util/jsonutils.h

DISTFILES += \
    $$PWD/settings.ini

SOURCES += \
    $$PWD/bot.cpp \
    $$PWD/eventhandler.cpp \
    $$PWD/gateway.cpp \
    $$PWD/httpclient.cpp \
    $$PWD/logging/logfactory.cpp \
    $$PWD/logging/logger.cpp \
    $$PWD/logging/logworker.cpp \
    $$PWD/payloads/activity.cpp \
    $$PWD/payloads/activityassets.cpp \
    $$PWD/payloads/activityemoji.cpp \
    $$PWD/payloads/activityparty.cpp \
    $$PWD/payloads/activitysecrets.cpp \
    $$PWD/payloads/activitytimestamps.cpp \
    $$PWD/payloads/attachment.cpp \
    $$PWD/payloads/channel.cpp \
    $$PWD/payloads/channelmention.cpp \
    $$PWD/payloads/clientstatus.cpp \
    $$PWD/payloads/embed.cpp \
    $$PWD/payloads/embedauthor.cpp \
    $$PWD/payloads/embedfield.cpp \
    $$PWD/payloads/embedfooter.cpp \
    $$PWD/payloads/embedimage.cpp \
    $$PWD/payloads/embedprovider.cpp \
    $$PWD/payloads/embedthumbnail.cpp \
    $$PWD/payloads/embedvideo.cpp \
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
    $$PWD/payloads/message.cpp \
    $$PWD/payloads/messageactivity.cpp \
    $$PWD/payloads/messageapplication.cpp \
    $$PWD/payloads/messagereference.cpp \
    $$PWD/payloads/permissionoverwrite.cpp \
    $$PWD/payloads/presenceupdate.cpp \
    $$PWD/payloads/reaction.cpp \
    $$PWD/payloads/ready.cpp \
    $$PWD/payloads/resume.cpp \
    $$PWD/payloads/role.cpp \
    $$PWD/payloads/updatestatus.cpp \
    $$PWD/payloads/user.cpp \
    $$PWD/payloads/voicestate.cpp \
    $$PWD/qml/botscript.cpp \
    $$PWD/qml/bsqldatabase.cpp \
    $$PWD/qml/eventcontext.cpp \
    $$PWD/routes/createmessage.cpp \
    $$PWD/qml/scriptfactory.cpp \
    $$PWD/qml/scriptregistrar.cpp \
    $$PWD/util/jsonutils.cpp \
    $$PWD/util/settings.cpp
