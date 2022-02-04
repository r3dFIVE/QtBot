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

    GridFSFile(QObject *parent = nullptr) : JsonSerializable(parent) {}
    GridFSFile(const GridFSFile &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    GridFSFile(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    GridFSFile(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    GridFSFile(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    QJsonValue getObjectId() const;
    QJsonValue getLength() const;
    QJsonValue getChunkSize() const;
    QJsonValue getUploadDate() const;
    QJsonValue getFilename() const;
    QJsonObject getMetaData() const;
};

#endif // GRIDFSFILE_H
