#ifndef USERGETUSER_H
#define USERGETUSER_H

#include "route.h"


class UserGetUser : public Route
{
public:
    const QString PATH = "/users/{user.id}";

    UserGetUser(const EventContext &context) {
        QString userId = context.getUserId().toString();

        _pathParams[Route::USER_ID_TOKEN] = userId;

        buildRequest(GET, PATH, userId, context.getTargetPayload());
    }
};

#endif // USERGETUSER_H
