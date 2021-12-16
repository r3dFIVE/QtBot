#ifndef GRIDFSFILE_H
#define GRIDFSFILE_H

#include "payloads/jsonserializable.h"

class GridFSFile : public JsonSerializable
{
    Q_OBJECT

public:

    static const QString OBJECT_ID;
    static const QString LENGTH;
    static const QString CHUNK_SIZE;
    static const QString UPLOAD_DATE;
    static const QString FILENAME;
    static const QString METADATA;

    GridFSFile() {}
    GridFSFile(const QByteArray &json) : JsonSerializable(json) {}
    GridFSFile(const QJsonObject &json) : JsonSerializable(json) {}
    GridFSFile(const QString &json) : JsonSerializable(json) {}
    GridFSFile operator=(const GridFSFile &other) {
        if (this == &other) {
            return *this;
        }

        _jsonObject = other._jsonObject;

        return *this;
    }

    QJsonValue getObjectId() const;
    QJsonValue getLength() const;
    QJsonValue getChunkSize() const;
    QJsonValue getUploadDate() const;
    QJsonValue getFilename() const;
    QJsonObject getMetaData() const;
};

#endif // GRIDFSFILE_H
