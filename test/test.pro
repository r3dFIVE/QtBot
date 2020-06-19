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
    payloads/tst_gatewaypayload.cpp \
    payloads/tst_identifyproperties.cpp \
    payloads/tst_resume.cpp \
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
    payloads/tst_gatewaypayload.h \
    payloads/tst_identifyproperties.h \
    payloads/tst_resume.h \
    tests.h \
    testsuite.h \
    payloads/testpayloads.h \
    payloads/tst_heartbeat.h \
    payloads/tst_hello.h \
    payloads/tst_user.h

include(../bot/bot.pri)
