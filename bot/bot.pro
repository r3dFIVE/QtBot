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


    MONGODEPS.files += $${MONGO_C_BIN}/bson-1.0.dll
    MONGODEPS.files += $${MONGO_C_BIN}/mongoc-1.0.dll
    MONGODEPS.files += $${MONGO_CXX_BIN}/bsoncxx.dll
    MONGODEPS.files += $${MONGO_CXX_BIN}/mongocxx.dll

    CONFIG( debug, debug|release ) {
        # debug
        DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/debug/$${TARGET}$${TARGET_CUSTOM_EXT}))
        DEPLOY_OPTIONS += "--debug"
        MONGODEPS.path = $$shell_quote($$shell_path($${OUT_PWD}/debug))
    } else {
        # release
        DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}$${TARGET_CUSTOM_EXT}))
        DEPLOY_OPTIONS += "--release"
        MONGODEPS.path = $$shell_quote($$shell_path($${OUT_PWD}/release))
    }
}

DISTFILES += \
    main.pri

