#ifndef FILEIO_H
#define FILEIO_H

#include <QFile>
#include <QObject>
#include <QQmlContext>
#include <QTextStream>

#include "logging/logfactory.h"
#include "enums/openmode.h"


class File : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger();

    int _openMode;
    QFile _file;
    QString _fileName;
    QTextStream _textStream;

public:

    Q_INVOKABLE File() {}
    Q_INVOKABLE File(const File &other);
    Q_INVOKABLE File(const QString &filePath, const OpenMode::Mode openMode, QObject *parent = nullptr);
    Q_INVOKABLE~File() {}

    Q_INVOKABLE File &operator=(const File &other);

    Q_INVOKABLE bool hasNext() const;
    Q_INVOKABLE bool open();
    Q_INVOKABLE void write(const QString &string);
    Q_INVOKABLE void write(const QStringList &string);
    Q_INVOKABLE void writeLine(const QString &string);
    Q_INVOKABLE void writeLine(const QStringList &strings);
    Q_INVOKABLE QString fileName() const;
    Q_INVOKABLE QString readAll();
    Q_INVOKABLE QString readLine();
};

#endif // FILEIO_H
