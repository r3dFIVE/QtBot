#ifndef TIMESTAMPSTEST_H
#define TIMESTAMPSTEST_H

#include "testsuite.h"

#include <QObject>

class ActivityTimestampsTest : public TestSuite
{
    Q_OBJECT
public:
    ActivityTimestampsTest() {}
    ~ActivityTimestampsTest() {}

private slots:
    void test_serialization_minimal();
    void test_serialization_full();
    void test_deserialization_minimal();
    void test_deserialization_full();
};

#endif // TIMESTAMPSTEST_H
