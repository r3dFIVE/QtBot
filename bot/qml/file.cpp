#include "file.h"

#include "util/enumutils.h"


File::File(const QString &fileName,
           const OpenMode::Mode openMode,
           QObject *parent) : QObject(parent) {

    _fileName = fileName;

    _openMode = openMode;
}

File::File(const File &other) {
    _fileName = other._fileName;

    _openMode = other._openMode;
}

File
&File::operator=(const File &other) {
    _fileName = other._fileName;

    _openMode = other._openMode;

    return *this;
}

bool
File::hasNext() const {
    return !_textStream.atEnd();
}

bool
File::open() {
    _file.setFileName(_fileName);

    if (!_file.open(QIODevice::OpenMode(_openMode))) {
        _logger->warning(QString("Failed to open %1, with openmode: %2. Reason: %3")
                         .arg(_fileName)
                         .arg(OpenMode::Mode(_openMode))
                         .arg(_file.errorString()));

        return false;
    }

    _textStream.setDevice(&_file);

    return true;
}

bool
File::exists() const {
    return _file.exists(_fileName);
}

bool
File::remove() {
    return _file.remove();
}

bool
File::rename(const QString &newName) {
    return _file.rename(newName);
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

QString
File::fileName() const {
    return _file.fileName();
}

QString
File::errorString() const {
    return _file.errorString();
}

QString
File::readLine() {
    return _textStream.readLine();
}

QString
File::readAll() {
    return _textStream.readAll();
}
