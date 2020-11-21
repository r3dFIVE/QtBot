/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
