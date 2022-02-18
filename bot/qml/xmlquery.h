
#ifndef XMLQUERY_H
#define XMLQUERY_H

#include <QFile>
#include <QObject>
#include <QDebug>
#include <QSharedPointer>
#include <QXmlItem>
#include <QXmlQuery>
#include <QDomDocument>
#include <QJsonObject>

#include "logging/logfactory.h"

#include "file.h"

class XMLQuery : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger();
    QXmlQuery _query;

public:

    XMLQuery(QObject *parent = nullptr) : QObject(parent) {}
    XMLQuery(const XMLQuery &other, QObject *parent = nullptr) : QObject(parent) {
        Q_UNUSED(other);
    }
    ~XMLQuery() {
        QString ptrStr = QString("0x%1").arg((quintptr)this,
                            QT_POINTER_SIZE * 2, 16, QChar('0'));

        _logger->trace(QString("Destroyed XMLQuery(%1)").arg(ptrStr));
    }

    Q_INVOKABLE bool setFocusString(const QString &focus);
    Q_INVOKABLE bool setFocusUrl(const QString &focus);
    Q_INVOKABLE bool setFocusFile(File *focus);
    Q_INVOKABLE void setQuery(const QString &query);
    Q_INVOKABLE QString getXMLString(const int spacing = -1);
    Q_INVOKABLE QJsonObject getJSON(const int spacing = -1);


    bool setFocus(const QXmlItem &focus);

};

Q_DECLARE_METATYPE(XMLQuery)

#endif // XMLQUERY_H
