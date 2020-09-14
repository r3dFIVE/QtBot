#include "discordapi.h"

#include "createmessage.h"

QSharedPointer<EventContext>
DiscordAPI::channelCreateMessage(const EventContext &context)
{
    CreateMessage createMessage(context);

    return _httpClient.processRoute(createMessage);
}
