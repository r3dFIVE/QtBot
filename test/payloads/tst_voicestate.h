/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef VOICESTATETEST_H
#define VOICESTATETEST_H

#include <QObject>
#include <testsuite.h>

class VoiceStateTest : public TestSuite
{
    Q_OBJECT
public:
    VoiceStateTest() {}
    ~VoiceStateTest() {}

private slots:
    void test_deserialization_full();
    void test_deserialization_minimal();
    void test_serialization_full();
    void test_serialization_minimal();
};

#endif // VOICESTATETEST_H
