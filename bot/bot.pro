QT += gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

include(main.pri)
include(bot.pri)

win32 {
    TARGET_CUSTOM_EXT = .exe
    DEPLOY_COMMAND = $$[QT_INSTALL_BINS]\windeployqt
    DEPLOY_OPTIONS = "--no-svg --no-system-d3d-compiler --no-opengl --no-angle --no-opengl-sw"

    CONFIG( debug, debug|release ) {
        # debug
        DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/debug/$${TARGET}$${TARGET_CUSTOM_EXT}))
        DEPLOY_OPTIONS += "--debug"
    } else {
        # release
        DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}$${TARGET_CUSTOM_EXT}))
        DEPLOY_OPTIONS += "--release"
    }


    QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_OPTIONS} $${DEPLOY_TARGET}
}

DISTFILES += \
    main.pri

