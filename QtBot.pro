QT -= gui
QT += websockets

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/bot.cc \
    src/gatewayconnection.cc \
    src/main.cc \
    src/messagehandler.cc \
    src/payloads/user.pb.cc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/lib/debug/libsodium/ -llibsodium

INCLUDEPATH += $$PWD/lib/debug/libsodium/include
DEPENDPATH += $$PWD/lib/debug/libsodium

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/debug/libsodium/libsodium.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/debug/libsodium/libsodium.lib

win32: LIBS += -L$$PWD/lib/debug/opus/ -lopus

INCLUDEPATH += $$PWD/lib/debug/opus/include
DEPENDPATH += $$PWD/lib/debug/opus

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/debug/opus/opus.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/debug/opus/libopus.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/debug/protobuf/lib/ -llibprotobuf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/protobuf/lib/ -llibprotobufd

INCLUDEPATH += $$PWD/lib/debug/protobuf/include
DEPENDPATH += $$PWD/lib/debug/protobuf/

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/debug/protobuf/lib/liblibprotobuf.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/debug/protobuf/lib/liblibprotobufd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/debug/protobuf/lib/libprotobuf.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/debug/protobuf/lib/libprotobufd.lib

DISTFILES +=

HEADERS += \
    gatewayopcodes.h \
    src/bot.h \
    src/gatewayconnection.h \
    src/lockingqueue.h \
    src/messagehandler.h \
    src/opcodes/gatewayopcodes.h \
    src/payloads/gatewaypayload.h
