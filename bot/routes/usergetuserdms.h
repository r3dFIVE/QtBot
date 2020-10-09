#ifndef USERGETUSERDMS_H
#define USERGETUSERDMS_H

#include "route.h"


class UserGetUserDms : public Route
{
public:
    const QString PATH = "/users/@me/channels";

    UserGetUserDms(const EventContext &context) {
        Q_UNUSED(context)

        buildRequest(GET, PATH);
    }
};


#endif // USERGETUSERDMS_H
