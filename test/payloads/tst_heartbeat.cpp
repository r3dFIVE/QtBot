#include "tst_heartbeat.h"

void
HeartbeatTest::test_serialization() {
    Heartbeat heartbeat;

    heartbeat.setOp(GatewayEvents::HEARTBEAT);

    heartbeat.setD(42);

    QString serialized = heartbeat.toQString();

    QVERIFY(serialized == PLD_HEARTBEAT);
    QVERIFY(serialized != QString(PLD_HEARTBEAT).replace("42", "24"));
}

void
HeartbeatTest::test_deserialization() {
    Heartbeat heartbeat(PLD_HEARTBEAT);

    QVERIFY(heartbeat.getD() == 42);
    QVERIFY(heartbeat.getD() != 24);
    QVERIFY(heartbeat.getOp() == GatewayEvents::HEARTBEAT);
    QVERIFY(heartbeat.getOp() != GatewayEvents::HEARTBEAT_ACK);
}

static HeartbeatTest HEARTBEAT_TEST;
