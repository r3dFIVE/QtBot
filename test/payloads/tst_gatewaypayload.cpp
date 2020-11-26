/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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

    gatewayPayload.setOp(GatewayEvent::HELLO);

    gatewayPayload.setD(serializedHello);

    QJsonObject serializedPayload = gatewayPayload.toQJsonObject();

    QJsonObject d = serializedPayload[GatewayPayload::D].toObject();

    QVERIFY(d.contains(Hello::HEARTBEAT_INTERVAL));
    QVERIFY(d[Hello::HEARTBEAT_INTERVAL] == TEST_INT1);
    QVERIFY(serializedPayload[GatewayPayload::OP] == GatewayEvent::HELLO);
    QVERIFY(serializedPayload[GatewayPayload::OP] != GatewayEvent::HEARTBEAT_ACK);
}

void
GatewayPayloadTest::test_deserialization_minimal() {
    GatewayPayload payload(PLD_GATEWAYPAYLOAD_MINIMAL);
;
    QVERIFY(payload.getOp() == GatewayEvent::HELLO);
    QVERIFY(payload.getOp() != GatewayEvent::DISPATCH);

    Hello hello(payload.getD());

    QVERIFY(hello.getHeartbeatInterval() == TEST_INT1);
    QVERIFY(hello.getHeartbeatInterval() != TEST_INT2);
}


void
GatewayPayloadTest::test_single_value() {
    GatewayPayload payload(PLD_INVALID_SESSION);

    QVERIFY(payload.getOp() == GatewayEvent::INVALID_SESSION);
    QVERIFY(payload.getV().toBool());
}

static GatewayPayloadTest GATEWAYPAYLOAD_TEST;
