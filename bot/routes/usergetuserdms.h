#ifndef USERGETUSERDMS_H
#define USERGETUSERDMS_H

#include "route.h"


class UserGetUserDms : public Route
{
public:
    const QString PATH = "/users/@me/channels";

    UserGetUserDms(const EventContext &context) {
        buildRequest(GET, PATH, Route::GLOBAL_BUCKET, context.getTargetPayload());
    }
};


#endif // USERGETUSERDMS_H
