#ifndef QMLFACTORY_H
#define QMLFACTORY_H

#include <QObject>

#include "botjob/databasecontext.h"


class QmlFactory : public QObject
{
    Q_OBJECT

    DatabaseContext _databaseContext;
public:

    QmlFactory(const DatabaseContext &context);

public slots:
    QObject* createObject(const QString& typeName, const QVariantMap& arguments);
};

#endif // QMLFACTORY_H
