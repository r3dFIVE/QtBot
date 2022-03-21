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

#ifndef GATEWAYBINDING_H
#define GATEWAYBINDING_H

#include "ibinding.h"
#include "gatewaybindingproperties.h"


class GatewayBinding : public IBinding
{
    Q_OBJECT

    QSharedPointer<GatewayBindingProperties> _gatewayProperties;

public:

    static const QString GATEWAY_EVENT;

    GatewayBinding() {}
    GatewayBinding(const QString &eventType);
    GatewayBinding(const GatewayBinding &other);

    GatewayBinding &operator=(const GatewayBinding &other);

    void setGatewayProperties(QSharedPointer<GatewayBindingProperties> properties);

    void copy(const GatewayBinding &other);

    bool isValid(const QMetaObject &metaObject) const override;
    QString getEventName() const;
};

#endif // GATEWAYBINDING_H
