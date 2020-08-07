#include "tst_resume.h"
#include "testpayloads.h"

#include <payloads/resume.h>

void
ResumeTest::test_serialization() {
    Resume resume;

    resume.setToken(TEST_STRING1);

    resume.setSessionId(TEST_STRING2);

    resume.setSeq(TEST_INT1);

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
    Resume resume(PLD_RESUME);

    QVERIFY(resume.getToken() == TEST_STRING1);
    QVERIFY(resume.getToken() != TEST_STRING2);
    QVERIFY(resume.getSessionId() != TEST_STRING1);
    QVERIFY(resume.getSessionId() == TEST_STRING2);
    QVERIFY(resume.getSeq() == TEST_INT1);
    QVERIFY(resume.getSeq() != TEST_INT2);
}

static ResumeTest RESUME_TEST;
