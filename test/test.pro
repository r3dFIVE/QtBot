QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    payloads/tst_activity.cpp \
    payloads/tst_assets.cpp \
    payloads/tst_gatewaypayload.cpp \
    payloads/tst_party.cpp \
    payloads/tst_properties.cpp \
    payloads/tst_resume.cpp \
    payloads/tst_secrets.cpp \
    testmain.cpp \
    testsuite.cpp \
    payloads/tst_emoji.cpp \
    payloads/tst_heartbeat.cpp \
    payloads/tst_hello.cpp \
    payloads/tst_timestamps.cpp \
    payloads/tst_user.cpp

HEADERS += \
    payloads/tst_activity.h \
    payloads/tst_assets.h \
    payloads/tst_gatewaypayload.h \
    payloads/tst_party.h \
    payloads/tst_properties.h \
    payloads/tst_resume.h \
    payloads/tst_secrets.h \
    tests.h \
    testsuite.h \
    payloads/testpayloads.h \
    payloads/tst_emoji.h \
    payloads/tst_heartbeat.h \
    payloads/tst_hello.h \
    payloads/tst_timestamps.h \
    payloads/tst_user.h

include(../bot/bot.pri)
