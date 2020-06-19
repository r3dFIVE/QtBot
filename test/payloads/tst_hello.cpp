#include "tst_hello.h"

const QString HEARTBEAT_INTERVAL = "heartbeat_interval";

void
HelloTest::test_deserialization()
{
    Hello hello;
    hello.fromQString(PLD_HELLO);
    QVERIFY(*hello.heartbeat_interval == TEST_INT1);
    QVERIFY(*hello.heartbeat_interval != TEST_INT2);
}

void
HelloTest::test_serialization()
{
    Hello hello;
    hello.setHeartbeatInterval(TEST_INT2);

    QJsonObject serialized = hello.toQJsonObject();

    QVERIFY(serialized[hello.HEARTBEAT_INTERVAL] != TEST_INT1);
    QVERIFY(serialized[hello.HEARTBEAT_INTERVAL] == TEST_INT2);
}

static HelloTest HELLO_TEST;
