#ifndef ACTIVITYTEST_H
#define ACTIVITYTEST_H

#include <QObject>
#include <testsuite.h>

class ActivityTest : public TestSuite
{
    Q_OBJECT
public:
    ActivityTest() {}
    ~ActivityTest() {}

private slots:
    void test_serialization_minimal();
    void test_serialization_full();
    void test_deserialization_minimal();
    void test_deserialization_full();
};

#endif // ACTIVITYTEST_H
