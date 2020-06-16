#include <QtTest>
#include <QCoreApplication>

#include "payloads/hello.h"

class HelloTest : public QObject
{
    Q_OBJECT

public:
    HelloTest();
    ~HelloTest();

private slots:
    void test_case2();

};

HelloTest::HelloTest()
{

}

HelloTest::~HelloTest()
{

}

void HelloTest::test_case2()
{
    Hello hello;
    hello.heartbeatInterval = 200;
    QVERIFY(hello.heartbeatInterval == 200);
}

QTEST_MAIN(HelloTest)

#include "tst_hello.moc"
