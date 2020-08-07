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
