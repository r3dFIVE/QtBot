#include "gridfsfile.h"

const QString GridFSFile::OBJECT_ID = "_id";
const QString GridFSFile::LENGTH = "length";
const QString GridFSFile::CHUNK_SIZE = "chunkSize";
const QString GridFSFile::UPLOAD_DATE = "uploadDate";
const QString GridFSFile::FILENAME = "filename";
const QString GridFSFile::METADATA = "metadata";

QJsonValue
GridFSFile::getObjectId() const {
    return _jsonObject[OBJECT_ID];
}

QJsonValue
GridFSFile::getLength() const {
    return _jsonObject[LENGTH];
}

QJsonValue
GridFSFile::getChunkSize() const {
    return _jsonObject[CHUNK_SIZE];
}

QJsonValue
GridFSFile::getUploadDate() const {
    return _jsonObject[UPLOAD_DATE];
}

QJsonValue
GridFSFile::getFilename() const {
    return _jsonObject[FILENAME];
}

QJsonObject
GridFSFile::getMetaData() const {
    return _jsonObject[METADATA].toObject();
}
