#include "tst_gatewaypayload.h"
#include "testpayloads.h"

#include <payloads/gatewaypayload.h>
#include <payloads/hello.h>


void
GatewayPayloadTest::test_serialization_minimal() {
    Hello hello;
    hello.setHeartbeatInterval(TEST_INT1);
    QJsonObject serializedHello = hello.toQJsonObject();

    GatewayPayload::GatewayPayload gatewayPayload;
    gatewayPayload.op = GatewayOpcodes::HELLO;
    gatewayPayload.d = serializedHello;

    QJsonObject serializedPayload = gatewayPayload.toQJsonObject();

    QJsonObject d = serializedPayload[GatewayPayload::D].toObject();
    QVERIFY(d.contains(hello.HEARTBEAT_INTERVAL));
    QVERIFY(d[hello.HEARTBEAT_INTERVAL] == TEST_INT1);

    QVERIFY(serializedPayload[GatewayPayload::OP] == GatewayOpcodes::HELLO);
    QVERIFY(serializedPayload[GatewayPayload::OP] != GatewayOpcodes::HEARTBEAT_ACK);
}

void
GatewayPayloadTest::test_serialization_full() {
    //TODO when displatch payload is created
}

void
GatewayPayloadTest::test_deserialization_minimal() {
    GatewayPayload::GatewayPayload payload;
    payload.fromQString(PLD_GATEWAYPAYLOAD_MINIMAL);

    QVERIFY(payload.op == GatewayOpcodes::HELLO);
    QVERIFY(payload.op != GatewayOpcodes::DISPATCH);

    Hello hello;
    hello.fromQJsonObject(payload.d);

    QVERIFY(*hello.heartbeat_interval == TEST_INT1);
    QVERIFY(*hello.heartbeat_interval != TEST_INT2);
}

void
GatewayPayloadTest::test_deserialization_full() {
    //TODO when displatch payload is created
}

void
GatewayPayloadTest::test_single_value() {
    GatewayPayload::GatewayPayload payload;
    payload.fromQString(PLD_INVALID_SESSION);

    QVERIFY(payload.op == GatewayOpcodes::INVALID_SESSION);
    QVERIFY(payload.d[GatewayPayload::VALUE].toBool());
}

static GatewayPayloadTest GATEWAYPAYLOAD_TEST;
