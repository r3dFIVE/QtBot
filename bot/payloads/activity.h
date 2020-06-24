#ifndef ACTIVITY_H
#define ACTIVITY_H

class ActivityEmoji;
class ActivityTimestamps;

#include "jsonserializable.h"
#include "activityparty.h"
#include "activityassets.h"
#include "activitysecrets.h"
#include "activityemoji.h"
#include "activitytimestamps.h"

#include <QSharedPointer>

class Activity : public JsonSerializable
{
    Q_OBJECT

public:
    const QString NAME = "name";
    const QString TYPE = "type";
    const QString URL = "url";
    const QString CREATED_AT = "created_at";
    const QString TIMESTAMPS = "timestamps";
    const QString APPLICATION_ID = "application_id";
    const QString DETAILS = "details";
    const QString STATE = "state";
    const QString EMOJI = "emoji";
    const QString PARTY = "party";
    const QString ASSETS = "assets";
    const QString SECRETS = "secrets";
    const QString INSTANCE = "instance";
    const QString FLAGS = "flags";

    Q_PROPERTY(QString name READ getName WRITE setName)
    QString name;

    Q_PROPERTY(int type READ getType WRITE setType)
    int type;

    Q_PROPERTY(QString url READ getUrl WRITE setUrl)
    QString url;

    Q_PROPERTY(int created_at READ getCreatedAt WRITE setCreatedAt)
    int created_at;

    Q_PROPERTY(QJsonObject timestamps  READ getTimestamps WRITE setTimestamps)
    QSharedPointer<ActivityTimestamps> timestamps;

    Q_PROPERTY(QString application_id READ getApplicationId WRITE setApplicationId)
    QString application_id;

    Q_PROPERTY(QString details READ getDetails WRITE setDetails)
    QString details;

    Q_PROPERTY(QString state READ getState WRITE setState)
    QString state;

    Q_PROPERTY(QJsonObject emoji READ getEmoji WRITE setEmoji)
    QSharedPointer<ActivityEmoji> emoji;

    Q_PROPERTY(QJsonObject party READ getParty WRITE setParty)
    QSharedPointer<ActivityParty> party;

    Q_PROPERTY(QJsonObject assets READ getAssets WRITE setAssets)
    QSharedPointer<ActivityAssets> assets;

    Q_PROPERTY(QJsonObject secrets READ getSecrets WRITE setSecrets)
    QSharedPointer<ActivitySecrets> secrets;

    Q_PROPERTY(QJsonValue instance READ getInstance WRITE setInstance)
    QSharedPointer<bool> instance;

    Q_PROPERTY(QJsonValue flags READ getFlags WRITE setFlags)
    QSharedPointer<int> flags;

    QString getName();
    void setName(QString name);
    int getType();
    void setType(int type);
    QString getUrl();
    void setUrl(QString url);
    int getCreatedAt();
    void setCreatedAt(int created_at);
    QJsonObject getTimestamps();
    void setTimestamps(QJsonObject timestamps);
    QString getApplicationId();
    void setApplicationId(QString application_id);
    QString getDetails();
    void setDetails(QString details);
    QString getState();
    void setState(QString state);
    QJsonObject getEmoji();
    void setEmoji(QJsonObject emoji);
    QJsonObject getParty();
    void setParty(QJsonObject party);
    QJsonObject getAssets();
    void setAssets(QJsonObject assets);
    QJsonObject getSecrets();
    void setSecrets(QJsonObject secrets);
    QJsonValue getInstance();
    void setInstance(QJsonValue instance);
    QJsonValue getFlags();
    void setFlags(QJsonValue flags);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    enum ActivityType {
        Game = 0,
        Streaming = 1,
        Listening = 2,
        Custom = 4
    };

    Q_ENUM(ActivityType)
};

Q_DECLARE_METATYPE(Activity)

#endif // ACTIVITY_H
