#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <QtTest>
#include <QCoreApplication>

class TestSuite : public QObject
{
public:
    TestSuite();
    static QList<TestSuite*> & suite();
};

#endif // TESTSUITE_H
