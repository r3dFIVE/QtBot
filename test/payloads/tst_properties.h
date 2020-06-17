#ifndef PROPERTIESTEST_H
#define PROPERTIESTEST_H

#include <QObject>
#include <testsuite.h>

class PropertiesTest : public TestSuite
{
    Q_OBJECT
public:
    PropertiesTest() {}
    ~PropertiesTest() {}

private slots:
    void test_serialization();
    void test_deserialization();
};

#endif // PROPERTIESTEST_H
