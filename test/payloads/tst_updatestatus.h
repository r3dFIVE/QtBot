#ifndef UPDATESTATUSTEST_H
#define UPDATESTATUSTEST_H

#include <QObject>
#include <testsuite.h>

class UpdateStatusTest : public TestSuite
{
    Q_OBJECT
public:
    UpdateStatusTest() {}
    ~UpdateStatusTest() {}

private slots:
    void test_deserialization();
    void test_serialization();
};

#endif // UPDATESTATUSTEST_H
