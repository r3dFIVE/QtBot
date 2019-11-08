#ifndef GATEWAYPAYLOAD_H
#define GATEWAYPAYLOAD_H

#include <QString>

class GatewayPayload  {
    QString _json_payload;
    QString _event_name;
    int opcode;
    int seq_num;


};

#endif // GATEWAYPAYLOAD_H
