#ifndef INVALIDSESSIONTEST_H
#define INVALIDSESSIONTEST_H

#include <QObject>
#include <testsuite.h>

class InvalidSessionTest : public TestSuite
{
    Q_OBJECT
public:
    InvalidSessionTest() {}
    ~InvalidSessionTest() {}

private slots:
    void test_deserialization();
};

#endif // INVALIDSESSIONTEST_H

