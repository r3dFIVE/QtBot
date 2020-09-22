#include "discordapi.h"

#include "channelcreatemessage.h"

QSharedPointer<EventContext>
DiscordAPI::channelCreateMessage(const EventContext &context)
{
    ChannelCreateMessage createMessage(context);

    return _httpClient.processRoute(createMessage);
}
