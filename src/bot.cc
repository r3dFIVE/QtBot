#include "bot.h"


Bot::Bot()
{

}

void
Bot::Run() {
    GatewayConnection connection(QUrl(""), nullptr);
    QString socket_payload("{ \"op\" : 42, \"d\" : { \"test1\" : \"sometest\", \"test2\" : { \"test3\" : 12345676 } }, \"s\" : 24, \"t\" : \"TEST\" }");
    //auto payload = connection.BuildPayload(socket_payload);
    //qDebug(qUtf8Printable(payload.to_string()));
}
