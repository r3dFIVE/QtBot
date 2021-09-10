#ifndef MIMEUTILS_H
#define MIMEUTILS_H

#include <QFile>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QObject>

class MimeUtils {
public:
    static bool isTextContent(const QFile &file) {
        return isTextContent(getMimeType(file).name());
    }

    static bool isTextContent(const QString &contentType) {
        return (contentType.contains("text/")
                   || contentType.contains("application/xml")
                   || contentType.contains("application/json")) ;
    }

    static QMimeType getMimeType(const QByteArray &data) {
        return QMimeDatabase().mimeTypeForData(data);
    }

    static QMimeType getMimeType(const QFile &file) {
        return getMimeType(QFileInfo(file));
    }

    static QMimeType getMimeType(QFileInfo file) {
        return QMimeDatabase().mimeTypeForFile(file);
    }

    static QList<QMimeType> getMimeType(const QString &fileName) {
        return QMimeDatabase().mimeTypesForFileName(fileName);
    }
};

#endif // MIMEUTILS_H
