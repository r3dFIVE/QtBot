#ifndef ROLETEST_H
#define ROLETEST_H

#include "testpayloads.h"
#include "testsuite.h"

#include <QObject>

class RoleTest : public TestSuite
{
    Q_OBJECT
public:
    RoleTest() {}
    ~RoleTest() {}

private slots:
    void test_serialization();
    void test_deserialization();
};

#endif // ROLETEST_H
