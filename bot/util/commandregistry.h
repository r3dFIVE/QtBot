#ifndef COMMANDREGISTRY_H
#define COMMANDREGISTRY_H

#include <QMap>
#include <QObject>
#include <functional>



class CommandRegistry : public QObject
{
    Q_OBJECT

    QMap<QString, QString> coreCommands;

public:
    explicit CommandRegistry(QObject *parent = nullptr);


signals:

};

#endif // COMMANDREGISTRY_H
