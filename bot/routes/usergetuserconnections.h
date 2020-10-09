#ifndef USERGETUSERCONNECTIONS_H
#define USERGETUSERCONNECTIONS_H

#include "route.h"


class UserGetUserConnections : public Route
{
public:
    const QString PATH = "/users/@me/connections";

    UserGetUserConnections(const EventContext &context) {
        Q_UNUSED(context)

        buildRequest(GET, PATH);
    }
};

#endif // USERGETUSERCONNECTIONS_H
