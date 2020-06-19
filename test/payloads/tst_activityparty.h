#ifndef PARTYTEST_H
#define PARTYTEST_H

#include <QObject>
#include <testsuite.h>

class ActivityPartyTest : public TestSuite
{
    Q_OBJECT

public:
    ActivityPartyTest() {}
    ~ActivityPartyTest() {}

private slots:
    void test_serialization_minimal();
    void test_serialization_full();
    void test_deserialization_minimal();
    void test_deserialization_full();
};

#endif // PARTYTEST_H
