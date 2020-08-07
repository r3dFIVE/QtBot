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
