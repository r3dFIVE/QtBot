#include "tst_gatewaypayload.h"

#include "testpayloads.h"
#include "payloads/gatewaypayload.h"
#include "payloads/hello.h"


void
GatewayPayloadTest::test_serialization_minimal() {
    Hello hello;

    hello.setHeartbeatInterval(TEST_INT1);

    QJsonObject serializedHello = hello.toQJsonObject();

    GatewayPayload gatewayPayload;

    gatewayPayload.setOp(GatewayEvents::HELLO);

    gatewayPayload.setD(serializedHello);

    QJsonObject serializedPayload = gatewayPayload.toQJsonObject();

    QJsonObject d = serializedPayload[GatewayPayload::D].toObject();

    QVERIFY(d.contains(Hello::HEARTBEAT_INTERVAL));
    QVERIFY(d[Hello::HEARTBEAT_INTERVAL] == TEST_INT1);
    QVERIFY(serializedPayload[GatewayPayload::OP] == GatewayEvents::HELLO);
    QVERIFY(serializedPayload[GatewayPayload::OP] != GatewayEvents::HEARTBEAT_ACK);
}

void
GatewayPayloadTest::test_deserialization_minimal() {
    GatewayPayload payload(PLD_GATEWAYPAYLOAD_MINIMAL);
;
    QVERIFY(payload.getOp() == GatewayEvents::HELLO);
    QVERIFY(payload.getOp() != GatewayEvents::DISPATCH);

    Hello hello(payload.getD());

    QVERIFY(hello.getHeartbeatInterval() == TEST_INT1);
    QVERIFY(hello.getHeartbeatInterval() != TEST_INT2);
}


void
GatewayPayloadTest::test_single_value() {
    GatewayPayload payload(PLD_INVALID_SESSION);

    QVERIFY(payload.getOp() == GatewayEvents::INVALID_SESSION);
    QVERIFY(payload.getV().toBool());
}

static GatewayPayloadTest GATEWAYPAYLOAD_TEST;
