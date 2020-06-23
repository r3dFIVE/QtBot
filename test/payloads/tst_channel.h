#ifndef CHANNELTEST_H
#define CHANNELTEST_H

#include <QObject>
#include <testsuite.h>

class ChannelTest : public TestSuite
{
    Q_OBJECT
public:
    ChannelTest() {}
    ~ChannelTest() {}

private slots:
    void test_deserialization_full();
    void test_deserialization_minimal();
    void test_serialization_full();
    void test_serialization_minimal();
};

#endif // CHANNELTEST_H
