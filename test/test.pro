QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    payloads/tst_activity.cpp \
    payloads/tst_activityassets.cpp \
    payloads/tst_activityemoji.cpp \
    payloads/tst_activityparty.cpp \
    payloads/tst_activitysecrets.cpp \
    payloads/tst_activitytimestamps.cpp \
    payloads/tst_channel.cpp \
    payloads/tst_clientstatus.cpp \
    payloads/tst_emoji.cpp \
    payloads/tst_gatewaypayload.cpp \
    payloads/tst_guildmemeber.cpp \
    payloads/tst_identify.cpp \
    payloads/tst_identifyproperties.cpp \
    payloads/tst_invalidsession.cpp \
    payloads/tst_permissionoverwrite.cpp \
    payloads/tst_presenceupdate.cpp \
    payloads/tst_resume.cpp \
    payloads/tst_role.cpp \
    payloads/tst_updatestatus.cpp \
    payloads/tst_voicestate.cpp \
    testmain.cpp \
    testsuite.cpp \
    payloads/tst_heartbeat.cpp \
    payloads/tst_hello.cpp \
    payloads/tst_user.cpp

HEADERS += \
    payloads/tst_activity.h \
    payloads/tst_activityassets.h \
    payloads/tst_activityemoji.h \
    payloads/tst_activityparty.h \
    payloads/tst_activitysecrets.h \
    payloads/tst_activitytimestamps.h \
    payloads/tst_channel.h \
    payloads/tst_clientstatus.h \
    payloads/tst_emoji.h \
    payloads/tst_gatewaypayload.h \
    payloads/tst_guildmemeber.h \
    payloads/tst_identify.h \
    payloads/tst_identifyproperties.h \
    payloads/tst_invalidsession.h \
    payloads/tst_permissionoverwrite.h \
    payloads/tst_presenceupdate.h \
    payloads/tst_resume.h \
    payloads/tst_role.h \
    payloads/tst_updatestatus.h \
    payloads/tst_voicestate.h \
    testsuite.h \
    payloads/testpayloads.h \
    payloads/tst_heartbeat.h \
    payloads/tst_hello.h \
    payloads/tst_user.h

include(../bot/bot.pri)
