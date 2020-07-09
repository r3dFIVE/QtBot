#ifndef EVENTCONTEXT_H
#define EVENTCONTEXT_H

#include <QObject>

#include <payloads/jsonserializable.h>

class EventContext : public JsonSerializable
{
    Q_OBJECT
public:


    void write(QJsonObject &jsonObject) override {}
    void read(const QJsonObject &jsonObject) override {}
signals:

};

Q_DECLARE_METATYPE(EventContext)

#endif // EVENTCONTEXT_H
