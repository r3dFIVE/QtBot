/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "tst_hello.h"

const QString HEARTBEAT_INTERVAL = "heartbeat_interval";

void
HelloTest::test_deserialization()
{
    Hello hello(PLD_HELLO);

    QVERIFY(hello.getHeartbeatInterval() == TEST_INT1);
    QVERIFY(hello.getHeartbeatInterval() != TEST_INT2);
}

void
HelloTest::test_serialization()
{
    Hello hello;

    hello.setHeartbeatInterval(TEST_INT2);

    QJsonObject serialized = hello.toQJsonObject();

    QVERIFY(serialized[Hello::HEARTBEAT_INTERVAL] != TEST_INT1);
    QVERIFY(serialized[Hello::HEARTBEAT_INTERVAL] == TEST_INT2);
}

static HelloTest HELLO_TEST;
