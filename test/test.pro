QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    payloads/tst_gatewaypayload.cpp \
    payloads/tst_party.cpp \
    testmain.cpp \
    testsuite.cpp \
    payloads/tst_emoji.cpp \
    payloads/tst_heartbeat.cpp \
    payloads/tst_hello.cpp \
    payloads/tst_timestamps.cpp

HEADERS += \
    payloads/tst_gatewaypayload.h \
    payloads/tst_party.h \
    tests.h \
    testsuite.h \
    payloads/testpayloads.h \
    payloads/tst_emoji.h \
    payloads/tst_heartbeat.h \
    payloads/tst_hello.h \
    payloads/tst_timestamps.h

include(../bot/bot.pri)
