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
