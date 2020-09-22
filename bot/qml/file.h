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

    File() {}
    File(const File &other);
    File(const QString &filePath, const OpenMode::Mode openMode, QObject *parent = nullptr);
    ~File() {
        _logger->info("FILEIO DESTROYED!!!");
    }

    File &operator=(const File &other);

public slots:
    bool hasNext() const;
    bool open();
    void write(const QString &string);
    void write(const QStringList &string);
    void writeLine(const QString &string);
    void writeLine(const QStringList &strings);
    QString fileName() const;
    QString readAll();
    QString readLine();
};

#endif // FILEIO_H
