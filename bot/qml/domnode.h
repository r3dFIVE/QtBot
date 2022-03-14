/**
 *
 *
 * Original credit to https://github.com/lagner/QGumboParser
 *
 * DOMParsing code borrows _heavily_ from here!
 */

#ifndef DOMNODE_H
#define DOMNODE_H

#include <QObject>
#include <QJsonObject>
#include <functional>

#include "gumbo.h"
#include "enums/htmltag.h"
#include "logging/logfactory.h"

class QString;
class DOMNode;
class DOMAttribute;
class DOMParser;
class QStringList;


class DOMNode : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger(this);

    DOMNode(GumboNode* node, QObject *parent = nullptr);

    GumboNode* _ptr;

    friend class DOMParser;

public:
    DOMNode(QObject *parent = nullptr) : QObject(parent) {}
    DOMNode(const DOMNode &other, QObject *parent = nullptr);
    ~DOMNode() {
        QString ptrStr = QString("0x%1").arg((quintptr)this,
                            QT_POINTER_SIZE * 2, 16, QChar('0'));

        _logger->trace(QString("Destroyed DOMNode(%1)").arg(ptrStr));
    };

    DOMNode(DOMNode&&, QObject *parent = nullptr) noexcept;
    DOMNode& operator=(const DOMNode& other);

    Q_INVOKABLE HtmlTag::Tag tag() const;
    Q_INVOKABLE QString tagName() const;
    Q_INVOKABLE QString nodeName() const;

    Q_INVOKABLE QString id() const;
    Q_INVOKABLE QStringList classList() const;

    Q_INVOKABLE DOMNode* getElementById(const QString&);
    Q_INVOKABLE QList<QObject*> getElementsByTagName(HtmlTag::Tag);
    Q_INVOKABLE QList<QObject*> getElementsByClassName(const QString&);
    Q_INVOKABLE QList<QObject*> childNodes();
    Q_INVOKABLE QList<QObject*> children();

    Q_INVOKABLE int childElementCount();

    Q_INVOKABLE bool isElement() const;
    Q_INVOKABLE bool hasAttribute(const QString&) const;

    Q_INVOKABLE QString innerText();
    Q_INVOKABLE QString outerHtml() const;
    Q_INVOKABLE QJsonObject outerJson() const;
    Q_INVOKABLE QString getAttribute(const QString&) const;

    Q_INVOKABLE QList<QObject*> allAttributes();

    Q_INVOKABLE explicit operator bool() const;
};

Q_DECLARE_METATYPE(DOMNode)

#endif // DOMNODE_H
