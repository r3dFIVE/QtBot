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

#include "file.h"

#include <QDir>

#include "util/mimeutils.h"


File::File(QObject *parent) : QObject(parent) {
    _openMode = OpenMode::ReadWrite;

    _file = QSharedPointer<QFile>(new QFile);
}

File::File(const QString &fileName,
           const OpenMode::Mode openMode,
           QObject *parent) : QObject(parent) {

    _fileName = fileName;

    _openMode = openMode;

    _file = QSharedPointer<QFile>(new QFile);
}

File::File(const File &other, QObject *parent) : QObject(parent) {
    if (this == &other) {
        return;
    }

    _fileName = other._fileName;

    _openMode = other._openMode;

    _file = other._file;
}

File
&File::operator=(const File &other) {
    if (this == &other) {
        return *this;
    }

    _fileName = other._fileName;

    _openMode = other._openMode;

    _file = other._file;

    return *this;
}

bool
File::hasNext() const {
    return !_textStream.atEnd();
}

bool
File::open() {
    _file->setFileName(_fileName);

    if (!_file->open(QIODevice::OpenMode(_openMode))) {
        _logger->warning(QString("Failed to open %1, with openmode: %2. Reason: %3")
                         .arg(_fileName)
                         .arg(OpenMode::Mode(_openMode))
                         .arg(_file->errorString()));

        return false;
    }

    if (MimeUtils::isTextContent(*_file)) {
        _textStream.setDevice(_file.data());
    } else {
        _dataStream.setDevice(_file.data());
    }

    return true;
}

bool
File::exists() const {
    return _file->exists(_fileName);
}

bool
File::remove() {
    return _file->remove();
}

bool
File::rename(const QString &name) {
    return _file->rename(name);
}

void
File::write(const QString &string) {
    _textStream << string;

    _textStream.flush();
}

void
File::write(const QStringList &strings) {
    for (QString string : strings) {
        write(string);
    }
}

void
File::writeLine(const QString &string) {
    _textStream << string << "\n";

    _textStream.flush();
}

void
File::writeLine(const QStringList &strings) {
    for (QString string : strings) {
        writeLine(string);
    }
}

int
File::writeRawData(const char *data, int len) {
    int byteWritten = 0;

    open();

    if (_dataStream.status() == QDataStream::Ok) {
       byteWritten = _dataStream.writeRawData(data, len);

    } else {
       _logger->warning(QString("Failed to writeRawData, STATUS: %1").arg(_dataStream.status()));
    }

    return byteWritten;
}

void
File::setFileName(const QString &fileName) {
    _fileName = fileName;
}

QString
File::fileName() const {
    return _file->fileName();
}

QString
File::getPath() {
    return QFileInfo(*_file.data()).absolutePath();
}

QString
File::errorString() const {
    return _file->errorString();
}

QString
File::readLine() {
    return _textStream.readLine();
}

void
File::setParent(QObject *parent) {
    _file->setParent(parent);
}

void
File::close() {
    _file->close();
}

QFile*
File::get() {
    if (!_file->isOpen()) {
        open();
    }
    return _file.data();
}

QString
File::readAll() {
    return _textStream.readAll();
}
