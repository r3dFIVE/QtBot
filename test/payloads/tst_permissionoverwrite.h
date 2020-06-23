#ifndef PERMISSIONOVERWRITETEST_H
#define PERMISSIONOVERWRITETEST_H

#include <QObject>
#include <testsuite.h>

class PermissionOverwriteTest : public TestSuite
{
    Q_OBJECT
public:
    PermissionOverwriteTest() {}
    ~PermissionOverwriteTest() {}

private slots:
    void test_serialization();
    void test_deserialization();
};

#endif // PERMISSIONOVERWRITETEST_H
