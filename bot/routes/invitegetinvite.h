#ifndef INVITEGETINVITE_H
#define INVITEGETINVITE_H

#include "route.h"


class InviteGetInvite : public Route
{
public:
    const QString PATH = "/invites/{invite.code}";

    InviteGetInvite(const EventContext &context) {
        _pathParams[Route::INVITE_CODE_TOKEN] = context.getInviteCode().toString();

        buildRequest(GET, PATH, context);
    }
};

#endif // INVITEGETINVITE_H
