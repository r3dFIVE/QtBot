#ifndef PROPERTIESTEST_H
#define PROPERTIESTEST_H

#include <QObject>
#include <testsuite.h>

class IdentifyPropertiesTest : public TestSuite
{
    Q_OBJECT
public:
    IdentifyPropertiesTest() {}
    ~IdentifyPropertiesTest() {}

private slots:
    void test_serialization();
    void test_deserialization();
};

#endif // PROPERTIESTEST_H
