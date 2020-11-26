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

#include "tst_updatestatus.h"

#include "payloads/activity.h"
#include "payloads/updatestatus.h"


void
UpdateStatusTest::test_deserialization() {
    UpdateStatus updateStatus(PLD_UPDATE_STATUS);

    QVERIFY(updateStatus.getSince() == TEST_INT1);

    Activity game(updateStatus.getGame());

    QVERIFY(game.getName() == TEST_STRING1);
    QVERIFY(updateStatus.getStatus() == TEST_STRING1);
    QVERIFY(updateStatus.getAfk() == true);
}


void
UpdateStatusTest::test_serialization() {
    UpdateStatus updateStatus;

    updateStatus.setSince(TEST_INT1);

    Activity game(PLD_ACTIVITY_MINIMAL);

    updateStatus.setGame(game.toQJsonObject());

    updateStatus.setStatus(TEST_STRING1);

    updateStatus.setAfk(true);

    QJsonObject serializedUpdateStatus = updateStatus.toQJsonObject();

    QVERIFY(serializedUpdateStatus[UpdateStatus::SINCE] == TEST_INT1);

    Activity serializedGame(serializedUpdateStatus[updateStatus.GAME].toObject());

    QVERIFY(serializedGame.getName() == TEST_STRING1);
    QVERIFY(serializedUpdateStatus[UpdateStatus::STATUS] == TEST_STRING1);
    QVERIFY(serializedUpdateStatus[UpdateStatus::AFK] == true);
}

static UpdateStatusTest UPDATE_STATUS_TEST;
