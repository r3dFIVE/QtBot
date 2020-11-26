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

#ifndef ENUM_SQL_H
#define ENUM_SQL_H

#include <QObject>

class Sql : public QObject
{
    Q_OBJECT

public:



    enum ErrorType {
        NoError,
        ConnectionError,
        StatementError,
        TransactionError,
        UnknownError
    };
    Q_ENUM(ErrorType)

    enum Location
    {
        BeforeFirstRow = -1,
        AfterLastRow = -2
    };
    Q_ENUM(Location)

    enum ParamTypeFlag
    {
        In = 0x00000001,
        Out = 0x00000002,
        InOut = In | Out,
        Binary = 0x00000004
    };
    Q_ENUM(ParamTypeFlag)
    Q_DECLARE_FLAGS(ParamType, ParamTypeFlag)

    enum TableType
    {
        Tables = 0x01,
        SystemTables = 0x02,
        Views = 0x04,
        AllTables = 0xff
    };
    Q_FLAG(TableType)

    enum NumericalPrecisionPolicy
    {
        LowPrecisionInt32    = 0x01,
        LowPrecisionInt64    = 0x02,
        LowPrecisionDouble   = 0x04,

        HighPrecision        = 0
    };
    Q_FLAG(NumericalPrecisionPolicy)

    enum BatchExecutionMode {
        ValuesAsRows,
        ValuesAsColumns
    };
    Q_FLAG(BatchExecutionMode)

    enum RequiredStatus {
        Unknown = -1,
        Optional = 0,
        Required = 1
    };
    Q_FLAG(RequiredStatus)
};

#endif // ENUM_SQL_H
