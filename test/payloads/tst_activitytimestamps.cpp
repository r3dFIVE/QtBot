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

#include "tst_activitytimestamps.h"
#include "testpayloads.h"

#include <payloads/activitytimestamps.h>

void
ActivityTimestampsTest::test_serialization_minimal() {
    ActivityTimestamps timestamps;

    QJsonObject serializedTimestamps = timestamps.toQJsonObject();

    QVERIFY(!serializedTimestamps.contains(ActivityTimestamps::START));
    QVERIFY(!serializedTimestamps.contains(ActivityTimestamps::END));
}

void
ActivityTimestampsTest::test_serialization_full() {
    ActivityTimestamps timestamps;

    timestamps.setStart(TEST_INT1);

    timestamps.setEnd(TEST_INT2);

    QJsonObject serializedTimestamps = timestamps.toQJsonObject();

    QVERIFY(serializedTimestamps.contains(ActivityTimestamps::START));
    QVERIFY(serializedTimestamps[ActivityTimestamps::START] == TEST_INT1);
    QVERIFY(serializedTimestamps[ActivityTimestamps::START] != TEST_INT2);
    QVERIFY(serializedTimestamps.contains(ActivityTimestamps::END));
    QVERIFY(serializedTimestamps[ActivityTimestamps::END] != TEST_INT1);
    QVERIFY(serializedTimestamps[ActivityTimestamps::END] == TEST_INT2);
}

void
ActivityTimestampsTest::test_deserialization_minimal() {
    ActivityTimestamps timestamps(PLD_ACTIVITY_TIMESTAMPS_MINIMAL);

    QVERIFY(timestamps.getStart().isUndefined());
    QVERIFY(timestamps.getEnd().isUndefined());
}

void
ActivityTimestampsTest::test_deserialization_full() {
    ActivityTimestamps timestamps(PLD_ACTIVITY_TIMESTAMPS_FULL);

    QVERIFY(timestamps.getStart() == TEST_INT1);
    QVERIFY(timestamps.getStart() != TEST_INT2);
    QVERIFY(timestamps.getEnd() != TEST_INT1);
    QVERIFY(timestamps.getEnd() == TEST_INT2);
}

static ActivityTimestampsTest ACTIVITY_TIMESTAMPS_TEST;
