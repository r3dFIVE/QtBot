#include "tst_activitytimestamps.h"
#include "testpayloads.h"

#include <payloads/activitytimestamps.h>

void
ActivityTimestampsTest::test_serialization_minimal() {
    ActivityTimestamps timestamps;

    QJsonObject serializedTimestamps = timestamps.toQJsonObject();

    QVERIFY(!serializedTimestamps.contains(timestamps.START));
    QVERIFY(!serializedTimestamps.contains(timestamps.END));
}

void
ActivityTimestampsTest::test_serialization_full() {
    ActivityTimestamps timestamps;
    timestamps.start = QSharedPointer<int>(new int(TEST_INT1));
    timestamps.end = QSharedPointer<int>(new int(TEST_INT2));
    QJsonObject serializedTimestamps = timestamps.toQJsonObject();

    QVERIFY(serializedTimestamps.contains(timestamps.START));
    QVERIFY(serializedTimestamps[timestamps.START] == TEST_INT1);
    QVERIFY(serializedTimestamps[timestamps.START] != TEST_INT2);

    QVERIFY(serializedTimestamps.contains(timestamps.END));
    QVERIFY(serializedTimestamps[timestamps.END] != TEST_INT1);
    QVERIFY(serializedTimestamps[timestamps.END] == TEST_INT2);
}

void
ActivityTimestampsTest::test_deserialization_minimal() {
    ActivityTimestamps timestamps;
    timestamps.fromQString(PLD_TIMESTAMPS_MINIMAL);

    QVERIFY(timestamps.start == nullptr);
    QVERIFY(timestamps.end == nullptr);
}

void
ActivityTimestampsTest::test_deserialization_full() {
    ActivityTimestamps timestamps;
    timestamps.fromQString(PLD_TIMESTAMPS_FULL);

    QVERIFY(timestamps.start != nullptr);
    QVERIFY(*timestamps.start == TEST_INT1);
    QVERIFY(*timestamps.start != TEST_INT2);

    QVERIFY(timestamps.end != nullptr);
    QVERIFY(*timestamps.end != TEST_INT1);
    QVERIFY(*timestamps.end == TEST_INT2);
}

static ActivityTimestampsTest ACTIVITY_TIMESTAMPS_TEST;
