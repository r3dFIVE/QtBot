#ifndef RESUMETEST_H
#define RESUMETEST_H

#include <QObject>
#include <testsuite.h>

class ResumeTest : public TestSuite
{
    Q_OBJECT
public:
    ResumeTest() {}
    ~ResumeTest() {}

private slots:
    void test_serialization();
    void test_deserialization();
};

#endif // RESUMETEST_H
