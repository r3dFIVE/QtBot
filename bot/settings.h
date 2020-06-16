#ifndef SETTINGSSERVICE_H
#define SETTINGSSERVICE_H

#include <QMap>
#include <QObject>

class Settings
{
public:
    Settings(QString path);

    QVariant value(QString key);

private:
    QMap<QString, QVariant> _settings;
    QString _path;

    void parseSettingsFile();
    void validateSettings();
    void validateConnectionSettings();
    void validateDatabaseSettings();
    void validateLoggingSettings();
    void validateLogLevel(QString property, QString logLevel);
    void invalidDatabaseProperty [[ noreturn ]] (QString databaseType, QString propertyName);
    void invalidEnumValue [[ noreturn ]] (QString property, QString value, QMetaEnum metaEnum);
    bool isComment(QString);
};


#endif // SETTINGSSERVICE_H
