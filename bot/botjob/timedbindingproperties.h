#ifndef TIMEDBINDINGPROPERTIES_H
#define TIMEDBINDINGPROPERTIES_H

#include <QObject>

struct TimedBindingProperties
{
    bool forceEnable = false;
    bool singleton = false;
    bool singleShot = true;
    int fireAfter = 0;
    QString scriptName;
};

#endif // TIMEDBINDINGPROPERTIES_H
