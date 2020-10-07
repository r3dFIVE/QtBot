#ifndef USERMODIFYCURRENTUSER_H
#define USERMODIFYCURRENTUSER_H

#include "route.h"


class UserModifyCurrentUser : public Route
{
public:
    const QString PATH = "/users/@me";

    UserModifyCurrentUser(const EventContext &context) {
        buildRequest(PATCH, PATH, Route::GLOBAL_BUCKET, context.getTargetPayload());
    }
};

#endif // USERMODIFYCURRENTUSER_H
