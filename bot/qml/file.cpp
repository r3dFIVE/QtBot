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

    bool ok = _file.open(QIODevice::OpenMode(_openMode));

    _textStream.setDevice(&_file);

    return ok;
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
File::readLine() {
    return _textStream.readLine();
}

QString
File::readAll() {
    return _textStream.readAll();
}
