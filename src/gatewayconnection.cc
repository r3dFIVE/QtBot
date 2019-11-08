#include "gatewayconnection.h"
#include <stack>
#include <regex>
#include <memory>
#include <QStack>

const QString kOpcodeKey = "\"op\"";
const QString kPayloadKey = "\"d\"";
const QString kSequenceNumKey = "\"s\"";
const QString kEventKey = "\"t\"";
const int kNoResultsFound = -1;

GatewayConnection::GatewayConnection(const QUrl& url, bool debug, QObject *parent) :
    QObject(parent),
    url_(url),
    debug_(debug)
{
    if (debug_)
        qDebug() << "Gateway Connection Url: " << url;
    connect(&socket_, &QWebSocket::connected, this, &GatewayConnection::onConnected);
    connect(&socket_, &QWebSocket::textMessageReceived, this, &GatewayConnection::onMessageReceived);
    connect(&socket_, &QWebSocket::disconnected, this, &GatewayConnection::reconnect);
    socket_.open(QUrl(url));
}

void
GatewayConnection::onConnected() {

    //do nothing, wait for OPCODE 10 for now and dispatch accordingly
}

void
GatewayConnection::reconnect() {
    //TODO implement reco
}

void
GatewayConnection::onMessageReceived(QString message) {
    GatewayPayload payload = GatewayConnection::BuildPayload(message);
    if (!ValidatePayload(payload)) {
        if (debug_)
            qDebug() << "Error validating paylad: " << payload.to_string();
        return;
    }
    emit payloadReady(payload);
}

bool
GatewayConnection::ValidatePayload(GatewayPayload payload) {
    if (payload.opcode == kNoResultsFound) {
        return false;
    }
    if (payload.opcode == 0) {
        if (payload.seq_num == kNoResultsFound
                || payload.event_name == QString::number(kNoResultsFound)) {
            return false;
        }
    }
    if (payload.json_payload == QString::number(kNoResultsFound)) {
        return false;
    }

    return true;
}

GatewayPayload
GatewayConnection::BuildPayload(QString message) {
    GatewayPayload payload;
    payload.opcode = GatewayConnection::ParseInt(message, kOpcodeKey);
    payload.json_payload = GatewayConnection::ParseEventPayload(message);
    if (payload.opcode == 0) {
        payload.seq_num = GatewayConnection::ParseInt(message, kSequenceNumKey);
        payload.event_name = GatewayConnection::ParseEventName(message);
    }
    return payload;
}

QString
GatewayConnection::ParseEventName(QString socket_payload) {
    int begin = socket_payload.indexOf(":", socket_payload.indexOf(kEventKey) + kEventKey.size()) + 1;

    if (begin == kNoResultsFound) {
        //TODO add logging?
        return QString::number(kNoResultsFound);
    }

    int end = socket_payload.indexOf('}', begin) - 1;

    if (end == kNoResultsFound) {
        //TODO add logging?
        return QString::number(kNoResultsFound);
    }

    return socket_payload.mid(begin, end - begin)
            .replace(QRegExp("\\s+"), "")
            .replace(QRegExp("\"+"), "");
}

int
GatewayConnection::ParseInt(QString socket_payload, QString key) {
    int begin = socket_payload.indexOf(":", socket_payload.indexOf(key) + key.size()) + 1;
    if (begin == kNoResultsFound) {
        //TODO add logging?
        return kNoResultsFound;
    }

    int end = socket_payload.indexOf(',', begin);

    if (end == kNoResultsFound) {
        //TODO add logging?
        return kNoResultsFound;
    }
    return socket_payload.mid(begin, end - begin).toInt();
}

QString
GatewayConnection::ParseEventPayload(QString socket_payload) {
    int begin = socket_payload.indexOf(kPayloadKey);

    if (begin == kNoResultsFound) {
        //TODO add loggin?
        return QString::number(kNoResultsFound);
    }

    int end = kNoResultsFound;
    QStack<char> braces;

    for (int i = begin; i < socket_payload.size(); ++i) {
        if (socket_payload[i] == '{') {
            if (braces.size() == 0) {
                begin = i;
            }
            braces.push('{');
        } else if (socket_payload[i] == '}') {
            braces.pop();
            if (braces.size() == 0) {
                end = i;
                break;
            }
        }
    }

    if (!braces.empty()
            || begin >= socket_payload.size()
            || end == kNoResultsFound ) {
        return QString::number(kNoResultsFound);;
    }

    return socket_payload.mid(begin, (end - begin) + 1);
}
