#ifndef VOICELISTVOICEREGIONS_H
#define VOICELISTVOICEREGIONS_H

#include "route.h"


class VoiceListVoiceRegions: public Route
{
public:
    const QString PATH = "/voice/regions";

    VoiceListVoiceRegions(const EventContext &context) {
        buildRequest(GET, PATH, Route::GLOBAL_BUCKET, context.getTargetPayload());
    }
};

#endif // VOICELISTVOICEREGIONS_H
