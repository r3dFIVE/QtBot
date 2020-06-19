#ifndef TYPEFACTORY_H
#define TYPEFACTORY_H

#include <QObject>
#include <QSharedPointer>

#include <logging/logcontext.h>

struct TypeFactory {
    TypeFactory() {
        qRegisterMetaType<LogContext::LogLevel>();
    }
};

Q_DECLARE_METATYPE(QSharedPointer<int>)

static TypeFactory TYPEFACTORY;

#endif // TYPEFACTORY_H
