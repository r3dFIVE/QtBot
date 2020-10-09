#ifndef USERGETCURRENTUSER_H
#define USERGETCURRENTUSER_H

#include "route.h"


class UserGetCurrentUser : public Route
{
public:
    const QString PATH = "/users/@me";

    UserGetCurrentUser(const EventContext &context) {
        Q_UNUSED(context)

        buildRequest(GET, PATH);
    }
};

#endif // USERGETCURRENTUSER_H
