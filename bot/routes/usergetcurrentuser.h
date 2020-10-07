#ifndef USERGETCURRENTUSER_H
#define USERGETCURRENTUSER_H

#include "route.h"


class UserGetCurrentUser : public Route
{
public:
    const QString PATH = "/users/@me";

    UserGetCurrentUser(const EventContext &context) {
        buildRequest(GET, PATH, Route::GLOBAL_BUCKET, context.getTargetPayload());
    }
};

#endif // USERGETCURRENTUSER_H
