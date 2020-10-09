#ifndef VOICELISTVOICEREGIONS_H
#define VOICELISTVOICEREGIONS_H

#include "route.h"


class VoiceListVoiceRegions: public Route
{
public:
    const QString PATH = "/voice/regions";

    VoiceListVoiceRegions(const EventContext &context) {
        Q_UNUSED(context)

        buildRequest(GET, PATH);
    }
};

#endif // VOICELISTVOICEREGIONS_H
