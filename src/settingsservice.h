#ifndef SETTINGSSERVICE_H
#define SETTINGSSERVICE_H

#include <QMap>
#include <QObject>

class SettingsService
{
public:
    SettingsService(QString path);

    QString fileName();
    QVariant value(QString key);
    void setValue(QString key, QVariant value);

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
