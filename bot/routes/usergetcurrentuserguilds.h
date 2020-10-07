#ifndef USERGETCURRENTUSERGUILDS_H
#define USERGETCURRENTUSERGUILDS_H

#include "route.h"


class UserCurrentGetUserGuilds : public Route
{
public:
    const QString PATH = "/users/@me/guilds";

    UserCurrentGetUserGuilds(const EventContext &context) {
        buildRequest(GET, PATH, Route::GLOBAL_BUCKET,
                     context.getTargetPayload(), context.getQueryParams());
    }
};

#endif // USERGETCURRENTUSERGUILDS_H
