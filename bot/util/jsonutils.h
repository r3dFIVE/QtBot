#ifndef JSONUTILS_H
#define JSONUTILS_H

#include "logging/logfactory.h"
#include "payloads/jsonserializable.h"
#include <QMetaProperty>

struct JsonUtils
{
    static void readFromJson(QObject &target, const QJsonObject &source);
    static void writeToJson(const QObject &source, QJsonObject &target);
    static QJsonObject toQJsonObject(const QObject &source);
    static QString toQString(const QObject &source);
    static QByteArray toQByteArray(const QObject &source);
    static QJsonDocument toJsonDocument(const QObject &source);
    static QVariant toVariant(const QObject &source);
    static void fromQJsonObject(QObject &target, const QJsonObject &source);
    static void fromQString(QObject &target, const QString &source);
    static void fromQByteArray(QObject &target, const QByteArray &source);
    static void fromJsonDocument(QObject &target, const QJsonDocument &source);
    static void fromVariant(QObject &target, const QVariant &source);
};

#endif // JSONUTILS_H
