#include "activitytimestamps.h"

const QString ActivityTimestamps::START = "start";
const QString ActivityTimestamps::END = "end";

QJsonValue
ActivityTimestamps::getStart() const {
    return _jsonObject[START];
}

void
ActivityTimestamps::setStart(const QJsonValue &start) {
     _jsonObject[START] = start;
}

QJsonValue
ActivityTimestamps::getEnd() const {
     return _jsonObject[END];
}

void
ActivityTimestamps::setEnd(const QJsonValue &end) {
     _jsonObject[END] = end;
}
