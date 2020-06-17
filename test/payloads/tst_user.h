#ifndef USERTEST_H
#define USERTEST_H

#include <QObject>
#include <testsuite.h>

class UserTest : public TestSuite
{
    Q_OBJECT
public:
    UserTest() {}
    ~UserTest() {}

private slots:
    void test_serialization_minimal();
    void test_serialization_full();
    void test_deserialization_minimal();
    void test_deserialization_full();
};

#endif // USERTEST_H
