#ifndef CLIENTSTATUSTEST_H
#define CLIENTSTATUSTEST_H

#include <QObject>
#include <testsuite.h>

class ClientStatusTest : public TestSuite
{
    Q_OBJECT

public:
    ClientStatusTest() {}
    ~ClientStatusTest() {}

private slots:
    void test_deserialization();
    void test_serialization();
};

#endif // CLIENTSTATUSTEST_H
