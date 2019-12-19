
QT += websockets gui

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
    src/bot.cpp \
    src/eventservice.cpp \
    src/gatewayservice.cpp \
    src/jsonserializer.cpp \
    src/loggingservice.cpp \
    src/main.cpp \
    src/bot.cpp \
    src/jsonserializer.cpp \
    src/main.cpp \
    src/settingsservice.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/src/.
DEPENDPATH += $$PWD/src/.

DISTFILES += \
    settings.ini \
    src/spdlog/fmt/bundled/LICENSE.rst

HEADERS += \
    src/bot.h \
    src/eventservice.h \
    src/gatewayservice.h \
    src/globals.h \
    src/jsonserializeable.h \
    src/jsonserializer.h \
    src/lockingdeque.h \
    src/loggingservice.h \
    src/payloads/gatewaypayload.h \
    src/bot.h \
    src/jsonserializeable.h \
    src/jsonserializer.h \
    src/lockingdeque.h \
    src/payloads/gatewaypayload.h \
    src/payloads/hello.h \
    src/payloads/gatewaypayload.h \
    src/payloads/hello.h \
    src/payloads/heartbeat.h \
    src/settingsservice.h \
    src/spdlog/async.h \
    src/spdlog/async_logger-inl.h \
    src/spdlog/async_logger.h \
    src/spdlog/common-inl.h \
    src/spdlog/common.h \
    src/spdlog/details/backtracer-inl.h \
    src/spdlog/details/backtracer.h \
    src/spdlog/details/circular_q.h \
    src/spdlog/details/console_globals.h \
    src/spdlog/details/file_helper-inl.h \
    src/spdlog/details/file_helper.h \
    src/spdlog/details/fmt_helper.h \
    src/spdlog/details/log_msg-inl.h \
    src/spdlog/details/log_msg.h \
    src/spdlog/details/log_msg_buffer-inl.h \
    src/spdlog/details/log_msg_buffer.h \
    src/spdlog/details/mpmc_blocking_q.h \
    src/spdlog/details/null_mutex.h \
    src/spdlog/details/os-inl.h \
    src/spdlog/details/os.h \
    src/spdlog/details/pattern_formatter-inl.h \
    src/spdlog/details/pattern_formatter.h \
    src/spdlog/details/periodic_worker-inl.h \
    src/spdlog/details/periodic_worker.h \
    src/spdlog/details/registry-inl.h \
    src/spdlog/details/registry.h \
    src/spdlog/details/synchronous_factory.h \
    src/spdlog/details/thread_pool-inl.h \
    src/spdlog/details/thread_pool.h \
    src/spdlog/fmt/bin_to_hex.h \
    src/spdlog/fmt/bundled/chrono.h \
    src/spdlog/fmt/bundled/color.h \
    src/spdlog/fmt/bundled/compile.h \
    src/spdlog/fmt/bundled/core.h \
    src/spdlog/fmt/bundled/format-inl.h \
    src/spdlog/fmt/bundled/format.h \
    src/spdlog/fmt/bundled/locale.h \
    src/spdlog/fmt/bundled/ostream.h \
    src/spdlog/fmt/bundled/posix.h \
    src/spdlog/fmt/bundled/printf.h \
    src/spdlog/fmt/bundled/ranges.h \
    src/spdlog/fmt/bundled/safe-duration-cast.h \
    src/spdlog/fmt/fmt.h \
    src/spdlog/fmt/ostr.h \
    src/spdlog/formatter.h \
    src/spdlog/logger-inl.h \
    src/spdlog/logger.h \
    src/spdlog/sinks/android_sink.h \
    src/spdlog/sinks/ansicolor_sink-inl.h \
    src/spdlog/sinks/ansicolor_sink.h \
    src/spdlog/sinks/base_sink-inl.h \
    src/spdlog/sinks/base_sink.h \
    src/spdlog/sinks/basic_file_sink-inl.h \
    src/spdlog/sinks/basic_file_sink.h \
    src/spdlog/sinks/daily_file_sink.h \
    src/spdlog/sinks/dist_sink.h \
    src/spdlog/sinks/dup_filter_sink.h \
    src/spdlog/sinks/msvc_sink.h \
    src/spdlog/sinks/null_sink.h \
    src/spdlog/sinks/ostream_sink.h \
    src/spdlog/sinks/ringbuffer_sink.h \
    src/spdlog/sinks/rotating_file_sink-inl.h \
    src/spdlog/sinks/rotating_file_sink.h \
    src/spdlog/sinks/sink-inl.h \
    src/spdlog/sinks/sink.h \
    src/spdlog/sinks/stdout_color_sinks-inl.h \
    src/spdlog/sinks/stdout_color_sinks.h \
    src/spdlog/sinks/stdout_sinks-inl.h \
    src/spdlog/sinks/stdout_sinks.h \
    src/spdlog/sinks/syslog_sink.h \
    src/spdlog/sinks/systemd_sink.h \
    src/spdlog/sinks/wincolor_sink-inl.h \
    src/spdlog/sinks/wincolor_sink.h \
    src/spdlog/spdlog-inl.h \
    src/spdlog/spdlog.h \
    src/spdlog/tweakme.h \
    src/spdlog/version.h
