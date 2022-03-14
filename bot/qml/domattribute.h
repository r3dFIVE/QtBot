/**
 *
 *
 * Original credit to https://github.com/lagner/QGumboParser
 *
 * DOMParsing code borrows _heavily_ from here!
 */

#ifndef DOMATTRIBUTE_H
#define DOMATTRIBUTE_H

#include <QObject>

#include "logging/logfactory.h"

class DOMAttribute : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger(this);

    QString _name;
    QString _value;

public:
    DOMAttribute(QObject* parent = nullptr) : QObject(parent) {}
    DOMAttribute(const char* utf8name, const char* utf8value, QObject* parent = nullptr);
    DOMAttribute(const DOMAttribute &other, QObject* parent = nullptr);
    ~DOMAttribute() {
        QString ptrStr = QString("0x%1").arg((quintptr)this,
                            QT_POINTER_SIZE * 2, 16, QChar('0'));

        _logger->trace(QString("Destroyed DOMAttribute(%1)").arg(ptrStr));
    }

    const QString& name() const { return _name; }
    const QString& value() const { return _value; }
};

Q_DECLARE_METATYPE(DOMAttribute)

#endif // DOMATTRIBUTE_H
