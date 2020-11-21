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

#include "tst_activitysecrets.h"
#include "testpayloads.h"

#include <payloads/activitysecrets.h>

void
ActivitySecretsTest::test_serialization_minimal() {
    ActivitySecrets secrets;

    QJsonObject serializedSecrets = secrets.toQJsonObject();

    QVERIFY(!serializedSecrets.contains(secrets.JOIN));
    QVERIFY(!serializedSecrets.contains(secrets.SPECTATE));
    QVERIFY(!serializedSecrets.contains(secrets.MATCH));
}

void
ActivitySecretsTest::test_serialization_full() {
    ActivitySecrets secrets;

    secrets.setJoin(TEST_STRING1);

    secrets.setSpectate(TEST_STRING2);

    secrets.setMatch(TEST_STRING1);

    QJsonObject serializedSecrets = secrets.toQJsonObject();

    QVERIFY(serializedSecrets[secrets.JOIN] == TEST_STRING1);
    QVERIFY(serializedSecrets[secrets.JOIN] != TEST_STRING2);
    QVERIFY(serializedSecrets[secrets.SPECTATE] != TEST_STRING1);
    QVERIFY(serializedSecrets[secrets.SPECTATE] == TEST_STRING2);
    QVERIFY(serializedSecrets[secrets.MATCH] == TEST_STRING1);
    QVERIFY(serializedSecrets[secrets.MATCH] != TEST_STRING2);
}

void
ActivitySecretsTest::test_deserialization_minimal() {
    ActivitySecrets secrets(PLD_ACTIVITY_SECRETS_MINIMAL);

    QVERIFY(secrets.getJoin() == "");
    QVERIFY(secrets.getJoin() != TEST_STRING1);
    QVERIFY(secrets.getSpectate() == "");
    QVERIFY(secrets.getSpectate() != TEST_STRING1);
    QVERIFY(secrets.getMatch() == "");
    QVERIFY(secrets.getMatch() != TEST_STRING1);
}

void
ActivitySecretsTest::test_deserialization_full() {
    ActivitySecrets secrets(PLD_ACTIVITY_SECRETS_FULL);

    QVERIFY(secrets.getJoin() != "");
    QVERIFY(secrets.getJoin() == TEST_STRING1);
    QVERIFY(secrets.getSpectate() != "");
    QVERIFY(secrets.getSpectate() == TEST_STRING2);
    QVERIFY(secrets.getMatch() != "");
    QVERIFY(secrets.getMatch() == TEST_STRING1);
}

static ActivitySecretsTest SECRETS_TEST;
