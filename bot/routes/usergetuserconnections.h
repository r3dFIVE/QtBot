#ifndef USERGETUSERCONNECTIONS_H
#define USERGETUSERCONNECTIONS_H

#include "route.h"


class UserGetUserConnections : public Route
{
public:
    const QString PATH = "/users/@me/connections";

    UserGetUserConnections(const EventContext &context) {
        buildRequest(GET, PATH, Route::GLOBAL_BUCKET, context.getTargetPayload());
    }
};

#endif // USERGETUSERCONNECTIONS_H
