QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    payloads/tst_gatewaypayload.cpp \
    testmain.cpp \
    testsuite.cpp \
    payloads/tst_emoji.cpp \
    payloads/tst_heartbeat.cpp \
    payloads/tst_hello.cpp

HEADERS += \
    payloads/tst_gatewaypayload.h \
    tests.h \
    testsuite.h \
    payloads/testpayloads.h \
    payloads/tst_emoji.h \
    payloads/tst_heartbeat.h \
    payloads/tst_hello.h

include(../bot/bot.pri)
