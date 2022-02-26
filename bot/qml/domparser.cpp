/**
 *
 *
 * Original credit to https://github.com/lagner/QGumboParser
 *
 * DOMParsing code borrows _heavily_ from here!
 */

#include "domparser.h"
#include "file.h"

#include <QNetworkAccessManager>
#include <stdexcept>

#include "domnode.h"
#include "util/httputils.h"


bool
DOMParser::parseFromUrl(const QString &url) {
    QNetworkAccessManager manager;

    QSharedPointer<QNetworkReply> reply = QSharedPointer<QNetworkReply>(manager.get(QNetworkRequest(QUrl(url))));

    HttpUtils::waitForReply(reply, true);

    if (reply->error()) {
        _logger->debug(reply->errorString());

        return false;
    }

    QByteArray array = reply->readAll();

    return parseFromString(array);
}

bool
DOMParser::parseFromString(QByteArray arr) {
    _options = &kGumboDefaultOptions;

    _sourceData = arr;

    _gumboOutput = gumbo_parse_with_options(_options,
                                            _sourceData.constData(),
                                            _sourceData.length());
    if (!_gumboOutput) {
        _logger->debug("Gumbo-Parser could not parse input string");

        return false;
    }

    return true;
}

DOMParser::DOMParser(const DOMParser &other, QObject *parent) : QObject(parent) {
    if (this == &other) {
        return;
    }

    _options = other._options;

    _sourceData = other._sourceData;

    _gumboOutput = other._gumboOutput;
}

DOMParser::~DOMParser() {
    if (_gumboOutput) {
        gumbo_destroy_output(_options, _gumboOutput);
    }

    if (_options != &kGumboDefaultOptions) {
        delete _options;
    }

    QString ptrStr = QString("0x%1").arg((quintptr)this,
                        QT_POINTER_SIZE * 2, 16, QChar('0'));

    _logger->trace(QString("Destroyed DOMParser(%1)").arg(ptrStr));
}

DOMParser::DOMParser(DOMParser &&source, QObject *parent) :
    QObject(parent),
    _gumboOutput(source._gumboOutput),
    _options(source._options),
    _sourceData(source._sourceData)
{
    source._gumboOutput = nullptr;
    source._options = nullptr;
}

DOMNode*
DOMParser::rootNode() {
    return new DOMNode(_gumboOutput->root, this);
}
