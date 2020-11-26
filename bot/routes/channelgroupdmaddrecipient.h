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

#ifndef CHANNELGROUPDMADDRECIPIENT_H
#define CHANNELGROUPDMADDRECIPIENT_H

#include "route.h"


class ChannelGroupDmAddRecipient : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/recipients/{user.id}";

    ChannelGroupDmAddRecipient(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(PUT, PATH, _pathParams[Route::USER_ID_TOKEN], context);
    }
};

#endif // CHANNELGROUPDMADDRECIPIENT_H
