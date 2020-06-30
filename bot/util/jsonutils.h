#ifndef JSONUTILS_H
#define JSONUTILS_H

#include "logging/logfactory.h"
#include "payloads/jsonserializable.h"
#include <QMetaProperty>

struct JsonUtils
{
    static void readFromJson(QObject &target, const QJsonObject &source);
    static void writeToJson(QObject &source, QJsonObject &target);
    static QJsonObject toQJsonObject(QObject &source);
    static QByteArray toQByteArray(QObject &source);
    static QString toQString(QObject &source);
    static void fromQJsonObject(QObject &target, const QJsonObject &source);
    static void fromQString(QObject &target, const QString &source);
    static void fromQByteArray(QObject &target, const QByteArray &source);
};

#endif // JSONUTILS_H
