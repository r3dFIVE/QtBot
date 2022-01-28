#ifndef TEMPFILE_H
#define TEMPFILE_H

#include "file.h"
#include <QDebug>
#include <QObject>
#include <QDir>
#include <QUuid>
#include <QQmlEngine>


class TempFile : public File
{
    Q_OBJECT

    QString makeTempPath() const {
        QString tempPath = QString("%1/%2")
                .arg(Settings::tempDirectory())
                .arg(QUuid::createUuid().toString(QUuid::Id128));

        QDir().mkpath(tempPath);

        return tempPath;
    };

public:
    TempFile(QObject *parent = nullptr) : File{parent} {
        _fileName = QString("%1/%2")
                .arg(makeTempPath())
                .arg(QUuid::createUuid().toString(QUuid::Id128));
    }

    TempFile(const QString &fileName, QObject *parent = nullptr) : File{parent} {
        if (!fileName.isEmpty()) {
            _fileName = QString("%1/%2")
                    .arg(makeTempPath())
                    .arg(fileName);
        } else {
            _fileName = QString("%1/%2")
                    .arg(makeTempPath())
                    .arg(QUuid::createUuid().toString(QUuid::Id128));
        }
    }

    ~TempFile() {        
        QDir dir(QFileInfo(*_file.get()).absolutePath());

        _file->close();

        dir.removeRecursively();
    }
};

Q_DECLARE_METATYPE(TempFile)

#endif // TEMPFILE_H
