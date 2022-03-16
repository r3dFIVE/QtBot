#ifndef HELPPAGE_H
#define HELPPAGE_H

#include <QObject>
#include <QString>

class HelpPage : public QObject
{
    Q_OBJECT

protected:
    QString _description;
    QString _descriptionShort;
    QString _name;

public:    
    static const QString DESCRIPTION;
    static const QString DESCRIPTION_SHORT;

    QString getDescription() const;
    QString getDescriptionShort() const;
    QString getName() const;
    void setDescription(const QString &description);
    void setDescriptionShort(const QString &description);
    virtual void setName(const QString &name);

};

#endif // HELPPAGE_H
