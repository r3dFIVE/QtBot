#ifndef IDENTIFYTEST_H
#define IDENTIFYTEST_H

#include <QObject>
#include <testsuite.h>

class IdentifyTest : public TestSuite
{
    Q_OBJECT
public:
    IdentifyTest() {}
    ~IdentifyTest() {}

private slots:
    void test_deserialization_full();
    void test_deserialization_minimal();
    void test_serialization_full();
    void test_serialization_minimal();
};

#endif // IDENTIFYTEST_H
