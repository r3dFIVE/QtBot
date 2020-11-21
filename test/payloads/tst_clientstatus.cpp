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

#include "tst_clientstatus.h"

#include <payloads/clientstatus.h>

void ClientStatusTest::test_deserialization() {
    ClientStatus clientStatus;
    qDebug() << PLD_CLIENT_STATUS;
    clientStatus.fromQString(PLD_CLIENT_STATUS);

    QVERIFY(clientStatus.getDesktop() == TEST_STRING1);
    QVERIFY(clientStatus.getMobile() == TEST_STRING2);
    QVERIFY(clientStatus.getWeb() == TEST_STRING1);
}

void ClientStatusTest::test_serialization() {
    ClientStatus clientStatus;
    clientStatus.setDesktop(TEST_STRING1);
    clientStatus.setMobile(TEST_STRING2);
    clientStatus.setWeb(TEST_STRING1);

    QJsonObject serializedClientStatus = clientStatus.toQJsonObject();

    QVERIFY(serializedClientStatus[clientStatus.DESKTOP] == TEST_STRING1);
    QVERIFY(serializedClientStatus[clientStatus.MOBILE] == TEST_STRING2);
    QVERIFY(serializedClientStatus[clientStatus.WEB] == TEST_STRING1);
}

static ClientStatusTest CLIENT_STATUS_TEST;
