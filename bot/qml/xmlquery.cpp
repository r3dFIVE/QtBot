#include "xmlquery.h"

#include "util/serializationutils.h"
#include "xml2json.hpp"

bool
XMLQuery::setFocusString(const QString &focus) {
    return _query.setFocus(focus);
}

bool
XMLQuery::setFocusUrl(const QString &focus) {
    return _query.setFocus(QUrl(focus));
}

bool
XMLQuery::setFocusFile(File *focus) {
    return _query.setFocus(focus->get());
}

void
XMLQuery::setQuery(const QString &query) {
    _query.setQuery(query);
}

QString
XMLQuery::getXMLString(const int spacing) {

    if (!_query.isValid()) {
        _logger->debug(QString("DOMParser.getXMLString() failed. Query is not valid."));

        return QString();
    }

    QString result;

    _query.evaluateTo(&result);

    QDomDocument doc;

    doc.setContent(result);

    return doc.toString(spacing);
}

QJsonObject
XMLQuery::getJSON(const int spacing) {

    if (!_query.isValid()) {
        _logger->debug(QString("DOMParser.getJSON() failed. Query is not valid."));

        return QJsonObject();
    }

    QString result;

    _query.evaluateTo(&result);

    QDomDocument doc;

    doc.setContent(result);

    std::string xml_str = doc.toString(spacing).toStdString();

    std::string json_str = xml2json(xml_str.c_str());

    return SerializationUtils::toQJsonObject(QString::fromStdString(json_str));
}

