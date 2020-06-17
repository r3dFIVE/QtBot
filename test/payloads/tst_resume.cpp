#include "tst_resume.h"
#include "testpayloads.h"

#include <payloads/resume.h>

void
ResumeTest::test_serialization() {
    Resume resume;
    resume.token = TEST_STRING1;
    resume.session_id = TEST_STRING2;
    resume.seq = TEST_INT1;

    QJsonObject serializedResume = resume.toQJsonObject();

    QVERIFY(serializedResume[resume.TOKEN] == TEST_STRING1);
    QVERIFY(serializedResume[resume.TOKEN] != TEST_STRING2);

    QVERIFY(serializedResume[resume.SESSION_ID] != TEST_STRING1);
    QVERIFY(serializedResume[resume.SESSION_ID] == TEST_STRING2);

    QVERIFY(serializedResume[resume.SEQ] == TEST_INT1);
    QVERIFY(serializedResume[resume.SEQ] != TEST_INT2);
}

void
ResumeTest::test_deserialization() {
    Resume resume;
    QString s = PLD_RESUME;
    resume.fromQString(PLD_RESUME);

    QVERIFY(resume.token == TEST_STRING1);
    QVERIFY(resume.token != TEST_STRING2);

    QVERIFY(resume.session_id != TEST_STRING1);
    QVERIFY(resume.session_id == TEST_STRING2);

    QVERIFY(resume.seq == TEST_INT1);
    QVERIFY(resume.seq != TEST_INT2);
}

static ResumeTest RESUME_TEST;
