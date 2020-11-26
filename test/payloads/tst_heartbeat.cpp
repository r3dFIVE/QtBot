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

#include "tst_heartbeat.h"

void
HeartbeatTest::test_serialization() {
    Heartbeat heartbeat;

    heartbeat.setOp(GatewayEvent::HEARTBEAT);

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
    QVERIFY(heartbeat.getOp() == GatewayEvent::HEARTBEAT);
    QVERIFY(heartbeat.getOp() != GatewayEvent::HEARTBEAT_ACK);
}

static HeartbeatTest HEARTBEAT_TEST;
