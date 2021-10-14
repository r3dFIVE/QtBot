/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef FILE_H
#define FILE_H

#include <QDataStream>
#include <QFile>
#include <QQmlContext>
#include <QTextStream>

#include "logging/logfactory.h"
#include "enums/openmode.h"


class File : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger();

    int _openMode;
    QSharedPointer<QFile> _file;
    QString _fileName;
    QTextStream _textStream;
    QDataStream _dataStream;

public:
    Q_INVOKABLE File(QObject *parent = nullptr);
    Q_INVOKABLE File(const File &other, QObject *parent = nullptr);
    Q_INVOKABLE File(const QString &filePath, const OpenMode::Mode openMode, QObject *parent = nullptr);
    Q_INVOKABLE ~File() {}

    Q_INVOKABLE File &operator=(const File &other);

    Q_INVOKABLE bool hasNext() const;
    Q_INVOKABLE bool open();
    Q_INVOKABLE void close();

    Q_INVOKABLE bool exists() const;
    Q_INVOKABLE bool remove();
    Q_INVOKABLE bool rename(const QString &newName);

    Q_INVOKABLE void write(const QString &string);
    Q_INVOKABLE void write(const QStringList &string);
    Q_INVOKABLE void writeLine(const QString &string);
    Q_INVOKABLE void writeLine(const QStringList &strings);
    Q_INVOKABLE QString fileName() const;
    Q_INVOKABLE QString errorString() const;
    Q_INVOKABLE QString readAll();
    Q_INVOKABLE QString readLine();

    void setParent(QObject *parent);
    QFile* get();
};

Q_DECLARE_METATYPE(File)

#endif // FILE_H
