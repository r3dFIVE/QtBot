#ifndef LOGUTILS_H
#define LOGUTILS_H

#include <QObject>


class LogUtils
{
    static void doLogging(const QString &verb, QObject *obj, const QString &appendValue);
public:
    static void logConstructor(QObject *obj, const QString &appendValue = QString());
    static void logDestructor(QObject *obj, const QString &appendValue = QString());
};

#endif // LOGUTILS_H
