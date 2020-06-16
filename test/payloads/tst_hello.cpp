#include "tst_hello.h"

void
HelloTest::test_deserialization()
{
    Hello hello;
    hello.fromQString(PLD_HELLO);
    QVERIFY(hello.heartbeatInterval == TEST_INT1);
    QVERIFY(hello.heartbeatInterval != TEST_INT2);
}

void
HelloTest::test_serialization()
{

    Hello hello;
    hello.heartbeatInterval = TEST_INT1;

    QJsonObject serialized = hello.toQJsonObject();
    QVERIFY(serialized[hello.HEARTBEAT_INTERVAL] == TEST_INT1);
}

static HelloTest HELLO_TEST;
