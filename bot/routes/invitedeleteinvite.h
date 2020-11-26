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

#ifndef INVITEDELETEINVITE_H
#define INVITEDELETEINVITE_H

#include "route.h"


class InviteDeleteInvite : public Route
{
public:
    const QString PATH = "/invites/{invite.code}";

    InviteDeleteInvite(const EventContext &context) {
        _pathParams[Route::INVITE_CODE_TOKEN] = context.getInviteCode().toString();

        buildRequest(DELETE, PATH, context);
    }
};

#endif // INVITEDELETEINVITE_H
