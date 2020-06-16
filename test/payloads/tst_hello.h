#include <QtTest>
#include <QCoreApplication>

#include "payloads/hello.h"
#include "testpayloads.h"
#include "testsuite.h"

class HelloTest : public TestSuite
{
    Q_OBJECT

public:
    HelloTest() {}
    ~HelloTest() {}

private slots:
    void test_serialization();
    void test_deserialization();
};

