#ifndef USERGETUSER_H
#define USERGETUSER_H

#include "route.h"


class UserGetUser : public Route
{
public:
    const QString PATH = "/users/{user.id}";

    UserGetUser(const EventContext &context) {
        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(GET, PATH);
    }
};

#endif // USERGETUSER_H
