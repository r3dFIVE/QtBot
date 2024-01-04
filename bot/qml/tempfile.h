#ifndef TEMPFILE_H
#define TEMPFILE_H

#include "file.h"
#include <QDebug>
#include <QObject>
#include <QDir>
#include <QUuid>


class TempFile : public File
{
    Q_OBJECT


    Logger *_logger = LogFactory::getLogger(this);

    bool createTempPath(const QString &fileName = QString()) {
        QString tempPath = QString("%1/%2")
                .arg(Settings::tempDirectory())
                .arg(QUuid::createUuid().toString(QUuid::Id128));

        if (!fileName.isEmpty()) {
            _fileName = QString("%1/%2")
                    .arg(tempPath)
                    .arg(fileName);
        } else {
            _fileName = QString("%1/%2")
                    .arg(tempPath)
                    .arg(QUuid::createUuid().toString(QUuid::Id128));
        }

        QDir().mkpath(tempPath);

        bool isSuccess = true;

        if (_fileName.isEmpty() || !QDir(tempPath).isReadable()) {
            isSuccess = false;
        }

        return isSuccess;
    };


public:
    TempFile(QObject *parent = nullptr) : File{parent} {
        LogUtils::logConstructor(this);

        createTempPath();
    }

    TempFile(const QString &fileName, QObject *parent = nullptr) : File{parent} {
        LogUtils::logConstructor(this);

        createTempPath(fileName);
    }

    TempFile(const QString &fileName, const OpenMode::Mode openMode, QObject *parent = nullptr) : File{parent} {
        LogUtils::logConstructor(this);

        createTempPath(fileName);

        _openMode = openMode;        
    }

    ~TempFile() {                
        LogUtils::logDestructor(this);

        if (_file) {
            _file->close();
        }

        QFileInfo fileInfo(_fileName);

        QDir dir(fileInfo.absolutePath());

        dir.removeRecursively();
    }
};

Q_DECLARE_METATYPE(TempFile)

#endif // TEMPFILE_H
