#include "tst_heartbeat.h"

void
HeartbeatTest::test_serialization() {
    Heartbeat heartbeat;
    heartbeat.op = GatewayOpcodes::HEARTBEAT;
    heartbeat.d = 42;

    QString serialized = heartbeat.toQString();
    QVERIFY(serialized == PLD_HEARTBEAT);
    QVERIFY(serialized != QString(PLD_HEARTBEAT).replace("42", "24"));
}

void
HeartbeatTest::test_deserialization() {
    Heartbeat heartbeat;
    heartbeat.fromQString(PLD_HEARTBEAT);

    QVERIFY(heartbeat.d == 42);
    QVERIFY(heartbeat.d != 24);
    QVERIFY(heartbeat.op == GatewayOpcodes::HEARTBEAT);
    QVERIFY(heartbeat.op != GatewayOpcodes::HEARTBEAT_ACK);
}

static HeartbeatTest HEARTBEAT_TEST;
