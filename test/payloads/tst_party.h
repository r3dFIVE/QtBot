#ifndef PARTYTEST_H
#define PARTYTEST_H

#include <QObject>
#include <testsuite.h>

class PartyTest : public TestSuite
{
    Q_OBJECT

public:
    PartyTest() {}
    ~PartyTest() {}

private slots:
    void test_serialization_minimal();
    void test_serialization_full();
    void test_deserialization_minimal();
    void test_deserialization_full();
};

#endif // PARTYTEST_H
