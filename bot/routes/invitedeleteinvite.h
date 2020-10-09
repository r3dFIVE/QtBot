#ifndef INVITEDELETEINVITE_H
#define INVITEDELETEINVITE_H

#include "route.h"


class InviteDeleteInvite : public Route
{
public:
    const QString PATH = "/invites/{invite.code}";

    InviteDeleteInvite(const EventContext &context) {
        _pathParams[Route::INVITE_CODE_TOKEN] = context.getInviteCode().toString();

        buildRequest(DELETE, PATH, context);
    }
};

#endif // INVITEDELETEINVITE_H
