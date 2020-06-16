#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QMetaEnum>
#include <QObject>
#include "bot.h"
#include "globals.h"
#include "payloads/identify.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "C:\\workspace\\QtBot\\bot\\settings.ini";

    if(!(QFileInfo::exists(path))) {
        qDebug().noquote() << QString("Settings file %1 does not exist. . . exiting.\n").arg(path);
        exit(1);
    }    

    QString str = "{\"op\":2,\"d\":{\"token\":\"my_token\",\"properties\":{\"$os\":\"linux\",\"$browser\":\"disco\",\"$device\":\"disco\"},\"compress\":true,\"large_threshold\":250,\"guild_subscriptions\":false,\"shard\":[0,1],\"presence\":{\"game\":{\"name\":\"CardsAgainstHumanity\",\"type\":3},\"status\":\"dnd\",\"since\":91879201,\"afk\":false},\"intents\":7}}";
    GatewayPayload pld;
    pld.fromQString(str);
    Identify identify;
    identify.fromQJsonObject(pld.d);
    QString str2(identify.toQString());
    qDebug() << str2;

    QSharedPointer<Settings> settings = QSharedPointer<Settings>(new Settings(path));

    Bot bot;
    bot.run(settings);

    return a.exec();
}


