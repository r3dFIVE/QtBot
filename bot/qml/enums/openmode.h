#ifndef OPENMODE_H
#define OPENMODE_H

#include <QObject>

class OpenMode : public QObject
{
    Q_OBJECT

public:
    OpenMode();

    enum Mode {
        NotOpen = 0x0000,
        ReadOnly = 0x0001,
        WriteOnly = 0x0002,
        ReadWrite = ReadOnly | WriteOnly,
        Append = 0x0004,
        Truncate = 0x0008,
        Text = 0x0010,
        Unbuffered = 0x0020,
        NewOnly = 0x0040,
        ExistingOnly = 0x0080
    };
    Q_ENUM(Mode)

};

#endif // OPENMODE_H
