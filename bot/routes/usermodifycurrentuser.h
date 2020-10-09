#ifndef USERMODIFYCURRENTUSER_H
#define USERMODIFYCURRENTUSER_H

#include "route.h"


class UserModifyCurrentUser : public Route
{
public:
    const QString PATH = "/users/@me";

    UserModifyCurrentUser(const EventContext &context) {
        buildRequest(PATCH, PATH, context);
    }
};

#endif // USERMODIFYCURRENTUSER_H
