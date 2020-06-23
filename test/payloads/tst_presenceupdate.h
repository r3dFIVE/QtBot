#ifndef PRESENCEUPDATETEST_H
#define PRESENCEUPDATETEST_H

#include <QObject>
#include <testsuite.h>

class PresenceUpdateTest : public TestSuite
{
    Q_OBJECT

public:
    PresenceUpdateTest() {}
    ~PresenceUpdateTest() {}

private slots:
    void test_serialization_minimal();
    void test_serialization_full();
    void test_deserialization_minimal();
    void test_deserialization_full();
};

#endif // PRESENCEUPDATETEST_H
