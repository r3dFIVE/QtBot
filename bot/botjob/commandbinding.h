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

#ifndef COMMANDBINDING_H
#define COMMANDBINDING_H

#include "ibinding.h"

class CommandBinding : public IBinding
{
    Q_OBJECT

public:
    static const QString COMMAND;

    CommandBinding() { }
    CommandBinding(const QString &commandName,
                   const IBotJob::FunctionMapping &functionMapping,
                   QSharedPointer<IBindingProperties> properties);
    CommandBinding(const QString &commandName,
                   const IBotJob::FunctionMapping &functionMapping);
    CommandBinding(const CommandBinding &other);
    ~CommandBinding() {}

    CommandBinding &operator=(const CommandBinding &other);

    void copy(const CommandBinding &other);

    bool isValid(const QMetaObject &metaObject) const override;
};

#endif // COMMANDBINDING_H
