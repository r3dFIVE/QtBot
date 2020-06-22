#ifndef GUILDMEMEBERTEST_H
#define GUILDMEMEBERTEST_H

#include <QObject>
#include <testsuite.h>

class GuildMemberTest : public TestSuite
{
    Q_OBJECT
public:
    GuildMemberTest() {}
    ~GuildMemberTest() {}

private slots:
    void test_deserialization_full();
    void test_deserialization_minimal();
    void test_serialization_full();
    void test_serialization_minimal();
};

#endif // GUILDMEMEBERTEST_H
