/**
 *
 *
 * Original credit to https://github.com/lagner/QGumboParser
 *
 * DOMParsing code borrows _heavily_ from here!
 */


#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <QNetworkReply>
#include <QObject>

#include "gumbo.h"
#include "logging/logfactory.h"

class QString;
class DOMNode;

class DOMParser : public QObject
{
    Q_OBJECT

    DOMParser& operator=(const DOMParser&) = delete;

    Logger *_logger = LogFactory::getLogger();
    GumboOutput *_gumboOutput = nullptr;
    const GumboOptions *_options = nullptr;
    QByteArray _sourceData;

public:
    DOMParser(QObject *parent = nullptr) : QObject(parent) {}
    DOMParser(const DOMParser &other, QObject* parent = nullptr);
    DOMParser(DOMParser&&, QObject *parent);
    ~DOMParser();

    Q_INVOKABLE bool parseFromUrl(const QString& url);
    Q_INVOKABLE bool parseFromString(QByteArray utf8data);
    Q_INVOKABLE DOMNode* rootNode();
};

Q_DECLARE_METATYPE(DOMParser)

#endif // DOMPARSER_H
