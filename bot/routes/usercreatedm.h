#ifndef USERCREATEDM_H
#define USERCREATEDM_H

#include "route.h"


class UserCreateDm : public Route
{
public:
    const QString PATH = "/users/@me/channels";

    UserCreateDm(const EventContext &context) {
        buildRequest(POST, PATH, Route::GLOBAL_BUCKET, context.getTargetPayload());
    }
};

#endif // USERCREATEDM_H
