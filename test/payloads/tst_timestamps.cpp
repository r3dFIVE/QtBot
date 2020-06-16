#include "tst_timestamps.h"
#include "testpayloads.h"

#include <payloads/timestamps.h>

void
TimestampsTest::test_serialization_minimal() {
    Timestamps timestamps;

    QJsonObject serializedTimestamps = timestamps.toQJsonObject();

    QVERIFY(!serializedTimestamps.contains(timestamps.START));
    QVERIFY(!serializedTimestamps.contains(timestamps.END));
}

void
TimestampsTest::test_serialization_full() {
    Timestamps timestamps;
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
TimestampsTest::test_deserialization_minimal() {
    Timestamps timestamps;
    timestamps.fromQString(PLD_TIMESTAMPS_MINIMAL);

    QVERIFY(timestamps.start == nullptr);
    QVERIFY(timestamps.end == nullptr);
}

void
TimestampsTest::test_deserialization_full() {
    Timestamps timestamps;
    timestamps.fromQString(PLD_TIMESTAMPS_FULL);

    QVERIFY(timestamps.start != nullptr);
    QVERIFY(*timestamps.start == TEST_INT1);
    QVERIFY(*timestamps.start != TEST_INT2);

    QVERIFY(timestamps.end != nullptr);
    QVERIFY(*timestamps.end != TEST_INT1);
    QVERIFY(*timestamps.end == TEST_INT2);
}

static TimestampsTest TIMESTAMPS_TEST;
