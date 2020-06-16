#include "assets.h"

void
Assets::read(const QJsonObject &jsonObject)  {
    large_image = jsonObject[LARGE_IMAGE].toString();
    large_text = jsonObject[LARGE_TEXT].toString();
    small_image = jsonObject[SMALL_IMAGE].toString();
    small_text = jsonObject[SMALL_TEXT].toString();
}

void
Assets::write(QJsonObject &jsonObject) const  {
    if (!large_image.isEmpty()) {
        jsonObject[LARGE_IMAGE] = large_image;
    }

    if (!large_text.isEmpty()) {
        jsonObject[LARGE_TEXT] = large_text;
    }

    if (!small_image.isEmpty()) {
        jsonObject[SMALL_IMAGE] = small_image;
    }

    if (!small_text.isEmpty()) {
        jsonObject[SMALL_TEXT] = small_text;
    }
}
