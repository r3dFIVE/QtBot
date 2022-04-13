#ifndef IBindingProperties_H
#define IBindingProperties_H

#include <QString>

struct IBindingProperties
{
    bool adminOnly = false;
    bool ignoreAdmin = false;
    QString description;
    QString descriptionShort;
    QString name;
};

#endif // IBindingProperties_H
