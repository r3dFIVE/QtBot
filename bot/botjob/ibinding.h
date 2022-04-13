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

#ifndef IBINDING_H
#define IBINDING_H

#include "ibindingproperties.h"
#include "ibotjob.h"
#include "logging/logfactory.h"


class IBinding : public QObject
{
    Q_OBJECT

public:    

    static const QString BINDING_TYPE;
    static const QString BINDING_TYPE_COMMAND;
    static const QString BINDING_TYPE_GATEWAY;
    static const QString BINDING_TYPE_TIMED;
    static const QString BINDING_NAME;
    static const QString FUNCTION;
    static const QString DESCRIPTION;
    static const QString DESCRIPTION_SHORT;
    static const QString IGNORE_ADMIN;
    static const QString ADMIN_ONLY;
    static const QString NO_DESCRIPTION;

    IBinding() {};
    IBinding(QSharedPointer<IBindingProperties> properties) : _baseProperties{properties} {}

    bool validateFunctionMapping(const QMetaObject &metaObject) const;
    IBotJob::FunctionMapping getFunctionMapping() const;

    void setFunctionMapping(const IBotJob::FunctionMapping &functionMapping);
    bool ignoreAdmin();
    bool isAdminOnly() const;
    const QString& getName() const;
    const QString getDescriptionShort() const;
    const QString getDescription() const;

    void setBaseProperties(QSharedPointer<IBindingProperties> properties);

    virtual bool isValid(const QMetaObject &metaObject) const = 0;

protected:
    bool isValidParam(const QString &name, const QString &value) const;

    IBotJob::FunctionMapping _functionMapping;
    Logger *_logger = LogFactory::getLogger(this);
    QSharedPointer<IBindingProperties> _baseProperties;
};


#endif // IBINDING_H
